#pragma once
#ifndef HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_PERMISSIONS_H_
#define HARLINN_MEDIA_GST_RTSP_SERVER_HWMRTSP_PERMISSIONS_H_

/*
   Copyright 2024 Espen Harlinn

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "gst/HWMGstMiniObject.h"
#include "HWMrtsp-server-forwards.h"

namespace Harlinn::Media::GStreamer::RtspServer
{
    namespace Internal
    {
        template<typename BaseT>
        class RTSPPermissionsImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GSTMINIOBJECT_IMPLEMENT_STANDARD_MEMBERS( RTSPPermissionsImpl, GstRTSPPermissions )

        };
    }

    using BasicRTSPPermissions = Internal::RTSPPermissionsImpl<BasicMiniObject>;
    using RTSPPermissions = Internal::RTSPPermissionsImpl<MiniObject>;
}
#endif

