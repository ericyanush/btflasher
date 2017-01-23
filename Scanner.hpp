//
// Scanner
// BrewTroller_Flasher
//
// Created by Eric Yanush on 2017-01-19.
//

#ifndef BREWTROLLER_FLASHER_SCANNER_HPP
#define BREWTROLLER_FLASHER_SCANNER_HPP

#include <string>
#include <vector>

struct BrewTrollerInfo {
    std::string version;
    bool usesMetric;
    bool positiveID;
};

struct Port {
    /// @property Serial Port Name, contents is dependant on OS
    std::string name;

    BrewTrollerInfo btInfo;
};

class Scanner {
public:
    static std::vector<Port> enumerate_serial_ports();

private:
    const static int btBaudRate = 115200;
    const static int scanTimeoutMS = 4000;

    // Timestamp, SYS, VER, Version String, Build(not used), Protocol Type, COM Schema, Metric Units
    const static std::string idRegex;
    enum IdPos {
        wholeMatch,
        timestamp,
        sysStr,
        verStr,
        version,
        build,
        protocol,
        schemaVer,
        metric
    };

    static BrewTrollerInfo detect_brewtroller(std::string portName);
};



#endif //BREWTROLLER_FLASHER_SCANNER_HPP
