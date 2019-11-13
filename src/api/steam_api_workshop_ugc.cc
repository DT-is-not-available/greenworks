
#include "nan.h"
#include "steam/steam_api.h"
#include "v8.h"

#include "greenworks_async_workers.h"
#include "steam_api_registry.h"

namespace greenworks {
namespace api {
namespace {


NAN_METHOD(CreateItem) {
    Nan::HandleScope scope;

    if (info.Length() < 2 || !info[1]->IsFunction()) {
        THROW_BAD_ARGS("Bad arguments");
    }

    if (!info[0]/*->ToLocalChecked()*/->IsInt32()) {
        THROW_BAD_ARGS("First argument must be 32 bit integer app_id");
    }

    auto app_id = info[0]/*->ToLocalChecked()*/->Int32Value();

    Nan::Callback* success_callback = new Nan::Callback(info[1].As<v8::Function>());
    Nan::Callback* error_callback = nullptr;

    if (info.Length() > 2 && info[2]->IsFunction())
        error_callback = new Nan::Callback(info[2].As<v8::Function>());
    Nan::AsyncQueueWorker(new greenworks::ItemCreatorWorker(
        success_callback, error_callback, app_id));
    info.GetReturnValue().Set(Nan::Undefined());
}

void RegisterAPIs(v8::Local<v8::Object> target) {
  SET_FUNCTION("_CreateItem", CreateItem);
}

SteamAPIRegistry::Add X(RegisterAPIs);

}  // namespace
}  // namespace api
}  // namespace greenworks
