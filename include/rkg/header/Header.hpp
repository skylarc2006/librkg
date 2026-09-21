#ifndef RKG_HEADER_HPP
#define RKG_HEADER_HPP

#include <rkg/header/InGameTime.hpp>

namespace rkg::header {

/// @brief A class representing the header of a Mario Kart Wii RKG ghost file.
class Header {
    rkg::header::InGameTime m_finishTime{rkg::header::InGameTime::create(0, 0, 0).value()};
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

} // namespace rkg::header

#endif // RKG_HEADER_HPP
