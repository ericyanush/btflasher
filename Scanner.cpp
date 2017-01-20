//
// Scanner
// BrewTroller_Flasher
//
// Created by Eric Yanush on 2017-01-19.
//

#include <regex>
#include "Scanner.hpp"
#include "Scanner_private.hpp"
#include "serial/serial.h"

BrewTrollerInfo* Scanner::detect_brewtroller(std::string portName) {

    serial::Serial* testPort;

    try {
        testPort = new serial::Serial(portName,
                                      Scanner::btBaudRate,
                                      serial::Timeout::simpleTimeout(Scanner::scanTimeoutMS));

        if (!testPort->isOpen()) {
            testPort->open();
        }
    }
    catch (...) {
        return nullptr;
    }

    auto recData = testPort->readline();

    std::regex re(Scanner::idRegex);
    std::smatch versionMatch;

    if (std::regex_search(recData, versionMatch, re)) {
        auto info = new BrewTrollerInfo;

        info->version = versionMatch.str(IdPos::version).c_str();

        if (versionMatch.str(IdPos::metric)[0] == '0') {
            info->usesMetric = false;
        }
        else {
            info->usesMetric = true;
        }

        return info;
    }

    return nullptr;

}

int enumerate_serial_ports(Port* retPorts) {

    //enumerate all the ports
    auto discovered_ports = serial::list_ports();
    retPorts = new Port[discovered_ports.size()];

    for (size_t i = 0; i < discovered_ports.size(); i++) {
        retPorts[i].name = discovered_ports[i].port.c_str();
        retPorts[i].btInfo = Scanner::detect_brewtroller(retPorts[i].name);
    }

    return discovered_ports.size();
}