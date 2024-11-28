// Copyright (c) 2016 Greenheart Games Pty. Ltd. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "nan.h"
#include "steam/steam_api.h"
#include "v8.h"

#include "greenworks_async_workers.h"
#include "steam_api_registry.h"

namespace greenworks {
namespace api {
namespace {

void InitUgcMatchingTypes(v8::Local<v8::Object> exports) {
  v8::Local<v8::Object> ugc_matching_type = Nan::New<v8::Object>();
  SET_TYPE(ugc_matching_type, "Items", k_EUGCMatchingUGCType_Items);
  SET_TYPE(ugc_matching_type, "ItemsMtx", k_EUGCMatchingUGCType_Items_Mtx);
  SET_TYPE(ugc_matching_type, "ItemsReadyToUse",
           k_EUGCMatchingUGCType_Items_ReadyToUse);
  SET_TYPE(ugc_matching_type, "Collections", k_EUGCMatchingUGCType_Collections);
  SET_TYPE(ugc_matching_type, "Artwork", k_EUGCMatchingUGCType_Artwork);
  SET_TYPE(ugc_matching_type, "Videos", k_EUGCMatchingUGCType_Videos);
  SET_TYPE(ugc_matching_type, "Screenshots", k_EUGCMatchingUGCType_Screenshots);
  SET_TYPE(ugc_matching_type, "AllGuides", k_EUGCMatchingUGCType_AllGuides);
  SET_TYPE(ugc_matching_type, "WebGuides", k_EUGCMatchingUGCType_WebGuides);
  SET_TYPE(ugc_matching_type, "IntegratedGuides",
           k_EUGCMatchingUGCType_IntegratedGuides);
  SET_TYPE(ugc_matching_type, "UsableInGame",
           k_EUGCMatchingUGCType_UsableInGame);
  SET_TYPE(ugc_matching_type, "ControllerBindings",
           k_EUGCMatchingUGCType_ControllerBindings);
  Nan::Persistent<v8::Object> constructor;
  constructor.Reset(ugc_matching_type);
  Nan::Set(exports,
           Nan::New("UGCMatchingType").ToLocalChecked(),
           ugc_matching_type);
}

void InitUgcQueryTypes(v8::Local<v8::Object> exports) {
  v8::Local<v8::Object> ugc_query_type = Nan::New<v8::Object>();
  SET_TYPE(ugc_query_type, "RankedByVote", k_EUGCQuery_RankedByVote);
  SET_TYPE(ugc_query_type, "RankedByPublicationDate",
           k_EUGCQuery_RankedByPublicationDate);
  SET_TYPE(ugc_query_type, "AcceptedForGameRankedByAcceptanceDate",
           k_EUGCQuery_AcceptedForGameRankedByAcceptanceDate);
  SET_TYPE(ugc_query_type, "RankedByTrend", k_EUGCQuery_RankedByTrend);
  SET_TYPE(ugc_query_type, "FavoritedByFriendsRankedByPublicationDate",
           k_EUGCQuery_FavoritedByFriendsRankedByPublicationDate);
  SET_TYPE(ugc_query_type, "CreatedByFriendsRankedByPublicationDate",
           k_EUGCQuery_CreatedByFriendsRankedByPublicationDate);
  SET_TYPE(ugc_query_type, "RankedByNumTimesReported",
           k_EUGCQuery_RankedByNumTimesReported);
  SET_TYPE(ugc_query_type, "CreatedByFollowedUsersRankedByPublicationDate",
           k_EUGCQuery_CreatedByFollowedUsersRankedByPublicationDate);
  SET_TYPE(ugc_query_type, "NotYetRated",  k_EUGCQuery_NotYetRated);
  SET_TYPE(ugc_query_type, "RankedByTotalVotesAsc",
           k_EUGCQuery_RankedByTotalVotesAsc);
  SET_TYPE(ugc_query_type, "RankedByVotesUp", k_EUGCQuery_RankedByVotesUp);
  SET_TYPE(ugc_query_type, "RankedByTextSearch",
           k_EUGCQuery_RankedByTextSearch);
  Nan::Persistent<v8::Object> constructor;
  constructor.Reset(ugc_query_type);
  Nan::Set(exports,
           Nan::New("UGCQueryType").ToLocalChecked(),
           ugc_query_type);
}

void InitUserUgcList(v8::Local<v8::Object> exports) {
  v8::Local<v8::Object> ugc_list = Nan::New<v8::Object>();
  SET_TYPE(ugc_list, "Published", k_EUserUGCList_Published);
  SET_TYPE(ugc_list, "VotedOn", k_EUserUGCList_VotedOn);
  SET_TYPE(ugc_list, "VotedUp", k_EUserUGCList_VotedUp);
  SET_TYPE(ugc_list, "VotedDown", k_EUserUGCList_VotedDown);
  SET_TYPE(ugc_list, "WillVoteLater", k_EUserUGCList_WillVoteLater);
  SET_TYPE(ugc_list, "Favorited", k_EUserUGCList_Favorited);
  SET_TYPE(ugc_list, "Subscribed", k_EUserUGCList_Subscribed);
  SET_TYPE(ugc_list, "UsedOrPlayer", k_EUserUGCList_UsedOrPlayed);
  SET_TYPE(ugc_list, "Followed", k_EUserUGCList_Followed);
  Nan::Persistent<v8::Object> constructor;
  constructor.Reset(ugc_list);
  Nan::Set(exports, Nan::New("UserUGCList").ToLocalChecked(), ugc_list);
}

void InitUserUgcListSortOrder(v8::Local<v8::Object> exports) {
  v8::Local<v8::Object> ugc_list_sort_order = Nan::New<v8::Object>();
  SET_TYPE(ugc_list_sort_order, "CreationOrderDesc",
           k_EUserUGCListSortOrder_CreationOrderDesc);
  SET_TYPE(ugc_list_sort_order, "CreationOrderAsc",
           k_EUserUGCListSortOrder_CreationOrderAsc);
  SET_TYPE(ugc_list_sort_order, "TitleAsc", k_EUserUGCListSortOrder_TitleAsc);
  SET_TYPE(ugc_list_sort_order, "LastUpdatedDesc",
           k_EUserUGCListSortOrder_LastUpdatedDesc);
  SET_TYPE(ugc_list_sort_order, "SubscriptionDateDesc",
           k_EUserUGCListSortOrder_SubscriptionDateDesc);
  SET_TYPE(ugc_list_sort_order, "VoteScoreDesc",
           k_EUserUGCListSortOrder_VoteScoreDesc);
  SET_TYPE(ugc_list_sort_order, "ForModeration",
           k_EUserUGCListSortOrder_ForModeration);
  Nan::Persistent<v8::Object> constructor;
  constructor.Reset(ugc_list_sort_order);
  Nan::Set(exports,
           Nan::New("UserUGCListSortOrder").ToLocalChecked(),
           ugc_list_sort_order);
}

NAN_METHOD(FileShare) {
  Nan::HandleScope scope;

  if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
    THROW_BAD_ARGS("Bad arguments");
  }
  std::string file_name(*(v8::String::Utf8Value(info[0])));
  Nan::Callback* success_callback =
      new Nan::Callback(info[1].As<v8::Function>());
  Nan::Callback* error_callback = nullptr;

