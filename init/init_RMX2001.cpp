/*
   Copyright (c) 2014, The Linux Foundation. All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>

#include <android-base/properties.h>
#include "vendor_init.h"

using android::base::GetProperty;
using android::base::ReadFileToString;

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void init_opperator_name_properties()
{
    char const *opperator_name_file = "/proc/oppoVersion/operatorName";
    std::string opperator_name;

    if (ReadFileToString(opperator_name_file, &opperator_name)) {
        /*
         * Setup ro.separate.soft value to their OPPO project version
         * For current OPPO project version, here the following mapping:
         *
         * 101 -> NON NFC
         * 102 -> NFC
         * 104 -> NON NFC
         * 105 -> NON NFC
         * 106 -> NON NFC
         * 111 -> NON NFC
         * 112 -> NON NFC
         * 113 -> NON NFC
         * 114 -> NFC
         */
        if (opperator_name == "101") {
            property_set("ro.separate.soft", "19661");
        }
        else if (opperator_name == "102") {
            property_set("ro.separate.soft", "19662");
            property_set("ro.boot.product.hardware.sku", "nfc");
        }
        else if (opperator_name == "104") {
            property_set("ro.separate.soft", "19668");
        }
        else if (opperator_name == "105") {
            property_set("ro.separate.soft", "19669");
        }
        else if (opperator_name == "106") {
            property_set("ro.separate.soft", "19666");
        }
        else if (opperator_name == "111") {
            property_set("ro.separate.soft", "19663");
        }
        else if (opperator_name == "112") {
            property_set("ro.separate.soft", "19616");
        }
        else if (opperator_name == "113") {
            property_set("ro.separate.soft", "19667");
        }
        else if (opperator_name == "114") {
            property_set("ro.separate.soft", "19665");
            property_set("ro.boot.product.hardware.sku", "nfc");
        }
    }
    else {
        LOG(ERROR) << "Unable to read operatorName from " << opperator_name_file;
    }
}

void vendor_load_properties() {
    init_opperator_name_properties();
}
