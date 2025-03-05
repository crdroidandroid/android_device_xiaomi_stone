/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <libinit_dalvik_heap.h>
#include <libinit_variant.h>

#include "vendor_init.h"

void vendor_load_properties() {
    
    const std::vector<variant_info_t> variants = {
        { //MOONSTONE_GLOBAL
            "moonstone_p_global",
            "POCO",
            "moonstone",
            "POCO X5 5G",
            "_blair",
            "POCO/moonstone_p_global/moonstone:14/UKQ1.231003.002/V816.0.13.0.UMPMIXM:user/release-keys"
        },
        { //MOONSTONE_IN
            "moonstone_p_in",
            "POCO",
            "moonstone",
            "POCO X5 5G",
            "_blair",
            "POCO/moonstone_p_in/moonstone:14/UKQ1.231003.002/V816.0.11.0.UMPINXM:user/release-keys"
        },
        { //SUNSTONE_CN
            "sunstone_cn",
            "Redmi",
            "sunstone",
            "Redmi Note 12 5G",
            "_blair_lite",
            "Redmi/sunstone/sunstone:14/UKQ1.230917.001/V816.0.4.0.UMQCNXM:user/release-keys"
        },
        { //SUNSTONE_GLOBAL
            "sunstone_global",
            "Redmi",
            "sunstone",
            "Redmi Note 12 5G",
            "_blair_lite",
            "Redmi/sunstone_global/sunstone:14/UKQ1.230917.001/V816.0.10.0.UMQMIXM:user/release-keys"
        },
        { //SUNSTONE_IN
            "sunstone_in",
            "Redmi",
            "sunstone",
            "Redmi Note 12 5G",
            "_blair_lite",
            "Redmi/sunstone_in/sunstone:14/UKQ1.230917.001/V816.0.6.0.UMQINXM:user/release-keys"
        },
        { //SUNSTONE_X
            "sunstone_x",
            "Redmi",
            "sunstone",
            "Redmi Note 12R Pro",
            "_blair_lite",
            "Redmi/sunstone/sunstone:14/UKQ1.230917.001/V816.0.4.0.UMQCNXM:user/release-keys"
        }
    };
    
    search_variant(variants);
    set_dalvik_heap();
}
