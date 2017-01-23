//
// Scanner_wrap
// brewtroller-flasher
//
// Created by Eric Yanush on 2017-01-22.
//

#ifndef BREWTROLLER_FLASHER_SCANNER_WRAP_HPP
#define BREWTROLLER_FLASHER_SCANNER_WRAP_HPP

#include <nan.h>
#include "Scanner.hpp"

class BrewTrollerInfoWrap : public Nan::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static v8::Local<v8::Object> New(BrewTrollerInfo info);

private:

    static Nan::Persistent<v8::Function> constructor;

    BrewTrollerInfo btInfo;

    static void GetVersion(v8::Local<v8::String> property,
                           const Nan::PropertyCallbackInfo<v8::Value>& info);
    static void GetUseMetric(v8::Local<v8::String> property,
                             const Nan::PropertyCallbackInfo<v8::Value>& info);
    static void GetPositiveID(v8::Local<v8::String> property,
                              const Nan::PropertyCallbackInfo<v8::Value>& info);
};

class PortWrap : public Nan::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static v8::Local<v8::Object> New(Port port);

private:

    static Nan::Persistent<v8::Function> constructor;

    Port port;

    static void GetBTInfo(v8::Local<v8::String> property,
                   const Nan::PropertyCallbackInfo<v8::Value>& info);
    static void GetName(v8::Local<v8::String> property,
                 const Nan::PropertyCallbackInfo<v8::Value>& info);
};

class ScannerWrap : public Nan::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);

private:

    static Nan::Persistent<v8::Function> constructor;

    static void EnumeratePorts(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void EnumerateJobRunner(uv_work_t *request);
    static void EnumerateJobComplete(uv_work_t *request, int status);
};



#endif //BREWTROLLER_FLASHER_SCANNER_WRAP_HPP
