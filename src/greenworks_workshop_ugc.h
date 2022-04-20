// Copyright (c) 2019 Florian van Strien All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SRC_GREENWORKS_UGC_WORKERS_H_
#define SRC_GREENWORKS_UGC_WORKERS_H_

#include "steam_async_worker.h"

#include <vector>

#include "steam/steam_api.h"

namespace greenworks {
    class ItemCreatorWorker : public SteamCallbackAsyncWorker {
        public:
            ItemCreatorWorker(Nan::Callback* success_callback,
                                    Nan::Callback* error_callback,
                                    uint32 app_id);
            void OnCreateDone(CreateItemResult_t* result, bool io_failure);

            void Execute() override;
            void HandleOKCallback() override;
        private:
            uint32 app_id_;

            PublishedFileId_t publish_file_id_;
            CCallResult<ItemCreatorWorker,
                CreateItemResult_t> call_result_;
    };

    
    class SubmitItemUpdateWorker : public SteamCallbackAsyncWorker {
        public:
            SubmitItemUpdateWorker(Nan::Callback* success_callback,
                                    Nan::Callback* error_callback,
                                    uint64 update_id, char* change_note);
            void OnSubmitDone(SubmitItemUpdateResult_t* result, bool io_failure);

            void Execute() override;
        private:
            uint64 update_id_;
            char* change_note_;

            CCallResult<SubmitItemUpdateWorker,
                SubmitItemUpdateResult_t> call_result__;
    };
}

#endif