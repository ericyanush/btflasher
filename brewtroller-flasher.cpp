//
// brewtroller
// brewtroller-flasher
//
// Created by Eric Yanush on 2017-01-22.
//

#include <nan.h>
#include "Flasher_wrap.hpp"
#include "Scanner_wrap.hpp"

void InitAll(v8::Local<v8::Object> exports) {
    FlasherWrap::Init(exports);
    BrewTrollerInfoWrap::Init(exports);
    PortWrap::Init(exports);
    ScannerWrap::Init(exports);
}

NODE_MODULE(btflasher, InitAll)