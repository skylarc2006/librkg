#include "test_combo.hpp"
#include "test_date.hpp"
#include "test_in_game_time.hpp"
#include "test_slot_id.hpp"

int main() {
    testInGameTime();
    testSlotId();
    testCombo();
    testDate();
    return 0;
}
