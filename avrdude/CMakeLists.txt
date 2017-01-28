cmake_minimum_required(VERSION 3.2)
project(avrdude)

## Build Platform Options
include(CheckSymbolExists)
include(CheckCXXSourceCompiles)
include(CheckTypeSize)
include(CheckIncludeFiles)
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DCONFIG_DIR="${CMAKE_INSTALL_FULL_SYSCONFDIR}")

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DWIN32NATIVE)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(HAVE_LIBWS2_32 YES)
endif()

set(LIB_SOURCE_FILES
        arduino.h
        arduino.c
        avrdude.h
        avr.c
        avr910.h
        avr910.c
        avrftdi.h
        avrftdi.c
        avrftdi_private.h
        avrftdi_tpi.h
        avrftdi_tpi.c
        avrpart.c
        bitbang.h
        bitbang.c
        buspirate.h
        buspirate.c
        butterfly.h
        butterfly.c
        config.h
        config.c
        confwin.c
        crc16.h
        crc16.c
        dfu.h
        dfu.c
        fileio.c
        flip1.h
        flip1.c
        flip2.h
        flip2.c
        freebsd_ppi.h
        ft245r.h
        ft245r.c
        jtagmkI.h
        jtagmkI.c
        jtagmkI_private.h
        jtagmkII.h
        jtagmkII.c
        jtag3.h
        jtag3.c
        jtag3_private.h
        libavrdude.h
        linuxgpio.h
        linuxgpio.c
        linux_ppdev.h
        lists.c
        my_ddk_hidsdi.h
        par.h
        par.c
        pgm.c
        pgm_type.c
        pickit2.h
        pickit2.c
        pindefs.c
        ppi.h
        ppi.c
        ppiwin.c
        safemode.c
        serbb.h
        serbb_posix.c
        serbb_win32.c
        ser_win32.c
        ser_avrdoper.c
        ser_posix.c
        ser_win32.c
        solaris_ecpp.h
        stk500.h
        stk500.c
        stk500_private.h
        stk500v2.h
        stk500v2.c
        stk500v2_private.h
        stk500generic.h
        stk500generic.c
        tpi.h
        usbasp.h
        usbasp.c
        usb_libusb.c
        usbtiny.h
        usbtiny.c
        update.c
        wiring.h
        wiring.c)

