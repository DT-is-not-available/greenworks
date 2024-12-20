// Copyright (c) 2019 Florian van Strien All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "greenworks_workshop_ugc.h"

#include <algorithm>

#include "nan.h"
#include "steam/steam_api.h"
#include "v8.h"

#include "greenworks_utils.h"

namespace greenworks {
    ItemCreatorWorker::ItemCreatorWorker(
    Nan::Callback* success_callback, Nan::Callback* error_callback,
    uint32 app_id)
    : SteamCallbackAsyncWorker(success_callback, error_callback),
      app_id_(app_id) {
          
      }

    void ItemCreatorWorker::Execute() {
        SteamAPICall_t create_result = SteamUGC()->CreateItem(app_id_, k_EWorkshopFileTypeCommunity);

        call_result_.Set(create_result, this,
            &ItemCreatorWorker::OnCreateDone);

        WaitForCompleted();
    }



    void ItemCreatorWorker::OnCreateDone(CreateItemResult_t* result, bool io_failure) {
        if ( io_failure || result->m_eResult != k_EResultOK)
        {
            SetErrorMessage("Failed to create workshop item.");
        }
        else
            publish_file_id___ = utils::uint64ToString(result->m_nPublishedFileId);
        is_completed_ = true;
    }

    void ItemCreatorWorker::HandleOKCallback() {
        Nan::HandleScope scope;

        v8::Local<v8::Value> argv[] = {
            Nan::New(publish_file_id___).ToLocalChecked() };
        callback->Call(1, argv);
    }


    SubmitItemUpdateWorker::SubmitItemUpdateWorker(
    Nan::Callback* success_callback, Nan::Callback* error_callback,
    uint64 update_id, char* change_note)
    : SteamCallbackAsyncWorker(success_callback, error_callback),
      update_id_(update_id), change_note_(change_note) {
          
      }

    void SubmitItemUpdateWorker::Execute() {
        SteamAPICall_t submit_result = SteamUGC()->SubmitItemUpdate(update_id_, change_note_);

        call_result__.Set(submit_result, this,
            &SubmitItemUpdateWorker::OnSubmitDone);

        WaitForCompleted();
    }

    void SubmitItemUpdateWorker::OnSubmitDone(SubmitItemUpdateResult_t* result, bool io_failure) {
        if ( io_failure || result->m_eResult != k_EResultOK)
        {
            SetErrorMessage("Failed to submit updates.");
        }

        result__ = result->m_eResult;
        is_completed_ = true;
    }
    
    void SubmitItemUpdateWorker::HandleOKCallback() {
        Nan::HandleScope scope;

        v8::Local<v8::Value> argv[] = {
            Nan::New(result__) };
        callback->Call(1, argv);
    }
}

//SetItemContent
//SubmitItemUpdate
//StartItemUpdate