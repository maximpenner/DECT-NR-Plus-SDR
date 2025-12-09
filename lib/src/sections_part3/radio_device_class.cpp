/*
 * Copyright 2023-present Maxim Penner
 *
 * This file is part of DECTNRP.
 *
 * DECTNRP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * DECTNRP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 */

#include "dectnrp/sections_part3/radio_device_class.hpp"

#include <bit>

#include "dectnrp/common/json/json_parse.hpp"
#include "dectnrp/common/prog/assert.hpp"

namespace dectnrp::sp3 {

radio_device_class_t get_radio_device_class(const std::string& radio_device_class_string) {
    radio_device_class_t q;

    if (radio_device_class_string.compare("1.1.1.A") == 0) {
        q.u_min = 1;
        q.b_min = 1;
        q.N_TX_min = 1;
        q.mcs_index_min = 7;
        q.M_DL_HARQ_min = 8;
        q.M_connection_DL_HARQ_min = 2;
        q.N_soft_min = 25344;
        q.Z_min = 2048;

        // set to 16 to be standard compliant
        q.PacketLength_min = 4;

    } else if (radio_device_class_string.compare("1.1.1.B") == 0) {
        q.u_min = 1;
        q.b_min = 1;
        q.N_TX_min = 1;
        q.mcs_index_min = 7;
        q.M_DL_HARQ_min = 8;
        q.M_connection_DL_HARQ_min = 2;
        q.N_soft_min = 25344;
        q.Z_min = 6144;

        // set to 16 to be standard compliant
        q.PacketLength_min = 4;

    } else if (radio_device_class_string.compare("8.1.1.A") == 0) {
        q.u_min = 8;
        q.b_min = 1;
        q.N_TX_min = 1;
        q.mcs_index_min = 7;
        q.M_DL_HARQ_min = 8;
        q.M_connection_DL_HARQ_min = 2;
        q.N_soft_min = 25344;
        q.Z_min = 6144;

        // set to 16 to be standard compliant
        q.PacketLength_min = 4;

    } else if (radio_device_class_string.compare("1.8.1.A") == 0) {
        q.u_min = 1;
        q.b_min = 8;
        q.N_TX_min = 1;
        q.mcs_index_min = 7;
        q.M_DL_HARQ_min = 8;
        q.M_connection_DL_HARQ_min = 2;
        q.N_soft_min = 25344;
        q.Z_min = 6144;

        // set to 16 to be standard compliant
        q.PacketLength_min = 4;

    } else if (radio_device_class_string.compare("2.12.4.A") == 0) {
        q.u_min = 2;
        q.b_min = 12;
        q.N_TX_min = 4;
        q.mcs_index_min = 7;
        q.M_DL_HARQ_min = 8;
        q.M_connection_DL_HARQ_min = 2;
        q.N_soft_min = 25344;
        q.Z_min = 2048;

        // set to 16 to be standard compliant
        q.PacketLength_min = 4;

    } else if (radio_device_class_string.compare("2.12.4.B") == 0) {
        q.u_min = 2;
        q.b_min = 12;
        q.N_TX_min = 4;
        q.mcs_index_min = 7;
        q.M_DL_HARQ_min = 8;
        q.M_connection_DL_HARQ_min = 2;
        q.N_soft_min = 25344;
        q.Z_min = 6144;

        // set to 16 to be standard compliant
        q.PacketLength_min = 4;

    } else if (radio_device_class_string.compare("8.12.8.A") == 0) {
        q.u_min = 8;
        q.b_min = 12;
        q.N_TX_min = 8;
        q.mcs_index_min = 9;
        q.M_DL_HARQ_min = 8;
        q.M_connection_DL_HARQ_min = 2;
        q.N_soft_min = 225344;
        q.Z_min = 6144;

        // set to 16 to be standard compliant
        q.PacketLength_min = 16;

    } else if (radio_device_class_string.compare("8.16.8.A") == 0) {
        q.u_min = 8;
        q.b_min = 16;
        q.N_TX_min = 8;
        q.mcs_index_min = 9;
        q.M_DL_HARQ_min = 8;
        q.M_connection_DL_HARQ_min = 2;
        q.N_soft_min = 225344;
        q.Z_min = 6144;

        // set to 16 to be standard compliant
        q.PacketLength_min = 16;

    } else {
        // must be a filepath
        nlohmann::ordered_json json = common::jsonparse::parse(radio_device_class_string);

        auto it = json.begin();

        dectnrp_assert(it.key().starts_with("RDC"), "incorrect prefix for key {}", it.key());

        q.radio_device_class_string =
            common::jsonparse::read_string(it, "radio_device_class_string");
        q.u_min = common::jsonparse::read_int(it, "u_min");
        q.b_min = common::jsonparse::read_int(it, "b_min");
        q.N_TX_min = common::jsonparse::read_int(it, "N_TX_min");
        q.mcs_index_min = common::jsonparse::read_int(it, "mcs_index_min");
        q.M_DL_HARQ_min = common::jsonparse::read_int(it, "M_DL_HARQ_min");
        q.M_connection_DL_HARQ_min = common::jsonparse::read_int(it, "M_connection_DL_HARQ_min");
        q.N_soft_min = common::jsonparse::read_int(it, "N_soft_min");
        q.Z_min = common::jsonparse::read_int(it, "Z_min");
        q.PacketLength_min = common::jsonparse::read_int(it, "PacketLength_min");
    }

    dectnrp_assert(std::has_single_bit(q.u_min) && q.u_min <= 8, "u undefined");
    dectnrp_assert((std::has_single_bit(q.b_min) && q.b_min <= 16) || q.b_min == 12, "b undefined");
    dectnrp_assert(std::has_single_bit(q.N_TX_min) && q.N_TX_min <= 8, "N_TX_min undefined");
    dectnrp_assert(q.mcs_index_min <= 11, "mcs_index_min undefined");

    // the following three limitations are arbitrary
    dectnrp_assert(1 <= q.M_DL_HARQ_min && q.M_DL_HARQ_min <= 64, "M_DL_HARQ_min undefined");
    dectnrp_assert(1 <= q.M_connection_DL_HARQ_min && q.M_connection_DL_HARQ_min <= 64,
                   "M_connection_DL_HARQ_min undefined");
    dectnrp_assert(25344 <= q.N_soft_min && q.N_soft_min <= 16777216, "N_soft_min undefined");

    dectnrp_assert(q.Z_min == 2048 || q.Z_min == 6144, "Z_min undefined");
    dectnrp_assert(1 <= q.PacketLength_min && q.PacketLength_min <= 16,
                   "PacketLength_min undefined");

    return q;
}

}  // namespace dectnrp::sp3
