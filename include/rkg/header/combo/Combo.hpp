#ifndef RKG_COMBO_HPP
#define RKG_COMBO_HPP

#include <rkg/header/combo/Character.hpp>
#include <rkg/header/combo/Vehicle.hpp>
#include <variant>

namespace rkg::header::combo {

/// @brief Represents the different weight classes of characters/vehicles.
enum class WeightClass {
    Small,
    Medium,
    Large,
};

/// @brief Returns the weight class of the given character.
constexpr WeightClass weightClass(const Character character) {
    switch (character) {
    case Character::BabyMario:
    case Character::BabyLuigi:
    case Character::BabyPeach:
    case Character::BabyDaisy:
    case Character::Toad:
    case Character::Toadette:
    case Character::KoopaTroopa:
    case Character::DryBones:
    case Character::SmallMii:
    case Character::SmallMiiOutfitAFemale:
    case Character::SmallMiiOutfitAMale:
    case Character::SmallMiiOutfitBFemale:
    case Character::SmallMiiOutfitBMale:
    case Character::SmallMiiOutfitCFemale:
    case Character::SmallMiiOutfitCMale:
        return WeightClass::Small;
    case Character::Mario:
    case Character::Luigi:
    case Character::Peach:
    case Character::MenuPeach:
    case Character::Daisy:
    case Character::MenuDaisy:
    case Character::Yoshi:
    case Character::Birdo:
    case Character::DiddyKong:
    case Character::BowserJr:
    case Character::MediumMii:
    case Character::MediumMiiOutfitAFemale:
    case Character::MediumMiiOutfitAMale:
    case Character::MediumMiiOutfitBFemale:
    case Character::MediumMiiOutfitBMale:
    case Character::MediumMiiOutfitCFemale:
    case Character::MediumMiiOutfitCMale:
        return WeightClass::Medium;
    default:
        return WeightClass::Large;
    }
}

/// @brief Returns the weight class of the given character.
constexpr WeightClass weightClass(const Vehicle vehicle) {
    switch (vehicle) {
    case Vehicle::StandardKartS:
    case Vehicle::BoosterSeat:
    case Vehicle::MiniBeast:
    case Vehicle::CheepCharger:
    case Vehicle::TinyTitan:
    case Vehicle::BlueFalcon:
    case Vehicle::StandardBikeS:
    case Vehicle::BulletBike:
    case Vehicle::BitBike:
    case Vehicle::Quacker:
    case Vehicle::Magikruiser:
    case Vehicle::JetBubble:
        return WeightClass::Small;
    case Vehicle::StandardKartM:
    case Vehicle::ClassicDragster:
    case Vehicle::WildWing:
    case Vehicle::SuperBlooper:
    case Vehicle::Daytripper:
    case Vehicle::Sprinter:
        return WeightClass::Medium;
    default:
        return WeightClass::Large;
    }
}

/// @brief A class representing a character/vehicle combo.
class Combo {
public:
    enum class Error {
        /// @brief Mismatch between the weight class of the character and vehicle.
        IncongruentWeightClasses,
    };

private:
    Character m_character{};
    Vehicle m_vehicle{};

    [[nodiscard]] constexpr Combo(Character character, Vehicle vehicle);

public:
    [[nodiscard]] static constexpr std::variant<Combo, Error> create(Character character,
            Vehicle vehicle);

    [[nodiscard]] constexpr Character character() const {
        return m_character;
    }
    [[nodiscard]] constexpr Vehicle vehicle() const {
        return m_vehicle;
    }
};

constexpr std::variant<Combo, Combo::Error> Combo::create(const Character character,
        const Vehicle vehicle) {
    if (weightClass(character) != weightClass(vehicle)) {
        return Error::IncongruentWeightClasses;
    }
    return Combo{character, vehicle};
}

constexpr Combo::Combo(const Character character, const Vehicle vehicle)
    : m_character{character}, m_vehicle{vehicle} {}

} // namespace rkg::header::combo

#endif // RKG_COMBO_HPP