  if (info.Length() > 2 && info[2]->IsFunction())
    error_callback = new Nan::Callback(info[2].As<v8::Function>());

  Nan::AsyncQueueWorker(new greenworks::FileShareWorker(
      success_callback, error_callback, file_name));
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(PublishWorkshopFile) {
  Nan::HandleScope scope;

  if (info.Length() < 6 || !info[0]->IsObject() || !info[1]->IsString() ||
      !info[2]->IsString() || !info[3]->IsString() || !info[4]->IsString() ||
      !info[5]->IsFunction()) {
    THROW_BAD_ARGS("Bad arguments");
  }
  Nan::MaybeLocal<v8::Object> maybe_opt = Nan::To<v8::Object>(info[0]);
  auto options = maybe_opt.ToLocalChecked();
  auto app_id = Nan::Get(options, Nan::New("app_id").ToLocalChecked());
  auto tags = Nan::Get(options, Nan::New("tags").ToLocalChecked());
  if (!app_id.ToLocalChecked()->IsInt32() ||
      !tags.ToLocalChecked()->IsArray()) {
    THROW_BAD_ARGS(
        "The object parameter must have 'app_id' and 'tags' field.");
  }
  greenworks::WorkshopFileProperties properties;

  v8::Local<v8::Array> tags_array = tags.ToLocalChecked().As<v8::Array>();
  if (tags_array->Length() > greenworks::WorkshopFileProperties::MAX_TAGS) {
    THROW_BAD_ARGS("The length of 'tags' must be less than 100.");
  }
  for (uint32_t i = 0; i < tags_array->Length(); ++i) {
    if (!Nan::Get(tags_array, i).ToLocalChecked()->IsString())
      THROW_BAD_ARGS("Bad arguments");
    v8::String::Utf8Value tag(Nan::Get(tags_array, (i)).ToLocalChecked());
    properties.tags_scratch.push_back(*tag);
    properties.tags[i] = properties.tags_scratch.back().c_str();
  }

  Nan::Callback* success_callback =
      new Nan::Callback(info[5].As<v8::Function>());
  Nan::Callback* error_callback = nullptr;

  if (info.Length() > 6 && info[6]->IsFunction())
    error_callback = new Nan::Callback(info[6].As<v8::Function>());

  properties.file_path = (*(v8::String::Utf8Value(info[1])));
  properties.image_path = (*(v8::String::Utf8Value(info[2])));
  properties.title = (*(v8::String::Utf8Value(info[3])));
  properties.description = (*(v8::String::Utf8Value(info[4])));

  Nan::AsyncQueueWorker(new greenworks::PublishWorkshopFileWorker(
      success_callback, error_callback, app_id.ToLocalChecked()->Int32Value(),
      properties));
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(UpdatePublishedWorkshopFile) {
  Nan::HandleScope scope;

  if (info.Length() < 7 || !info[0]->IsObject() || !info[1]->IsString() ||
      !info[2]->IsString() || !info[3]->IsString() || !info[4]->IsString() ||
      !info[5]->IsString() || !info[6]->IsFunction()) {
    THROW_BAD_ARGS("Bad arguments");
  }
  Nan::MaybeLocal<v8::Object> maybe_opt = Nan::To<v8::Object>(info[0]);
  auto options = maybe_opt.ToLocalChecked();
  auto tags = Nan::Get(options, (Nan::New("tags").ToLocalChecked()));
  if (!tags.ToLocalChecked()->IsArray()) {
    THROW_BAD_ARGS("The object parameter must have 'tags' field.");
  }
  greenworks::WorkshopFileProperties properties;

  v8::Local<v8::Array> tags_array = tags.ToLocalChecked().As<v8::Array>();
  if (tags_array->Length() > greenworks::WorkshopFileProperties::MAX_TAGS) {
    THROW_BAD_ARGS("The length of 'tags' must be less than 100.");
  }
  for (uint32_t i = 0; i < tags_array->Length(); ++i) {
    if (!Nan::Get(tags_array, i).ToLocalChecked()->IsString())
      THROW_BAD_ARGS("Bad arguments");
    v8::String::Utf8Value tag(Nan::Get(tags_array, (i)).ToLocalChecked());
    properties.tags_scratch.push_back(*tag);
    properties.tags[i] = properties.tags_scratch.back().c_str();
  }
  Nan::Callback* success_callback =
      new Nan::Callback(info[6].As<v8::Function>());
  Nan::Callback* error_callback = nullptr;

  if (info.Length() > 7 && info[7]->IsFunction())
    error_callback = new Nan::Callback(info[7].As<v8::Function>());

  PublishedFileId_t published_file_id = utils::strToUint64(
      *(v8::String::Utf8Value(info[1])));
  properties.file_path = (*(v8::String::Utf8Value(info[2])));
  properties.image_path = (*(v8::String::Utf8Value(info[3])));
  properties.title = (*(v8::String::Utf8Value(info[4])));
  properties.description = (*(v8::String::Utf8Value(info[5])));

  Nan::AsyncQueueWorker(new greenworks::UpdatePublishedWorkshopFileWorker(
      success_callback, error_callback, published_file_id, properties));
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(UGCGetItems) {
  Nan::HandleScope scope;
  if (info.Length() < 4 || !info[0]->IsObject() || !info[1]->IsInt32() ||
      !info[2]->IsInt32() || !info[3]->IsFunction()) {
    THROW_BAD_ARGS("Bad arguments");
  }
  Nan::MaybeLocal<v8::Object> maybe_opt = Nan::To<v8::Object>(info[0]);
  auto options = maybe_opt.ToLocalChecked();
  auto app_id = Nan::Get(options, (Nan::New("app_id").ToLocalChecked()));
  auto page_num = Nan::Get(options, (Nan::New("page_num").ToLocalChecked()));
  if (!app_id.ToLocalChecked()->IsInt32() ||
      !page_num.ToLocalChecked()->IsInt32()) {
    THROW_BAD_ARGS(
        "The object parameter must have 'app_id' and 'page_num' fields.");
  }

  auto ugc_matching_type = static_cast<EUGCMatchingUGCType>(
      info[1]->Int32Value());
  auto ugc_query_type = static_cast<EUGCQuery>(info[2]->Int32Value());

  Nan::Callback* success_callback =
      new Nan::Callback(info[3].As<v8::Function>());
  Nan::Callback* error_callback = nullptr;

  if (info.Length() > 4 && info[4]->IsFunction())
    error_callback = new Nan::Callback(info[4].As<v8::Function>());

  Nan::AsyncQueueWorker(new greenworks::QueryAllUGCWorker(
      success_callback, error_callback, ugc_matching_type, ugc_query_type,
      app_id.ToLocalChecked()->Int32Value(),
      page_num.ToLocalChecked()->Int32Value()));
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(UGCGetUserItems) {
  Nan::HandleScope scope;
  if (info.Length() < 5 || !info[0]->IsObject() || !info[1]->IsInt32() ||
      !info[2]->IsInt32() || !info[3]->IsInt32() || !info[4]->IsFunction()) {
    THROW_BAD_ARGS("Bad arguments");
  }
  Nan::MaybeLocal<v8::Object> maybe_opt = Nan::To<v8::Object>(info[0]);
  auto options = maybe_opt.ToLocalChecked();
  auto app_id = Nan::Get(options, (Nan::New("app_id").ToLocalChecked()));
  auto page_num = Nan::Get(options, (Nan::New("page_num").ToLocalChecked()));
  if (!app_id.ToLocalChecked()->IsInt32() ||
      !page_num.ToLocalChecked()->IsInt32()) {
    THROW_BAD_ARGS(
        "The object parameter must have 'app_id' and 'page_num' fields.");
  }

  auto ugc_matching_type = static_cast<EUGCMatchingUGCType>(
      info[1]->Int32Value());
  auto ugc_list_order = static_cast<EUserUGCListSortOrder>(
      info[2]->Int32Value());
  auto ugc_list = static_cast<EUserUGCList>(info[3]->Int32Value());

  Nan::Callback* success_callback =
      new Nan::Callback(info[4].As<v8::Function>());
  Nan::Callback* error_callback = nullptr;

  if (info.Length() > 5 && info[5]->IsFunction())
    error_callback = new Nan::Callback(info[4].As<v8::Function>());

  Nan::AsyncQueueWorker(new greenworks::QueryUserUGCWorker(
      success_callback, error_callback, ugc_matching_type, ugc_list,
      ugc_list_order, app_id.ToLocalChecked()->Int32Value(),
      page_num.ToLocalChecked()->Int32Value()));
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(UGCDownloadItem) {
  Nan::HandleScope scope;
  if (info.Length() < 3 || !info[0]->IsString() || !info[1]->IsString() ||
      !info[2]->IsFunction()) {
    THROW_BAD_ARGS("Bad arguments");
  }
  UGCHandle_t download_file_handle = utils::strToUint64(
      *(v8::String::Utf8Value(info[0])));
  std::string download_dir = *(v8::String::Utf8Value(info[1]));

  Nan::Callback* success_callback =
      new Nan::Callback(info[2].As<v8::Function>());
  Nan::Callback* error_callback = nullptr;

  if (info.Length() > 3 && info[3]->IsFunction())
    error_callback = new Nan::Callback(info[3].As<v8::Function>());

  Nan::AsyncQueueWorker(new greenworks::DownloadItemWorker(
      success_callback, error_callback, download_file_handle, download_dir));
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(UGCSynchronizeItems) {
  Nan::HandleScope scope;
  if (info.Length() < 3 || !info[0]->IsObject() || !info[1]->IsString() ||
      !info[2]->IsFunction()) {
    THROW_BAD_ARGS("Bad arguments");
  }

  Nan::MaybeLocal<v8::Object> maybe_opt = Nan::To<v8::Object>(info[0]);
  auto options = maybe_opt.ToLocalChecked();
  auto app_id = Nan::Get(options, (Nan::New("app_id").ToLocalChecked()));
  auto page_num = Nan::Get(options, (Nan::New("page_num").ToLocalChecked()));
  if (!app_id.ToLocalChecked()->IsInt32() ||
      !page_num.ToLocalChecked()->IsInt32()) {
    THROW_BAD_ARGS(
        "The object parameter must have 'app_id' and 'page_num' fields.");
  }
  std::string download_dir = *(v8::String::Utf8Value(info[1]));

  Nan::Callback* success_callback =
      new Nan::Callback(info[2].As<v8::Function>());
  Nan::Callback* error_callback = nullptr;

  if (info.Length() > 3 && info[3]->IsFunction())
    error_callback = new Nan::Callback(info[3].As<v8::Function>());

  Nan::AsyncQueueWorker(new greenworks::SynchronizeItemsWorker(
      success_callback, error_callback, download_dir,
      app_id.ToLocalChecked()->Int32Value(),
      page_num.ToLocalChecked()->Int32Value()));
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(UGCShowOverlay) {
  Nan::HandleScope scope;
  std::string steam_store_url;
  if (info.Length() < 1) {
    uint32 appId = SteamUtils()->GetAppID();
    steam_store_url = "http://steamcommunity.com/app/" +
        utils::uint64ToString(appId) + "/workshop/";
  } else {
    if (!info[0]->IsString()) {
      THROW_BAD_ARGS("Bad arguments");
    }
    std::string item_id = *(v8::String::Utf8Value(info[0]));
    steam_store_url = "http://steamcommunity.com/sharedfiles/filedetails/?id="
      + item_id;
  }

  SteamFriends()->ActivateGameOverlayToWebPage(steam_store_url.c_str());
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(UGCUnsubscribe) {
  Nan::HandleScope scope;
  if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
    THROW_BAD_ARGS("Bad arguments");
  }
  PublishedFileId_t unsubscribed_file_id = utils::strToUint64(
      *(v8::String::Utf8Value(info[0])));
  Nan::Callback* success_callback =
      new Nan::Callback(info[1].As<v8::Function>());
  Nan::Callback* error_callback = nullptr;

  if (info.Length() > 2 && info[2]->IsFunction())
    error_callback = new Nan::Callback(info[2].As<v8::Function>());

  Nan::AsyncQueueWorker(new greenworks::UnsubscribePublishedFileWorker(
      success_callback, error_callback, unsubscribed_file_id));
  info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(UGCSubscribe) {
  Nan::HandleScope scope;
  if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
    THROW_BAD_ARGS("Bad arguments");
  }
  PublishedFileId_t subscribed_file_id = utils::strToUint64(
      *(v8::String::Utf8Value(info[0])));
  Nan::Callback* success_callback =
      new Nan::Callback(info[1].As<v8::Function>());
  Nan::Callback* error_callback = nullptr;

  if (info.Length() > 2 && info[2]->IsFunction())
    error_callback = new Nan::Callback(info[2].As<v8::Function>());
  
  Nan::AsyncQueueWorker(new greenworks::SubscribePublishedFileWorker(
      success_callback, error_callback, subscribed_file_id));
  info.GetReturnValue().Set(Nan::Undefined());
}

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

//For some reason passing to the program and back doesn't work, so just _don't do that I guess_
UGCUpdateHandle_t item_update_id_actual_hack;

NAN_METHOD(StartItemUpdate) {
    Nan::HandleScope scope;

    if (info.Length() < 2) {
        THROW_BAD_ARGS("Bad arguments");
    }

    if (!info[0]/*->ToLocalChecked()*/->IsInt32()) {
        THROW_BAD_ARGS("First argument must be 32 bit integer app_id");
    }
    if (!info[1]/*->ToLocalChecked()*/->IsString()) {
        THROW_BAD_ARGS("Second argument must be string item_id");
    }

    auto app_id = info[0]/*->ToLocalChecked()*/->Int32Value();
    UGCUpdateHandle_t item_id = utils::strToUint64(*(v8::String::Utf8Value(info[1])));
    
    auto item_update_id = SteamUGC()->StartItemUpdate(app_id, item_id);
    item_update_id_actual_hack = item_update_id;

    std::string iui = utils::uint64ToString(item_update_id_actual_hack);
    info.GetReturnValue().Set(Nan::New(iui.c_str()).ToLocalChecked());
}

NAN_METHOD(SetItemContent) {
    Nan::HandleScope scope;

    if (info.Length() < 2) {
        THROW_BAD_ARGS("Bad arguments");
    }

    if (!info[0]/*->ToLocalChecked()*/->IsString()) {
        THROW_BAD_ARGS("First argument must be string update id");
    }
    if (!info[1]/*->ToLocalChecked()*/->IsString()) {
        THROW_BAD_ARGS("Second argument must be string");
    }

    UGCUpdateHandle_t item_id = utils::strToUint64(*(v8::String::Utf8Value(info[0])));
    auto contentFolder = *(v8::String::Utf8Value(info[1]));

    bool setContentSuccess = SteamUGC()->SetItemContent(item_update_id_actual_hack, contentFolder);

    info.GetReturnValue().Set(Nan::New(setContentSuccess));
}

NAN_METHOD(SetItemPreview) {
    Nan::HandleScope scope;

    if (info.Length() < 2) {
        THROW_BAD_ARGS("Bad arguments");
    }

    if (!info[0]/*->ToLocalChecked()*/->IsString()) {
        THROW_BAD_ARGS("First argument must be string update id");
    }
    if (!info[1]/*->ToLocalChecked()*/->IsString()) {
        THROW_BAD_ARGS("Second argument must be string");
    }

    UGCUpdateHandle_t item_id = utils::strToUint64(*(v8::String::Utf8Value(info[0])));
    auto contentFolder = *(v8::String::Utf8Value(info[1]));

    bool setContentSuccess = SteamUGC()->SetItemPreview(item_update_id_actual_hack, contentFolder);

    info.GetReturnValue().Set(Nan::New(setContentSuccess));
}

NAN_METHOD(GetNumSubscribedItems) {
    info.GetReturnValue().Set(Nan::New(SteamUGC()->GetNumSubscribedItems()));
}

NAN_METHOD(GetSubscribedItems) {
    int sz = SteamUGC()->GetNumSubscribedItems();
    std::vector<PublishedFileId_t> vec(sz);
    sz = SteamUGC()->GetSubscribedItems(vec.data(), sz);

    v8::Local<v8::Array> items = Nan::New<v8::Array>(static_cast<int>(vec.size()));
    for (size_t i = 0; i < vec.size(); ++i)
        Nan::Set(items, i, Nan::New(utils::uint64ToString(vec[i])).ToLocalChecked());

    info.GetReturnValue().Set(items);
}

NAN_METHOD(TryGetItemFolder) {
    PublishedFileId_t item_id = utils::strToUint64(*(v8::String::Utf8Value(info[0])));

    uint32 unItemState = SteamUGC()->GetItemState(item_id);
    if (unItemState & k_EItemStateInstalled)
    {
        // indicates the item is currently installed
        // Try and get the content folder then
        uint64 sizeOnDisk;
        const int size = 260;
        char folder[size];
        uint32 timestamp;
        bool success = SteamUGC()->GetItemInstallInfo(item_id, &sizeOnDisk, folder, size, &timestamp);
        if (success) {
            //Return the folder
            info.GetReturnValue().Set(Nan::New(folder).ToLocalChecked());
        } else
            //Return an empty string
            info.GetReturnValue().Set(Nan::New("").ToLocalChecked());
    }
    else
    {
        // Return empty string if item is not installed
        info.GetReturnValue().Set(Nan::New("").ToLocalChecked());
    }
}

NAN_METHOD(SetItemTags) {
    Nan::HandleScope scope;

    if (info.Length() < 1) {
        THROW_BAD_ARGS("Bad arguments");
    }
    if (!info[0]->IsArray()) {
        THROW_BAD_ARGS("First argument must be string array tags");
    }
    v8::Local<v8::Array> tags = info[0].As<v8::Array>();

    int len = tags->Length();

    SteamParamStringArray_t *pTags = new SteamParamStringArray_t();
    const char* tags_arr[100];
    std::vector<std::string> tags_vec;

    // tags_vec.push_back(*(v8::String::Utf8Value(Nan::Get(tags, (0)).ToLocalChecked())));
    // tags_arr[0] = tags_vec.back().c_str();

    // tags_vec.push_back(*(v8::String::Utf8Value(Nan::Get(tags, (1)).ToLocalChecked())));
    // tags_arr[1] = tags_vec.back().c_str();


    // for (uint32_t i = 0; i < len; ++i) {
    //     tags_vec.push_back(*(v8::String::Utf8Value(Nan::Get(tags, (i)).ToLocalChecked())));
    //     tags_arr[i] = tags_vec.back().c_str();
    // }

    //Yes, I know what a loop is, but somehow nothing worked except this...
    std::string thisTag0;
    std::string thisTag1;
    std::string thisTag2;
    std::string thisTag3;
    std::string thisTag4;
    std::string thisTag5;
    std::string thisTag6;
    std::string thisTag7;
    std::string thisTag8;
    std::string thisTag9;
    
    if (len > 0) {
        thisTag0 = (*(v8::String::Utf8Value(Nan::Get(tags, (0)).ToLocalChecked())));
        tags_arr[0] = thisTag0.c_str();
    }
    if (len > 1) {
        thisTag1 = (*(v8::String::Utf8Value(Nan::Get(tags, (1)).ToLocalChecked())));
        tags_arr[1] = thisTag1.c_str();
    }
    if (len > 2) {
        thisTag2 = (*(v8::String::Utf8Value(Nan::Get(tags, (2)).ToLocalChecked())));
        tags_arr[2] = thisTag2.c_str();
    }
    if (len > 3) {
        thisTag3 = (*(v8::String::Utf8Value(Nan::Get(tags, (3)).ToLocalChecked())));
        tags_arr[3] = thisTag3.c_str();
    }
    if (len > 4) {
        thisTag4 = (*(v8::String::Utf8Value(Nan::Get(tags, (4)).ToLocalChecked())));
        tags_arr[4] = thisTag4.c_str();
    }
    if (len > 5) {
        thisTag5 = (*(v8::String::Utf8Value(Nan::Get(tags, (5)).ToLocalChecked())));
        tags_arr[5] = thisTag5.c_str();
    }
    if (len > 6) {
        thisTag6 = (*(v8::String::Utf8Value(Nan::Get(tags, (6)).ToLocalChecked())));
        tags_arr[6] = thisTag6.c_str();
    }
    if (len > 7) {
        thisTag7 = (*(v8::String::Utf8Value(Nan::Get(tags, (7)).ToLocalChecked())));
        tags_arr[7] = thisTag7.c_str();
    }
    if (len > 8) {
        thisTag8 = (*(v8::String::Utf8Value(Nan::Get(tags, (8)).ToLocalChecked())));
        tags_arr[8] = thisTag8.c_str();
    }
    if (len > 9) {
        thisTag9 = (*(v8::String::Utf8Value(Nan::Get(tags, (9)).ToLocalChecked())));
        tags_arr[9] = thisTag9.c_str(); 
    }
    pTags->m_ppStrings = reinterpret_cast<const char**>(tags_arr);
    pTags->m_nNumStrings = len;
    SteamUGC()->SetItemTags(item_update_id_actual_hack, pTags);
}

NAN_METHOD(SetItemTitle) {
    Nan::HandleScope scope;

    if (info.Length() < 2) {
        THROW_BAD_ARGS("Bad arguments");
    }

    if (!info[0]/*->ToLocalChecked()*/->IsString()) {
        THROW_BAD_ARGS("First argument must be string update id");
    }
    if (!info[1]/*->ToLocalChecked()*/->IsString()) {
        THROW_BAD_ARGS("Second argument must be string");
    }

    UGCUpdateHandle_t item_id = utils::strToUint64(*(v8::String::Utf8Value(info[0])));
    auto contentTitle = *(v8::String::Utf8Value(info[1]));

    bool setTitleSuccess = SteamUGC()->SetItemTitle(item_update_id_actual_hack, contentTitle);

    info.GetReturnValue().Set(Nan::New(setTitleSuccess));
}

NAN_METHOD(SubmitItemUpdate) {
    Nan::HandleScope scope;

    if (info.Length() < 3) {
        THROW_BAD_ARGS("Bad arguments");
    }

    if (!info[0]/*->ToLocalChecked()*/->IsString()) {
        THROW_BAD_ARGS("First argument must be string update id");
    }
    if (!info[1]/*->ToLocalChecked()*/->IsString()) {
        THROW_BAD_ARGS("Second argument must be string change note");
    }
    if (!info[2]/*->ToLocalChecked()*/->IsFunction()) {
        THROW_BAD_ARGS("Third argument must be function");
    }

    UGCUpdateHandle_t item_id = utils::strToUint64(*(v8::String::Utf8Value(info[0])));
    auto change_note = *(v8::String::Utf8Value(info[1]));
    auto success_callback = new Nan::Callback(info[2].As<v8::Function>());
    Nan::Callback* error_callback = nullptr;

    if (info.Length() > 3 && info[3]->IsFunction())
        error_callback = new Nan::Callback(info[3].As<v8::Function>());
    Nan::AsyncQueueWorker(new greenworks::SubmitItemUpdateWorker(
        success_callback, error_callback, item_update_id_actual_hack, change_note));
    
    info.GetReturnValue().Set(Nan::Undefined());
}

void RegisterAPIs(v8::Local<v8::Object> target) {
  InitUgcMatchingTypes(target);
  InitUgcQueryTypes(target);
  InitUserUgcListSortOrder(target);
  InitUserUgcList(target);

  SET_FUNCTION("fileShare", FileShare);
  SET_FUNCTION("_publishWorkshopFile", PublishWorkshopFile);
  SET_FUNCTION("_updatePublishedWorkshopFile", UpdatePublishedWorkshopFile);
  SET_FUNCTION("_ugcGetItems", UGCGetItems);
  SET_FUNCTION("_ugcGetUserItems", UGCGetUserItems);
  SET_FUNCTION("ugcDownloadItem", UGCDownloadItem);
  SET_FUNCTION("_ugcSynchronizeItems", UGCSynchronizeItems);
  SET_FUNCTION("ugcShowOverlay", UGCShowOverlay);
  SET_FUNCTION("ugcUnsubscribe", UGCUnsubscribe);
  SET_FUNCTION("ugcSubscribe", UGCSubscribe);
  SET_FUNCTION("_CreateItem", CreateItem);
  SET_FUNCTION("_StartItemUpdate", StartItemUpdate);
  SET_FUNCTION("_SetItemContent", SetItemContent);
  SET_FUNCTION("_SetItemTitle", SetItemTitle);
  SET_FUNCTION("_SetItemPreview", SetItemPreview);
  SET_FUNCTION("_SubmitItemUpdate", SubmitItemUpdate);
  SET_FUNCTION("GetNumSubscribedItems", GetNumSubscribedItems);
  SET_FUNCTION("GetSubscribedItems", GetSubscribedItems);
  SET_FUNCTION("TryGetItemFolder", TryGetItemFolder);
  SET_FUNCTION("SetItemTags", SetItemTags);
}

SteamAPIRegistry::Add X(RegisterAPIs);

}  // namespace
}  // namespace api
}  // namespace greenworks
