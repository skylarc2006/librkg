#include "test_slot_id.hpp"
#include <cassert>
#include <rkg/header/SlotId.hpp>

using namespace rkg::header;

void testSlotId() {
    assert(static_cast<int>(SlotId::LuigiCircuit) == 0x08);
    assert(static_cast<int>(SlotId::MooMooMeadows) == 0x01);
    assert(static_cast<int>(SlotId::MushroomGorge) == 0x02);
    assert(static_cast<int>(SlotId::ToadsFactory) == 0x04);

    assert(static_cast<int>(SlotId::MarioCircuit) == 0x00);
    assert(static_cast<int>(SlotId::CoconutMall) == 0x05);
    assert(static_cast<int>(SlotId::DKSummit) == 0x06);
    assert(static_cast<int>(SlotId::WariosGoldMine) == 0x07);

    assert(static_cast<int>(SlotId::DaisyCircuit) == 0x09);
    assert(static_cast<int>(SlotId::KoopaCape) == 0x0F);
    assert(static_cast<int>(SlotId::MapleTreeway) == 0x0B);
    assert(static_cast<int>(SlotId::GrumbleVolcano) == 0x03);

    assert(static_cast<int>(SlotId::DryDryRuins) == 0x0E);
    assert(static_cast<int>(SlotId::MoonviewHighway) == 0x0A);
    assert(static_cast<int>(SlotId::BowsersCastle) == 0x0C);
    assert(static_cast<int>(SlotId::RainbowRoad) == 0x0D);

    assert(static_cast<int>(SlotId::GCNPeachBeach) == 0x10);
    assert(static_cast<int>(SlotId::DSYoshiFalls) == 0x14);
    assert(static_cast<int>(SlotId::SNESGhostValley2) == 0x19);
    assert(static_cast<int>(SlotId::N64MarioRaceway) == 0x1A);

    assert(static_cast<int>(SlotId::N64SherbetLand) == 0x1B);
    assert(static_cast<int>(SlotId::GBAShyGuyBeach) == 0x1F);
    assert(static_cast<int>(SlotId::DSDelfinoSquare) == 0x17);
    assert(static_cast<int>(SlotId::GCNWaluigiStadium) == 0x12);

    assert(static_cast<int>(SlotId::DSDesertHills) == 0x15);
    assert(static_cast<int>(SlotId::GBABowserCastle3) == 0x1E);
    assert(static_cast<int>(SlotId::N64DKsJungleParkway) == 0x1D);
    assert(static_cast<int>(SlotId::GCNMarioCircuit) == 0x11);

    assert(static_cast<int>(SlotId::SNESMarioCircuit3) == 0x18);
    assert(static_cast<int>(SlotId::DSPeachGardens) == 0x16);
    assert(static_cast<int>(SlotId::GCNDKMountain) == 0x13);
    assert(static_cast<int>(SlotId::N64BowsersCastle) == 0x1C);

    assert(static_cast<int>(SlotId::BlockPlaza) == 0x21);
    assert(static_cast<int>(SlotId::DelfinoPier) == 0x20);
    assert(static_cast<int>(SlotId::FunkyStadium) == 0x23);
    assert(static_cast<int>(SlotId::ChainChompRoulette) == 0x22);
    assert(static_cast<int>(SlotId::ThwompDesert) == 0x24);

    assert(static_cast<int>(SlotId::SNESBattleCourse4) == 0x27);
    assert(static_cast<int>(SlotId::GBABattleCourse3) == 0x28);
    assert(static_cast<int>(SlotId::N64Skyscraper) == 0x29);
    assert(static_cast<int>(SlotId::GCNCookieLand) == 0x25);
    assert(static_cast<int>(SlotId::DSTwilightHouse) == 0x26);

    assert(static_cast<int>(SlotId::GalaxyColosseum) == 0x36);
    assert(static_cast<int>(SlotId::WinDemo) == 0x37);
    assert(static_cast<int>(SlotId::LoseDemo) == 0x38);
    assert(static_cast<int>(SlotId::DrawDemo) == 0x39);
    assert(static_cast<int>(SlotId::EndingDemo) == 0x3A);
}
