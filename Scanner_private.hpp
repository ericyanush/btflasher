//
// Scanner_private
// BrewTroller_Flasher
//
// Created by Eric Yanush on 2017-01-19.
//

#ifndef BREWTROLLER_FLASHER_SCANNER_PRIVATE_HPP
#define BREWTROLLER_FLASHER_SCANNER_PRIVATE_HPP

#include <string>
#include "Scanner.hpp"

namespace Scanner {

    const static int btBaudRate = 115200;
    const static int scanTimeoutMS = 4000;

    // Timestamp, SYS, VER, Version String, Build(not used), Protocol Type, COM Schema, Metric Units
    const static std::string idRegex = "([0-9]*)\\t(SYS|838983)\\t(VER|866982)\\t([0-9a-zA-Z.-]*)\\t([0-9]*)\\t([0-9]*)\\t([0-9]*)\\t([0-9]*)";
    enum IdPos {
        timestamp,
        sysStr,
        verStr,
        version,
        build,
        protocol,
        schemaVer,
        metric
    };

    BrewTrollerInfo* detect_brewtroller(std::string portName);
}

#endif //BREWTROLLER_FLASHER_SCANNER_PRIVATE_HPP
