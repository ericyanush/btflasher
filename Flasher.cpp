//
// Flasher
// BrewTroller_Flasher
//
// Created by Eric Yanush on 2017-01-19.
//

#include <functional>
#include "Flasher.hpp"

/// Global vars used by libavrdude
extern "C" {

    int quell_progress = 0;
    int verbose = 0;
    int ovsigck;

    const char* progname = "BrewTroller Flasher";
    char progbuf[PATH_MAX];

    /// Bridge avrdude's global logging function to an internal logging facility
    std::function<void(std::string)> logHandler;
    int avrdude_message(const int msglvl, const char* format, ...) {

        if (logHandler) {
            va_list varargs;
            va_start(varargs, format);

            std::string logMessage;
            std::vector<char> buffer(1024);

            vsnprintf(&buffer[0], buffer.max_size(), format, varargs);
            logMessage = std::string(buffer.data());

            logHandler(logMessage);

            va_end(varargs);
        }

        return 0;
    }

};

Flasher::Flasher() {
    // initialize the avrdude config structures
    init_config();

    progrmr = nullptr;
    programmerType = "arduino";
    hexFile = "";
    partDescription = "m1284p";
    serialPort = "";
    programmerBaudRate = 115200;
    ovsigck = 1;
    enableVerify = false;
}

Flasher::~Flasher() {

    cleanup_config();

    // cleanup the programmer object, if it exists
    if (progrmr != nullptr && programmerWasSetup) {
        progrmr->teardown(progrmr);
    }
}

bool Flasher::loadConfigFile(std::string fileName) {
    int returnCode = read_config(fileName.c_str());

    if (returnCode) {
        return false;
    }

    return true;
}

void Flasher::programmer(std::string programmer) {
    programmerType = programmer;
}

std::string Flasher::programmer() {
    return programmerType;
}

void Flasher::hexFileName(std::string fileName) {
    hexFile = fileName;
}

std::string Flasher::hexFileName() {
    return hexFile;
}

void Flasher::partName(std::string name) {
    partDescription = name;
}

std::string Flasher::partName() {
    return partDescription;
}

void Flasher::serialPortName(std::string serialPort) {
    this->serialPort = serialPort;
}

std::string Flasher::serialPortName() {
    return serialPort;
}

void Flasher::serialBaudRate(uint32_t baudrate) {
    programmerBaudRate = baudrate;
}

uint32_t Flasher::serialBaudRate() {
    return programmerBaudRate;
}

void Flasher::signatureCheck(bool enabled) {
    // ovsigck: 1 = override, 0 = verify signature
    ovsigck = !enabled;
}

bool Flasher::signatureCheck() {
    // ovsigck: 1 = override, 0 = verify signature
    return !ovsigck;
}

void Flasher::verifyWrites(bool enabled) {
    enableVerify = enabled;
}

bool Flasher::verifyWrites() {
    return enableVerify;
}

void Flasher::progressCallback(std::function<void(int, bool, bool)> callback) {
    progressCB = callback;
}

void Flasher::progressHandler(int percentComp, bool done, bool success) {
    progressCB(percentComp, done, success);
}

std::vector<std::string> Flasher::logMessages() {
    return messages;
}

void Flasher::flash() {

    //get the programmer
    progrmr = locate_programmer(programmers, programmerType.c_str());

    if (progrmr == nullptr) {
        return failWithError("Unable to load programmer type: " + programmerType);
    }

    if (progrmr->initpgm) {
        progrmr->initpgm(progrmr);
    }

    if (progrmr->setup) {
        progrmr->setup(progrmr);
        programmerWasSetup = true;
    }

    UPDATE* updateOp = new UPDATE();
    char* memType = const_cast<char*>(memoryType.c_str());
    updateOp->memtype = memType;
    updateOp->op = DEVICE_WRITE;
    char* fileName = const_cast<char*>(hexFile.c_str());
    updateOp->filename = fileName;
    updateOp->format = FMT_AUTO;

    char* partDescr = const_cast<char*>(partDescription.c_str());
    struct avrpart* part = locate_part(part_list, partDescr);

    if (part == nullptr) {
        return failWithError("Could not locate part: " + partDescription);
    }

    if (avr_initmem(part) != 0) {
        return failWithError("Error initializing device memory");
    }


    // configure programmer serial port
    progrmr->baudrate = programmerBaudRate;
    char* portName = const_cast<char*>(serialPort.c_str());
    if (progrmr->open(progrmr, portName) < 0) {
        return failWithError("Error opening port: " + serialPort);
    }

    //enable programming mode
    progrmr->enable(progrmr);

    if (progrmr->initialize(progrmr, part) < 0) {
        progrmr->disable(progrmr);
        progrmr->close(progrmr);
        return failWithError("Error initializing device");
    }

    int verifyRC = 0;
    int updateRC = do_op(progrmr, part, updateOp, UF_NONE);

    if (updateRC) {
        failWithError("Error performing flash operation");
    }

    if (!updateOp && enableVerify) {
        UPDATE* verifyOp = dup_update(updateOp);
        verifyOp->op = DEVICE_VERIFY;

        verifyRC = do_op(progrmr,  part, verifyOp, UF_NONE);
    }

    progrmr->powerdown(progrmr);
    progrmr->disable(progrmr);
    progrmr->close(progrmr);

    progressHandler(100, true, !updateRC && !verifyRC);
}


void Flasher::logMessageHandler(std::string message) {
    messages.push_back(message);
}

void Flasher::failWithError(std::string error) {
    messages.push_back(error);
    return progressHandler(0, true, false);
}