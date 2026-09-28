#ifndef RKG_HEADER_HPP
#define RKG_HEADER_HPP

#include <rkg/header/Controller.hpp>
#include <rkg/header/Date.hpp>
#include <rkg/header/DriftType.hpp>
#include <rkg/header/GhostType.hpp>
#include <rkg/header/InGameTime.hpp>
#include <rkg/header/SlotId.hpp>
#include <rkg/header/combo/Combo.hpp>
#include <variant>
#include <vector>

namespace rkg::header {

/// @brief A class representing the header of a Mario Kart Wii RKG ghost file.
class Header {
    InGameTime m_finishTime{std::get<InGameTime>(InGameTime::create(0, 0, 0))};
    SlotId m_slotId{SlotId::LuigiCircuit};
    combo::Combo m_combo{std::get<combo::Combo>(
            combo::Combo::create(combo::Character::Mario, combo::Vehicle::StandardKartM))};
    Date m_dateSet{std::get<Date>(Date::create(2010, 1, 1))};
    Controller m_controller{Controller::GameCube};
    bool m_compressed{false};
    GhostType m_ghostType{GhostType::PlayerBest};
    DriftType m_driftType{DriftType::Manual};
    std::uint16_t m_decompressedInputDataLength{};
    std::uint16_t m_lapCount{3};
    std::vector<InGameTime> m_lapTimes{std::get<InGameTime>(InGameTime::create(0, 0, 0)),
            std::get<InGameTime>(InGameTime::create(0, 0, 0)),
            std::get<InGameTime>(InGameTime::create(0, 0, 0))};
    // Location m_location{};
    // Mii m_mii{};
};

} // namespace rkg::header

#endif // RKG_HEADER_HPP
