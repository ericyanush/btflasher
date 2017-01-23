//
// Scanner
// BrewTroller_Flasher
//
// Created by Eric Yanush on 2017-01-19.
//

#include <regex>
#include "Scanner.hpp"
#include "serial/serial.h"

const std::string Scanner::idRegex = "([0-9]*)\\t(SYS|838983)\\t(VER|866982)\\t([0-9a-zA-Z.-]*)\\t([0-9]*)\\t([0-9]*)\\t([0-9]*)\\t([0-9]*)";

BrewTrollerInfo Scanner::detect_brewtroller(std::string portName) {

    BrewTrollerInfo info;
    info.positiveID = false;

    try {
        serial::Serial testPort(portName,
                                Scanner::btBaudRate,
                                serial::Timeout::simpleTimeout(Scanner::scanTimeoutMS));

        if (!testPort.isOpen()) {
            testPort.open();
        }

        auto recData = testPort.readline();

        std::regex re(Scanner::idRegex);
        std::smatch versionMatch;

        if (std::regex_search(recData, versionMatch, re)) {
            info.positiveID = true;

            info.version = versionMatch.str(IdPos::version);

            if (versionMatch.str(IdPos::metric)[0] == '0') {
                info.usesMetric = false;
            } else {
                info.usesMetric = true;
            }
        }
    }
    catch (...) {
        return info;
    }


    return info;

}

std::vector<Port> Scanner::enumerate_serial_ports() {

    //enumerate all the ports
    auto discovered_ports = serial::list_ports();
    std::vector<Port> ports;

    for (auto discPort : discovered_ports) {
        Port port;
        port.name = discPort.port;
        port.btInfo = detect_brewtroller(discPort.port);
        ports.push_back(port);
    }

    return ports;
}