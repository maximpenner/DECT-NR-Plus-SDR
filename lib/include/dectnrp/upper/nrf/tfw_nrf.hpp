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

#pragma once

#include "dectnrp/common/adt/miscellaneous.hpp"
#include "dectnrp/upper/tpoint.hpp"

namespace dectnrp::upper::tfw::nrf {

class tfw_nrf_t final : public tpoint_t {
    public:
        explicit tfw_nrf_t(const tpoint_config_t& tpoint_config_, phy::mac_lower_t& mac_lower_);
        ~tfw_nrf_t() = default;

        tfw_nrf_t() = delete;
        tfw_nrf_t(const tfw_nrf_t&) = delete;
        tfw_nrf_t& operator=(const tfw_nrf_t&) = delete;
        tfw_nrf_t(tfw_nrf_t&&) = delete;
        tfw_nrf_t& operator=(tfw_nrf_t&&) = delete;

        static const std::string firmware_name;

        phy::irregular_report_t work_start(const int64_t start_time_64) override final;
        phy::machigh_phy_t work_regular(const phy::regular_report_t& regular_report) override final;
        phy::machigh_phy_t work_irregular(
            const phy::irregular_report_t& irregular_report) override final;
        phy::maclow_phy_t work_pcc(const phy::phy_maclow_t& phy_maclow) override final;
        phy::machigh_phy_t work_pdc(const phy::phy_machigh_t& phy_machigh) override final;
        phy::machigh_phy_t work_pdc_error(const phy::phy_machigh_t& phy_machigh) override final;
        phy::machigh_phy_t work_application(
            const application::application_report_t& application_report) override final;
        phy::machigh_phy_tx_t work_channel(const phy::chscan_t& chscan) override final;
        void work_stop() override final;

    private:
        void parse_and_log_type_1(const phy::phy_maclow_t& phy_maclow) const;
        void parse_and_log_type_2(const phy::phy_maclow_t& phy_maclow) const;
};

}  // namespace dectnrp::upper::tfw::nrf
