#include "test_combo.hpp"
#include <cassert>
#include <rkg/header/combo/Combo.hpp>
#include <variant>

using namespace rkg::header::combo;

void testCombo() {
    assert(std::holds_alternative<Combo>(
            Combo::create(Character::FunkyKong, Vehicle::FlameRunner)));
    assert(std::holds_alternative<Combo>(Combo::create(Character::Mario, Vehicle::SuperBlooper)));
    assert(std::holds_alternative<Combo>(Combo::create(Character::BabyDaisy, Vehicle::BulletBike)));

    assert(std::holds_alternative<Combo::Error>(Combo::create(Character::Toad, Vehicle::MachBike)));
    assert(std::holds_alternative<Combo::Error>(
            Combo::create(Character::Yoshi, Vehicle::FlameFlyer)));
    assert(std::holds_alternative<Combo::Error>(
            Combo::create(Character::KingBoo, Vehicle::BulletBike)));
}
