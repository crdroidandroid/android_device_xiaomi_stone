/*
 * Copyright (C) 2023 Paranoid Android
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <android-base/properties.h>
#include <sys/sysinfo.h>

#include <cstdlib>
#include <cstring>
#include <vector>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;

// list of partitions to override props
std::vector<std::string> ro_props_default_source_order = {
    "", "odm.", "odm_dlkm.", "product.", "system.", "system_ext.", "vendor.", "vendor_dlkm.",
};

void property_override(char const prop[], char const value[], bool add = true) {
    auto pi = (prop_info *)__system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void set_ro_build_prop(const std::string &source, const std::string &prop,
                       const std::string &value, bool product = false) {
    std::string prop_name;

    if (product) {
        prop_name = "ro.product." + source + prop;
    } else {
        prop_name = "ro." + source + "build." + prop;
    }

    property_override(prop_name.c_str(), value.c_str(), true);
}

void set_device_props(const std::string fingerprint, const std::string description,
                      const std::string brand, const std::string device, const std::string model, const std::string mod_device) {
    for (const auto &source : ro_props_default_source_order) {
        set_ro_build_prop(source, "fingerprint", fingerprint);
        set_ro_build_prop(source, "brand", brand, true);
        set_ro_build_prop(source, "device", device, true);
        set_ro_build_prop(source, "model", model, true);
    }

    property_override("ro.build.fingerprint", fingerprint.c_str());
    property_override("ro.build.description", description.c_str());
    property_override("ro.product.mod_device", mod_device.c_str());
    property_override("bluetooth.device.default_name", model.c_str());
}

void load_device_properties() {
    // Detect variant and override properties
    std::string hwname = GetProperty("ro.boot.hwname", "");
    std::string hwversion = GetProperty("ro.boot.hwversion", "");

    if (hwname == "moonstone") {
        set_device_props(
            "POCO/moonstone_p_global/moonstone:13/TKQ1.221114.001/V14.0.5.0.TMPMIXM:user/release-keys",
            "qssi-user 13 TKQ1.221114.001 V14.0.5.0.TMPMIXM release-keys", "moonstone_global", "POCO", "moonstone",
            "POCO X5 5G");
    } else if (hwname == "sunstone") {
        set_device_props(
            "Redmi/sunstone/sunstone:13/TKQ1.221013.002/V14.0.5.0.TMQMIXM:user/release-keys",
            "qssi-user 13 TKQ1.221114.001 V14.0.5.0.TMQMIXM release-keys", "sunstone_global", "Redmi", "sunstone",
            "Redmi Note 12 5G");
    }
    property_override("vendor.boot.hwversion", hwversion.c_str());
    property_override("ro.boot.product.hardware.sku", hwname.c_str());
}

void load_dalvik_properties() {
    char const *heapstartsize;
    char const *heapgrowthlimit;
    char const *heapsize;
    char const *heapminfree;
    char const *heapmaxfree;
    char const *heaptargetutilization;
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram >= 5ull * 1024 * 1024 * 1024) {
        // from - phone-xhdpi-6144-dalvik-heap.mk
        heapstartsize = "16m";
        heapgrowthlimit = "256m";
        heapsize = "512m";
        heaptargetutilization = "0.5";
        heapminfree = "8m";
        heapmaxfree = "32m";
    } else if (sys.totalram >= 3ull * 1024 * 1024 * 1024) {
        // from - phone-xhdpi-4096-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heaptargetutilization = "0.6";
        heapminfree = "8m";
        heapmaxfree = "16m";
    } else {
        return;
    }

    property_override("dalvik.vm.heapstartsize", heapstartsize);
    property_override("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_override("dalvik.vm.heapsize", heapsize);
    property_override("dalvik.vm.heaptargetutilization", heaptargetutilization);
    property_override("dalvik.vm.heapminfree", heapminfree);
    property_override("dalvik.vm.heapmaxfree", heapmaxfree);
}

void vendor_load_properties() {
    load_dalvik_properties();
    load_device_properties();
}
