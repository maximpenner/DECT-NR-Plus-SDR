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

#include <tins/tins.h>

#include <cstdlib>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    // Simple stuff, no need to use pointers!
    Tins::EthernetII eth = Tins::EthernetII() / Tins::IP() / Tins::TCP();

    // Retrieve a pointer to the stored TCP PDU
    [[maybe_unused]] Tins::TCP* tcp = eth.find_pdu<Tins::TCP>();

    // You can also retrieve a reference. This will throw a
    // pdu_not_found exception if there is no such PDU in this packet.
    [[maybe_unused]] Tins::IP& ip = eth.rfind_pdu<Tins::IP>();

    return EXIT_SUCCESS;
}
