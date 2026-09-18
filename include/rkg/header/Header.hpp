#ifndef RKG_HEADER_HPP
#define RKG_HEADER_HPP

#include <cstdint>
#include <vector>

#include <rkg/header/InGameTime.hpp>

class Header {
    InGameTime m_finishTime{InGameTime::create(0, 0, 0).value()};
    // SlotId m_slotId{};
    // Combo m_combo{};
    // Date m_dateSet{};
    // Controller m_controller{};
    // bool m_compressed{};
    // TransmissionMod m_transmissionMod{};
    // GhostType m_ghostType{};
    // DriftType m_driftType{};
    // std::uint16_t m_decompressedInputDataLength{};
    // std::uint16_t m_lapCount{};
    // std::vector<InGameTime> m_lapTimes{};
    // Location m_location{};
    // Mii m_mii{};
};

#endif // RKG_HEADER_HPP
