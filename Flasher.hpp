//
// Flasher
// BrewTroller_Flasher
//
// Created by Eric Yanush on 2017-01-19.
//

#ifndef BREWTROLLER_FLASHER_FLASHER_HPP
#define BREWTROLLER_FLASHER_FLASHER_HPP

#include <vector>
#include <string>
#include <functional>

extern "C" {
#include "libavrdude.h"
};

/**
 * Flash progress callback
 *
 * @param int: % complete
 * @param bool: Flash complete
 * @param bool: Success
 */
typedef void (*FlashProgressCallback)(int, bool, bool);

class Flasher {

public:
    /**
     * Construct Flasher with default options
     *
     * Programmer type = arduino
     * Part Description = m1284p
     * Baud Rate = 115200
     * Signature Check = Disabled
     * Verify Step = Disabled
     */
    Flasher();
    ~Flasher();

    bool loadConfigFile(std::string fileName = "avrdude.conf");

    void programmer(std::string programmer);
    std::string programmer();

    void hexFileName(std::string fileName);
    std::string hexFileName();

    void partName(std::string descr);
    std::string partName();

    void serialPortName(std::string serialPort);
    std::string serialPortName();

    void serialBaudRate(uint32_t baudrate);
    uint32_t  serialBaudRate();

    void signatureCheck(bool enabled);
    bool signatureCheck();

    void verifyWrites(bool enabled);
    bool verifyWrites();

    static void progressCallback(std::function<void(int, bool, bool)> callback);

    std::vector<std::string> logMessages();

    bool flash();

private:
    /// avrdude options

    std::string programmerType;
    std::string hexFile;
    std::string memoryType = "flash";
    std::string partDescription;
    std::string serialPort;
    uint32_t programmerBaudRate;
    bool enableVerify;

    /// avrdude callbacks
    static std::function<void(int, bool, bool)> progressCB;
    static void progressHandler(int, double, char*);

    std::vector<std::string> messages;
    void logMessageHandler(std::string);

    /// avrdude objects
    PROGRAMMER* progrmr;

    bool programmerWasSetup = false;

    bool failWithError(std::string);
};


#endif //BREWTROLLER_FLASHER_FLASHER_HPP
