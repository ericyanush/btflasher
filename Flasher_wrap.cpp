//
// Flasher_wrap
// brewtroller-flasher
//
// Created by Eric Yanush on 2017-01-22.
//

#include "Flasher_wrap.hpp"

Nan::Persistent<v8::Function> FlasherWrap::constructor;

namespace FlasherProp {
    static const std::string flashMethod = "flash";
    static const std::string loadConfigMethod = "loadConfigFile";
    static const std::string getLogMessages = "getLogMessages";

    static const std::string programmer = "programmer";
    static const std::string hexFile = "hexFile";
    static const std::string partname = "partname";
    static const std::string serialport = "serialportName";
    static const std::string serialbaud = "serialBaudRate";
    static const std::string signatureCheck = "signatureCheck";
    static const std::string verifyWrites = "verifyWrites";
};

FlasherWrap::FlasherWrap() {
    flasher = new Flasher();
}

FlasherWrap::~FlasherWrap() {
    delete flasher;
}

void FlasherWrap::Init(v8::Local <v8::Object> exports) {
    Nan::HandleScope scope;

    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(FlasherWrap::New);
    tpl->SetClassName(Nan::New("Flasher").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Setup Methods
    Nan::SetPrototypeMethod(tpl, FlasherProp::flashMethod.c_str(), FlasherWrap::Flash);
    Nan::SetPrototypeMethod(tpl, FlasherProp::loadConfigMethod.c_str(), FlasherWrap::LoadConfigFile);
    Nan::SetPrototypeMethod(tpl, FlasherProp::getLogMessages.c_str(), FlasherWrap::GetLogMessages);

    v8::Local<v8::ObjectTemplate> otl = tpl->InstanceTemplate();
    // Setup Properties
    Nan::SetAccessor(otl, Nan::New(FlasherProp::programmer).ToLocalChecked(),
                     FlasherWrap::GetStringProp, FlasherWrap::SetStringProp);
    Nan::SetAccessor(otl, Nan::New(FlasherProp::hexFile).ToLocalChecked(),
                     FlasherWrap::GetStringProp, FlasherWrap::SetStringProp);
    Nan::SetAccessor(otl, Nan::New(FlasherProp::partname).ToLocalChecked(),
                     FlasherWrap::GetStringProp, FlasherWrap::SetStringProp);
    Nan::SetAccessor(otl, Nan::New(FlasherProp::serialport).ToLocalChecked(),
                     FlasherWrap::GetStringProp, FlasherWrap::SetStringProp);
    Nan::SetAccessor(otl, Nan::New(FlasherProp::serialbaud).ToLocalChecked(),
                     FlasherWrap::GetUintProp, FlasherWrap::SetUintProp);
    Nan::SetAccessor(otl, Nan::New(FlasherProp::signatureCheck).ToLocalChecked(),
                     FlasherWrap::GetBoolProp, FlasherWrap::SetBoolProp);
    Nan::SetAccessor(otl, Nan::New(FlasherProp::verifyWrites).ToLocalChecked(),
                     FlasherWrap::GetBoolProp, FlasherWrap::SetBoolProp);

    constructor.Reset(tpl->GetFunction());
    exports->Set(Nan::New("Flasher").ToLocalChecked(), tpl->GetFunction());
}

void FlasherWrap::New(const Nan::FunctionCallbackInfo<v8::Value> &args) {
    if (args.IsConstructCall()) {
        FlasherWrap* obj = new FlasherWrap();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    else {
        v8::Local<v8::Function> cons = Nan::New(constructor);
        args.GetReturnValue().Set(cons->NewInstance(0, nullptr));
    }
}

void FlasherWrap::LoadConfigFile(const Nan::FunctionCallbackInfo<v8::Value> &info) {
    Nan::HandleScope scope;

    if (info.Length() != 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsString()) {
        Nan::ThrowTypeError("Filename is not a String");
        return;
    }

    v8::String::Utf8Value s(info[0]->ToString());
    std::string filename(*s);

    FlasherWrap* wrapper = Nan::ObjectWrap::Unwrap<FlasherWrap>(info.Holder());
    bool result = wrapper->flasher->loadConfigFile(filename);

    info.GetReturnValue().Set(Nan::New(result));
}

void FlasherWrap::GetStringProp(v8::Local <v8::String> property,
                                const Nan::PropertyCallbackInfo<v8::Value> &info) {
    FlasherWrap* wrapper = Nan::ObjectWrap::Unwrap<FlasherWrap>(info.Holder());

    v8::String::Utf8Value v(property);
    std::string propertyName(*v);

    std::string retVal;
    if (propertyName == FlasherProp::programmer) {
        retVal = wrapper->flasher->programmer();
    }
    else if (propertyName == FlasherProp::hexFile) {
        retVal = wrapper->flasher->hexFileName();
    }
    else if (propertyName == FlasherProp::partname) {
        retVal = wrapper->flasher->partName();
    }
    else if (propertyName == FlasherProp::serialport) {
        retVal = wrapper->flasher->serialPortName();
    }

    info.GetReturnValue().Set(Nan::New(retVal).ToLocalChecked());
}

void FlasherWrap::SetStringProp(v8::Local <v8::String> property, v8::Local <v8::Value> value,
                                const Nan::PropertyCallbackInfo<void> &info) {
    FlasherWrap* wrapper = Nan::ObjectWrap::Unwrap<FlasherWrap>(info.Holder());

    v8::String::Utf8Value s(property);
    std::string targetProp(*s);

    if (!value->IsString()) {
        Nan::ThrowTypeError("New Value is Not a String");
        return;
    }

    v8::String::Utf8Value pv(value->ToString());
    std::string newValue(*pv);

    if (targetProp == FlasherProp::programmer) {
        wrapper->flasher->programmer(newValue);
    }
    else if (targetProp == FlasherProp::hexFile) {
        wrapper->flasher->hexFileName(newValue);
    }
    else if (targetProp == FlasherProp::partname) {
        wrapper->flasher->partName(newValue);
    }
    else if (targetProp == FlasherProp::serialport) {
        wrapper->flasher->serialPortName(newValue);
    }
}

void FlasherWrap::GetBoolProp(v8::Local <v8::String> property,
                              const Nan::PropertyCallbackInfo<v8::Value> &info) {
    FlasherWrap* wrapper = Nan::ObjectWrap::Unwrap<FlasherWrap>(info.Holder());

    v8::String::Utf8Value v(property);
    std::string propertyName(*v);

    bool retVal;
    if (propertyName == FlasherProp::signatureCheck) {
        retVal = wrapper->flasher->signatureCheck();
    }
    else if (propertyName == FlasherProp::verifyWrites) {
        retVal = wrapper->flasher->verifyWrites();
    }

    info.GetReturnValue().Set(Nan::New(retVal));
}

void FlasherWrap::SetBoolProp(v8::Local <v8::String> property, v8::Local <v8::Value> value,
                              const Nan::PropertyCallbackInfo<void> &info) {
    FlasherWrap* wrapper = Nan::ObjectWrap::Unwrap<FlasherWrap>(info.Holder());

    v8::String::Utf8Value s(property);
    std::string targetProp(*s);

    if (!value->IsBoolean()) {
        Nan::ThrowTypeError("New Value is Not a Bool");
        return;
    }

    bool newValue = value->BooleanValue();

    if (targetProp == FlasherProp::signatureCheck) {
        wrapper->flasher->signatureCheck(newValue);
    }
    else if (targetProp == FlasherProp::verifyWrites) {
        wrapper->flasher->verifyWrites(newValue);
    }
}

void FlasherWrap::GetUintProp(v8::Local <v8::String> property,
                              const Nan::PropertyCallbackInfo<v8::Value> &info) {
    FlasherWrap* wrapper = Nan::ObjectWrap::Unwrap<FlasherWrap>(info.Holder());

    v8::String::Utf8Value v(property);
    std::string propertyName(*v);

    uint32_t retVal;
    if (propertyName == FlasherProp::serialbaud) {
        retVal = wrapper->flasher->serialBaudRate();
    }

    info.GetReturnValue().Set(Nan::New(retVal));
}

void FlasherWrap::SetUintProp(v8::Local <v8::String> property, v8::Local <v8::Value> value,
                              const Nan::PropertyCallbackInfo<void> &info) {
    FlasherWrap* wrapper = Nan::ObjectWrap::Unwrap<FlasherWrap>(info.Holder());

    v8::String::Utf8Value s(property);
    std::string targetProp(*s);

    if (!value->IsNumber()) {
        Nan::ThrowTypeError("New Value is Not a Number");
        return;
    }

    uint32_t  newValue = value->Uint32Value();

    if (targetProp == FlasherProp::serialbaud) {
        wrapper->flasher->serialBaudRate(newValue);
    }
}

void FlasherWrap::GetLogMessages(const Nan::FunctionCallbackInfo<v8::Value> &info) {
    FlasherWrap* wrapper = Nan::ObjectWrap::Unwrap<FlasherWrap>(info.Holder());

    auto messages = wrapper->flasher->logMessages();

    v8::Local<v8::Array> results = Nan::New<v8::Array>(messages.size());

    for (uint32_t i = 0; i < messages.size(); i++) {
        results->Set(i, Nan::New(messages[i]).ToLocalChecked());
    }

    info.GetReturnValue().Set(results);
}

struct FlashJob {
    uv_work_t request;
    Nan::Persistent<v8::Function> callback;
    Flasher* flasher;
};

void FlasherWrap::Flash(const Nan::FunctionCallbackInfo<v8::Value> &info) {
    Nan::HandleScope scope;

    FlasherWrap* wrapper = Nan::ObjectWrap::Unwrap<FlasherWrap>(info.Holder());

    if (info.Length() != 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsFunction()) {
        Nan::ThrowTypeError("Callback is not a function");
        return;
    }

    FlashJob* job = new FlashJob();
    job->request.data = job;
    job->flasher = wrapper->flasher;

    v8::Local<v8::Function> callback = info[0].As<v8::Function>();
    job->callback.Reset(callback);

    uv_queue_work(uv_default_loop(), &job->request, FlashJobRunner, FlashJobComplete);

    info.GetReturnValue().Set(Nan::Undefined());
}

void FlasherWrap::FlashJobRunner(uv_work_t *request) {
    FlashJob* job = static_cast<FlashJob*>(request->data);

    std::function<void(int, bool, bool)> progressHandler = [job] (int percent, bool done, bool success) {
        v8::Local<v8::Value> argv[] = { Nan::New(percent), Nan::New(done), Nan::New(success) };

        v8::Local<v8::Function> cb = Nan::New(job->callback);
        Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, 1, argv);
    };

    job->flasher->progressCallback(progressHandler);

    job->flasher->flash();
}

void FlasherWrap::FlashJobComplete(uv_work_t *request, int status) {
    Nan::HandleScope scope;

    FlashJob* job = static_cast<FlashJob*>(request->data);

    job->callback.Reset();

    delete job;
}