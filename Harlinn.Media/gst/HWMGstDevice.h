#pragma once 
#ifndef HARLINN_MEDIA_HWMGSTDEVICE_H_
#define HARLINN_MEDIA_HWMGSTDEVICE_H_
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

#include "HWMGstObject.h"

namespace Harlinn::Media::GStreamer
{
    namespace Internal
    {
        template<typename BaseT>
        class DeviceImpl : public BaseT
        {
        public:
            using Base = BaseT;
            HWM_GOBJECT_IMPLEMENT_STANDARD_MEMBERS( DeviceImpl, GstDevice )
        };
    }
    using BasicDevice = Internal::DeviceImpl<BasicObject>;
    using Device = Internal::DeviceImpl<Object>;
}
#endif
