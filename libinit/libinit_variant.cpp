/*
 * SPDX-FileCopyrightText: The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/logging.h>
#include <android-base/properties.h>
#include <libinit_utils.h>

#include <libinit_variant.h>

using android::base::GetProperty;

void search_variant(const std::vector<variant_info_t>& variants) {
    std::string sku_value = GetProperty("ro.boot.product.hardware.sku", "");

    for (const auto& variant : variants) {
        if ((variant.sku_value == "" || variant.sku_value == sku_value)) {
            set_variant_props(variant);
            break;
        }
    }
}

void set_variant_props(const variant_info_t variant) {
    
    set_ro_build_prop("brand", variant.brand, true);
    set_ro_build_prop("device", variant.device, true);
    set_ro_build_prop("marketname", variant.model, true);
    set_ro_build_prop("model", variant.model, true);
    set_ro_build_prop("name", variant.sku_value, true);
    property_override("ro.boot.hardware.sku", variant.sku_value);
    property_override("vendor.usb.product_string", variant.model, true);

    if (access("/system/bin/recovery", F_OK) != 0) {
        property_override("bluetooth.device.default_name", variant.model, true);
        property_override("vendor.media.target_variant", variant.media, true);
        set_ro_build_prop("fingerprint", variant.build_fingerprint);
        property_override("ro.bootimage.build.fingerprint", variant.build_fingerprint);

        property_override("ro.build.description", fingerprint_to_description(variant.build_fingerprint));
    }
}
