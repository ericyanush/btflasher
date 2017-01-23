//
// Scanner_wrap
// brewtroller-flasher
//
// Created by Eric Yanush on 2017-01-22.
//

#include "Scanner_wrap.hpp"

Nan::Persistent<v8::Function> BrewTrollerInfoWrap::constructor;

void BrewTrollerInfoWrap::Init(v8::Local <v8::Object> exports) {
    Nan::HandleScope scope;

    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(BrewTrollerInfoWrap::New);
    tpl->SetClassName(Nan::New("BrewTrollerInfo").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    v8::Local<v8::ObjectTemplate> otl = tpl->InstanceTemplate();

    // Setup Properties
    Nan::SetAccessor(otl, Nan::New("version").ToLocalChecked(), BrewTrollerInfoWrap::GetVersion);
    Nan::SetAccessor(otl, Nan::New("usesMetric").ToLocalChecked(), BrewTrollerInfoWrap::GetUseMetric);
    Nan::SetAccessor(otl, Nan::New("positiveID").ToLocalChecked(), BrewTrollerInfoWrap::GetPositiveID);

    constructor.Reset(tpl->GetFunction());
    exports->Set(Nan::New("BrewTrollerInfo").ToLocalChecked(), tpl->GetFunction());
}

void BrewTrollerInfoWrap::New(const Nan::FunctionCallbackInfo<v8::Value> &args) {
    if (args.IsConstructCall()) {
        BrewTrollerInfoWrap* obj = new BrewTrollerInfoWrap;
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    else {
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
        args.GetReturnValue().Set(cons->NewInstance());
    }
}

v8::Local<v8::Object> BrewTrollerInfoWrap::New(BrewTrollerInfo info) {
    Nan::EscapableHandleScope escapableScope;
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    auto obj = cons->NewInstance();
    auto infoWrap = BrewTrollerInfoWrap::Unwrap<BrewTrollerInfoWrap>(obj);
    infoWrap->btInfo = info;

    return escapableScope.Escape(obj);
}


void BrewTrollerInfoWrap::GetVersion(v8::Local <v8::String> property,
                                     const Nan::PropertyCallbackInfo<v8::Value> &info) {
    BrewTrollerInfoWrap* wrapper = Nan::ObjectWrap::Unwrap<BrewTrollerInfoWrap>(info.Holder());
    info.GetReturnValue().Set(Nan::New(wrapper->btInfo.version).ToLocalChecked());
}

void BrewTrollerInfoWrap::GetUseMetric(v8::Local <v8::String> property,
                                       const Nan::PropertyCallbackInfo<v8::Value> &info) {
    BrewTrollerInfoWrap* wrapper = Nan::ObjectWrap::Unwrap<BrewTrollerInfoWrap>(info.Holder());
    info.GetReturnValue().Set(Nan::New(wrapper->btInfo.usesMetric));
}

void BrewTrollerInfoWrap::GetPositiveID(v8::Local <v8::String> property,
                                        const Nan::PropertyCallbackInfo<v8::Value> &info) {
    BrewTrollerInfoWrap* wrapper = Nan::ObjectWrap::Unwrap<BrewTrollerInfoWrap>(info.Holder());
    info.GetReturnValue().Set(Nan::New(wrapper->btInfo.positiveID));
}

Nan::Persistent<v8::Function> PortWrap::constructor;

void PortWrap::Init(v8::Local <v8::Object> exports) {
    Nan::HandleScope scope;

    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(PortWrap::New);
    tpl->SetClassName(Nan::New("Port").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    v8::Local<v8::ObjectTemplate> otl = tpl->InstanceTemplate();

    // Setup Properties
    Nan::SetAccessor(otl, Nan::New("name").ToLocalChecked(), PortWrap::GetName);
    Nan::SetAccessor(otl, Nan::New("btInfo").ToLocalChecked(), PortWrap::GetBTInfo);

    constructor.Reset(tpl->GetFunction());
    exports->Set(Nan::New("Port").ToLocalChecked(), tpl->GetFunction());
}

void PortWrap::New(const Nan::FunctionCallbackInfo<v8::Value> &args) {
    if (args.IsConstructCall()) {
        PortWrap* obj = new PortWrap;
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    else {
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
        args.GetReturnValue().Set(cons->NewInstance());
    }
}

v8::Local<v8::Object> PortWrap::New(Port port) {
    Nan::EscapableHandleScope escapableScope;
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    auto obj = cons->NewInstance();
    auto portWrap = PortWrap::Unwrap<PortWrap>(obj);
    portWrap->port = port;

    return escapableScope.Escape(obj);
}

void PortWrap::GetBTInfo(v8::Local<v8::String> property,
                         const Nan::PropertyCallbackInfo<v8::Value>& info) {
    PortWrap* wrapper = Nan::ObjectWrap::Unwrap<PortWrap>(info.Holder());

    v8::Local<v8::Object> btInfo = BrewTrollerInfoWrap::New(wrapper->port.btInfo);

    info.GetReturnValue().Set(btInfo);
}

void PortWrap::GetName(v8::Local <v8::String> property,
                       const Nan::PropertyCallbackInfo<v8::Value> &info) {
    PortWrap* wrapper = Nan::ObjectWrap::Unwrap<PortWrap>(info.Holder());

    info.GetReturnValue().Set(Nan::New(wrapper->port.name).ToLocalChecked());
}

Nan::Persistent<v8::Function> ScannerWrap::constructor;

void ScannerWrap::Init(v8::Local <v8::Object> exports) {
    Nan::HandleScope scope;

    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(ScannerWrap::New);
    tpl->SetClassName(Nan::New("Scanner").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Setup methods
    Nan::SetPrototypeMethod(tpl, "enumeratePorts", ScannerWrap::EnumeratePorts);

    constructor.Reset(tpl->GetFunction());
    exports->Set(Nan::New("Scanner").ToLocalChecked(), tpl->GetFunction());
}

void ScannerWrap::New(const Nan::FunctionCallbackInfo<v8::Value> &args) {
    if (args.IsConstructCall()) {
        ScannerWrap* obj = new ScannerWrap;
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    else {
        v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
        args.GetReturnValue().Set(cons->NewInstance());
    }
}

struct EnumerateJob {
    uv_work_t request;
    Nan::Persistent<v8::Function> callback;
    std::vector<Port> discovered_ports;
};

void ScannerWrap::EnumeratePorts(const Nan::FunctionCallbackInfo<v8::Value> &info) {
    Nan::HandleScope scope;

    if (info.Length() != 1) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsFunction()) {
        Nan::ThrowTypeError("Callback is not a function");
        return;
    }

    EnumerateJob* job = new EnumerateJob();
    job->request.data = job;

    v8::Local<v8::Function> callback = info[0].As<v8::Function>();
    job->callback.Reset(callback);

    uv_queue_work(uv_default_loop(), &job->request, EnumerateJobRunner, EnumerateJobComplete);

    info.GetReturnValue().Set(Nan::Undefined());
}

void ScannerWrap::EnumerateJobRunner(uv_work_t *request) {
    EnumerateJob* job = static_cast<EnumerateJob*>(request->data);

    auto ports = Scanner::enumerate_serial_ports();

    job->discovered_ports = ports;
}

void ScannerWrap::EnumerateJobComplete(uv_work_t *request, int status) {
    Nan::HandleScope scope;

    EnumerateJob* job = static_cast<EnumerateJob*>(request->data);

    v8::Local<v8::Array> results = Nan::New<v8::Array>(job->discovered_ports.size());

    for (uint32_t i = 0; i < job->discovered_ports.size(); i++) {
        v8::Local<v8::Object> currPort = PortWrap::New(job->discovered_ports[i]);
        results->Set(i, currPort);
    }

    v8::Local<v8::Value> argv[] = { results };

    v8::Local<v8::Function> cb = Nan::New(job->callback);
    Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, 1, argv);

    job->callback.Reset();

    delete job;
}