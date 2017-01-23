//
// Flasher_wrap
// brewtroller-flasher
//
// Created by Eric Yanush on 2017-01-22.
//

#ifndef BREWTROLLER_FLASHER_FLASHER_WRAP_HPP
#define BREWTROLLER_FLASHER_FLASHER_WRAP_HPP

#include <nan.h>
#include "Flasher.hpp"

class FlasherWrap : public Nan::ObjectWrap {
public:
    static void Init(v8::Local<v8::Object> exports);
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);

private:

    FlasherWrap();
    ~FlasherWrap();

    Flasher* flasher;
    static Nan::Persistent<v8::Function> constructor;

    static void Flash(const Nan::FunctionCallbackInfo<v8::Value>& info);

    static void LoadConfigFile(const Nan::FunctionCallbackInfo<v8::Value>& info);

    static void GetStringProp(v8::Local<v8::String> property,
                              const Nan::PropertyCallbackInfo<v8::Value>& info);
    static void SetStringProp(v8::Local<v8::String> property,
                              v8::Local<v8::Value> value,
                              const Nan::PropertyCallbackInfo<void>& info);

    static void GetBoolProp(v8::Local<v8::String> property,
                            const Nan::PropertyCallbackInfo<v8::Value>& info);
    static void SetBoolProp(v8::Local<v8::String> property,
                            v8::Local<v8::Value> value,
                            const Nan::PropertyCallbackInfo<void>& info);

    static void GetUintProp(v8::Local<v8::String> property,
                            const Nan::PropertyCallbackInfo<v8::Value>& info);
    static void SetUintProp(v8::Local<v8::String> property,
                            v8::Local<v8::Value> value,
                            const Nan::PropertyCallbackInfo<void>& info);


    static void GetLogMessages(const Nan::FunctionCallbackInfo<v8::Value>& info);

    static void FlashJobRunner(uv_work_t *request);
    static void FlashJobComplete(uv_work_t *request, int status);
};


#endif //BREWTROLLER_FLASHER_FLASHER_WRAP_HPP
