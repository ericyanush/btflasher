//
// Scanner
// BrewTroller_Flasher
//
// Created by Eric Yanush on 2017-01-19.
//

#ifndef BREWTROLLER_FLASHER_SCANNER_HPP
#define BREWTROLLER_FLASHER_SCANNER_HPP

#ifdef  __cplusplus
extern "C" {
#endif

    struct BrewTrollerInfo {
        const char* version;
        bool usesMetric;
    };

    struct Port {
        /// @property Serial Port Name, contents is dependant on OS
        const char* name;

        BrewTrollerInfo* btInfo;
    };

    /// Enumerate all serial ports
    /// @param Pointer that will point to array of discovered ports
    /// @returns The number of ports found
    int enumerate_serial_ports(Port*);


#ifdef __cplusplus
};
#endif


#endif //BREWTROLLER_FLASHER_SCANNER_HPP
