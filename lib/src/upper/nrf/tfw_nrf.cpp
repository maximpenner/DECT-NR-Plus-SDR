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

#include "dectnrp/upper/nrf/tfw_nrf.hpp"

#include "dectnrp/common/prog/assert.hpp"
#include "dectnrp/common/prog/log.hpp"
#include "dectnrp/sections_part2/channel_arrangement.hpp"

namespace dectnrp::upper::tfw::nrf {

const std::string tfw_nrf_t::firmware_name("nrf");

tfw_nrf_t::tfw_nrf_t(const tpoint_config_t& tpoint_config_, phy::mac_lower_t& mac_lower_)
    : tpoint_t(tpoint_config_, mac_lower_) {
    const auto acfn = sp2::get_absolute_channel_frequency_numbering(1);
    const auto center_frequency = sp2::get_center_frequency(acfn, 1657);

    // set frequency, TX and RX power
    hw.set_command_time();
    hw.set_tx_power_ant_0dBFS_uniform_tc(-1000.0f);
    hw.set_rx_power_ant_0dBFS_uniform_tc(-30.0f);
    hw.set_freq_tc(center_frequency.FC);
}

phy::irregular_report_t tfw_nrf_t::work_start([[maybe_unused]] const int64_t start_time_64) {
    return phy::irregular_report_t();
}

phy::machigh_phy_t tfw_nrf_t::work_regular(
    [[maybe_unused]] const phy::regular_report_t& regular_report) {
    return phy::machigh_phy_t();
}

phy::machigh_phy_t tfw_nrf_t::work_irregular(
    [[maybe_unused]] const phy::irregular_report_t& irregular_report) {
    return phy::machigh_phy_t();
}

phy::maclow_phy_t tfw_nrf_t::work_pcc(const phy::phy_maclow_t& phy_maclow) {
    if (phy_maclow.pcc_report.plcf_decoder.get_plcf_base(1) != nullptr) {
        parse_and_log_type_1(phy_maclow);
    }

    if (phy_maclow.pcc_report.plcf_decoder.get_plcf_base(2) != nullptr) {
        parse_and_log_type_2(phy_maclow);
    }

    return phy::maclow_phy_t();
}

phy::machigh_phy_t tfw_nrf_t::work_pdc([[maybe_unused]] const phy::phy_machigh_t& phy_machigh) {
    return phy::machigh_phy_t();
}

phy::machigh_phy_t tfw_nrf_t::work_pdc_error(
    [[maybe_unused]] const phy::phy_machigh_t& phy_machigh) {
    return phy::machigh_phy_t();
}

phy::machigh_phy_t tfw_nrf_t::work_application(
    [[maybe_unused]] const application::application_report_t& application_report) {
    return phy::machigh_phy_t();
}

phy::machigh_phy_tx_t tfw_nrf_t::work_channel([[maybe_unused]] const phy::chscan_t& chscan) {
    return phy::machigh_phy_tx_t();
}

void tfw_nrf_t::work_stop() { dectnrp_log_inf("work_stop() called"); }

void tfw_nrf_t::parse_and_log_type_1(const phy::phy_maclow_t& phy_maclow) const {
    // base pointer to extract PLCF_type
    const auto* plcf_base = phy_maclow.pcc_report.plcf_decoder.get_plcf_base(1);

    dectnrp_assert_no_msg(plcf_base != nullptr);

    // is this the correct header type?
    if (plcf_base->get_HeaderFormat() != 0) {
        return;
    }

    // cast guaranteed to work
    const auto* plcf_10 = static_cast<const sp4::plcf_10_t*>(plcf_base);

    dectnrp_log_inf("Type 10: TransmitterIdentity={} ShortNetworkID={} STF_time={}",
                    plcf_10->TransmitterIdentity,
                    plcf_10->ShortNetworkID,
                    phy_maclow.sync_report.fine_peak_time_corrected_by_sto_fractional_64);
}

void tfw_nrf_t::parse_and_log_type_2(const phy::phy_maclow_t& phy_maclow) const {
    // base pointer to extract PLCF_type
    const auto* plcf_base = phy_maclow.pcc_report.plcf_decoder.get_plcf_base(2);

    dectnrp_assert_no_msg(plcf_base != nullptr);

    // is this the correct header type?
    if (plcf_base->get_HeaderFormat() == 0) {
        // cast guaranteed to work
        const auto* plcf_20 = static_cast<const sp4::plcf_20_t*>(plcf_base);

        dectnrp_log_inf(
            "Type 20: TransmitterIdentity={} ShortNetworkID={} ReceiverIdentity={} STF_time={}",
            plcf_20->TransmitterIdentity,
            plcf_20->ShortNetworkID,
            plcf_20->ReceiverIdentity,
            phy_maclow.sync_report.fine_peak_time_corrected_by_sto_fractional_64);
    } else if (plcf_base->get_HeaderFormat() == 1) {
        // cast guaranteed to work
        const auto* plcf_21 = static_cast<const sp4::plcf_21_t*>(plcf_base);

        dectnrp_log_inf(
            "Type 21: TransmitterIdentity={} ShortNetworkID={} ReceiverIdentity={} STF_time={}",
            plcf_21->TransmitterIdentity,
            plcf_21->ShortNetworkID,
            plcf_21->ReceiverIdentity,
            phy_maclow.sync_report.fine_peak_time_corrected_by_sto_fractional_64);
    }
}

}  // namespace dectnrp::upper::tfw::nrf