set(EXE_SOURCE_FILES
        main.c
        term.c
        term.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_path(HAVE_DDK_HIDSDI_H ddk/hidsdi.h)
if (HAVE_DDK_HIDSDI_H)
    include_directories(${HAVE_DDK_HIDSDI_H})
endif()

check_include_files(dlfcn.h HAVE_DLFCN_H)
check_include_files(fcntl.h HAVE_FCNTL_H)
check_symbol_exists(gettimeofday sys/time.h HAVE_GETTIMEOFDAY)
check_include_files(inttypes.h HAVE_INTTYPES_H)


find_library(HAVE_LIBELF elf)
find_path(HAVE_LIBELF_H libelf.h)
if (HAVE_LIBELF_H)
    include_directories(${HAVE_LIBELF_H})
endif()
find_path(HAVE_LIBELF_LIBELF_H libelf/libelf.h)
if (HAVE_LIBELF_LIBELF_H)
    include_directories(${HAVE_LIBELF_LIBELF_H})
endif()

find_library(HAVE_LIBFTDI ftdi)
find_library(HAVE_LIBFTDI1 ftdi1)
find_path(FTDI_INCLUDE_DIR ftdi.h)
if (FTDI_INCLUDE_DIR)
    include_directories(${FTDI_INCLUDE_DIR})

    set(CMAKE_REQUIRED_INCLUDES ${FTDI_INCLUDE_DIR})
    check_cxx_source_compiles("
    #include <ftdi.h>
    int main() {
        return TYPE_232H;
    }
    " HAVE_LIBFTDI_TYPE_232H)

else()
    set(HAVE_LIBFTDI_TYPE_232H NO)
endif()


find_library(HAVE_LIBHID hid)

find_library(HAVE_LIBNCURSES ncurses)

find_library(HAVE_LIBREADLINE readline)

find_library(HAVE_LIBTERMCAP termcap)

find_library(HAVE_LIBUSB_1_0 usb-1.0)
find_path(HAVE_LIBUSB_1_0_LIBUSB_H libusb-1.0/libusb.h)
if (HAVE_LIBUSB_1_0_LIBUSB_H)
    include_directories(${HAVE_LIBUSB_1_0_LIBUSB_H})
endif()

find_library(HAVE_LIBUSB usb)
find_path(HAVE_LIBUSB_H libusb.h)
if(HAVE_LIBUSB_H)
    include_directories(${HAVE_LIBUSB_H})
endif()

check_include_files(limits.h HAVE_LIMITS_H)

option(HAVE_LINUXGPIO "Enable Linux GPIO support" OFF)

find_path(HAVE_LUSB0_USB_H lusb0_usb.h)
if(HAVE_LUSB0_USB_H)
    include_directories(${HAVE_LUSB0_USB_H})
endif()

check_include_files(memory.h HAVE_MEMORY_H)

check_symbol_exists(memset string.h HAVE_MEMSET)

option(HAVE_PARPORT "Enable Linux Parallel port support" OFF)

find_path(HAVE_PTHREAD_H pthread.h)
if(HAVE_PTHREAD_H)
    include_directories(${HAVE_PTHREAD_H})
endif()

check_symbol_exists(select sys/select.h HAVE_SELECT)

check_include_files(stdint.h HAVE_STDINT_H)

check_include_files(stdlib.h HAVE_STDLIB_H)

check_symbol_exists(strcasecmp strings.h HAVE_STRCASECMP)

check_symbol_exists(strdup string.h HAVE_STRDUP)

check_symbol_exists(strerror stdio.h HAVE_STRERROR)

check_include_files(strings.h HAVE_STRINGS_H)

check_include_files(string.h HAVE_STRING_H)

check_symbol_exists(strncasecmp strings.h HAVE_STRNCASECMP)

check_symbol_exists(strtol stdlib.h HAVE_STRTOL)

check_symbol_exists(strtoul stdlib.h HAVE_STRTOUL)

check_include_files(sys/ioctl.h HAVE_SYS_IOCTL_H)

check_include_files(sys/stat.h HAVE_SYS_STAT_H)

check_include_files(sys/time.h HAVE_SYS_TIME_H)

check_include_files(sys/types.h HAVE_SYS_TYPES_H)

check_include_files(termios.h HAVE_TERMIOS_H)

check_type_size(uint_t UINT_T)

check_type_size(ulong_t ULONG_T)

check_include_files(unistd.h HAVE_UNISTD_H)
set(YY_NO_UNISTD_H HAVE_UNISTD_H)

find_path(HAVE_USB_H usb.h)
if(HAVE_USB_H)
    include_directories(${HAVE_USB_H})
endif()

check_symbol_exists(usleep unistd.h HAVE_USLEEP)

set(PACKAGE "avrdude")
set(PACKAGE_NAME "${PACKAGE}")
set(BUG_REPORT_EMAIL "")
set(VERSION "6.3")
set(PACKAGE_STRING "${PACKAGE}-${VERSION}")
set(PACKAGE_VERSION "${VERSION}")

configure_file(cmakeconfig.hpp.in ac_cfg.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(FLEX)
find_package(BISON)

Bison_Target(config_gram config_gram.y ${CMAKE_CURRENT_BINARY_DIR}/config_gram.c)
Flex_Target(lexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)
Add_Flex_Bison_Dependency(lexer config_gram)

add_library(avrdude STATIC ${LIB_SOURCE_FILES}
        ${BISON_config_gram_OUTPUTS}
        ${FLEX_lexer_OUTPUTS})

#add_executable(avrdude-bin ${EXE_SOURCE_FILES})
#target_link_libraries(avrdude-bin avrdude)

if(HAVE_LIBELF)
    target_link_libraries(avrdude ${HAVE_LIBELF})
endif()

if(HAVE_LIBFTDI AND NOT HAVE_LIBFTDI1)
    target_link_libraries(avrdude ${HAVE_LIBFTDI})
elseif(HAVE_LIBFTDI1)
    target_link_libraries(avrdude ${HAVE_LIBFTDI1})
endif()

if(HAVE_LIBHID)
    target_link_libraries(avrdude ${HAVE_LIBHID})
endif()

if(HAVE_LIBNCURSES)
    target_link_libraries(avrdude ${HAVE_LIBNCURSES})
endif()

if(HAVE_LIBREADLINE)
    target_link_libraries(avrdude ${HAVE_LIBREADLINE})
endif()

if(HAVE_LIBTERMCAP)
    target_link_libraries(avrdude ${HAVE_LIBTERMCAP})
endif()

if(HAVE_LIBUSB)
    target_link_libraries(avrdude ${HAVE_LIBUSB})
endif()

if(HAVE_LIBUSB_1_0)
    target_link_libraries(avrdude ${HAVE_LIBUSB_1_0})
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(avrdude ws2_32)
endif()
