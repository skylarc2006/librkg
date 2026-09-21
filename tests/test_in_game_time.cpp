#include "test_in_game_time.hpp"
#include <cassert>
#include <expected>
#include <rkg/header/InGameTime.hpp>

using namespace rkg::header;

static void testInvalidMinutesCreate() {
    constexpr auto time{InGameTime::create(103, 0, 0)};
    assert(time == std::unexpected(InGameTime::Error::InvalidInGameTimeElement));
}

static void testInvalidSecondsCreate() {
    constexpr auto time{InGameTime::create(0, 75, 0)};
    assert(time == std::unexpected(InGameTime::Error::InvalidInGameTimeElement));
}

static void testInvalidMillisecondsCreate() {
    constexpr auto time{InGameTime::create(0, 0, 1564)};
    assert(time == std::unexpected(InGameTime::Error::InvalidInGameTimeElement));
}

static void testInvalidMinutesSet() {
    InGameTime time{InGameTime::create(0, 0, 0).value()};
    assert(time.setMinutes(102) == std::unexpected(InGameTime::Error::InvalidInGameTimeElement));
}

static void testInvalidSecondsSet() {
    InGameTime time{InGameTime::create(0, 0, 0).value()};
    assert(time.setSeconds(75) == std::unexpected(InGameTime::Error::InvalidInGameTimeElement));
}

static void testInvalidMillisecondsSet() {
    InGameTime time{InGameTime::create(0, 0, 0).value()};
    assert(time.setMilliseconds(1564) ==
            std::unexpected(InGameTime::Error::InvalidInGameTimeElement));
}

static void testValidInGameTimes() {
    InGameTime time1{InGameTime::create(0, 0, 0).value()};
    InGameTime time2{InGameTime::create(1, 3, 904).value()};
    InGameTime time3{InGameTime::create(5, 59, 999).value()};
    InGameTime time4{InGameTime::create(99, 59, 999).value()};
    InGameTime time5{InGameTime::create(1, 44, 497).value()};

    time1.setMinutes(10).value();
    time1.setSeconds(1).value();
    time1.setMilliseconds(432).value();

    time2.setMinutes(4).value();
    time2.setSeconds(25).value();
    time2.setMilliseconds(290).value();

    time3.setMinutes(2).value();
    time3.setSeconds(16).value();
    time3.setMilliseconds(577).value();

    time4.setMinutes(3).value();
    time4.setSeconds(2).value();
    time4.setMilliseconds(1).value();

    time5.setMinutes(67).value();
    time5.setSeconds(41).value();
    time5.setMilliseconds(420).value();
}

static void testAddition() {
    constexpr InGameTime time1{InGameTime::createFromTotalMilliseconds(59'796).value()};
    constexpr InGameTime time2{InGameTime::createFromTotalMilliseconds(58'000).value()};

    assert((time1 + time2).totalMilliseconds() ==
            time1.totalMilliseconds() + time2.totalMilliseconds());
}

static void testSubtraction() {
    constexpr InGameTime time1{InGameTime::createFromTotalMilliseconds(59'796).value()};
    constexpr InGameTime time2{InGameTime::createFromTotalMilliseconds(58'000).value()};

    assert((time1 - time2).totalMilliseconds() ==
            time1.totalMilliseconds() - time2.totalMilliseconds());
}

static void testMaxAddition() {
    constexpr InGameTime time1{InGameTime::createFromTotalMilliseconds(5'999'998).value()};
    constexpr InGameTime time2{InGameTime::createFromTotalMilliseconds(10).value()};

    assert((time1 + time2).totalMilliseconds() == InGameTime::kMaxTotalMilliseconds);
}

static void testMinSubtraction() {
    constexpr InGameTime time1{InGameTime::createFromTotalMilliseconds(5'999'998).value()};
    constexpr InGameTime time2{InGameTime::createFromTotalMilliseconds(10).value()};

    assert((time2 - time1).totalMilliseconds() == 0);
}

static void testCreateFromTotalMilliseconds() {
    constexpr InGameTime time1{InGameTime::createFromTotalMilliseconds(999'999).value()};
    assert(time1.totalMilliseconds() == 999'999);
}

static void testInvalidCreateFromTotalMilliseconds() {
    constexpr auto time1{InGameTime::createFromTotalMilliseconds(9'999'999)};
    assert(time1 == std::unexpected(InGameTime::Error::InvalidInGameTimeElement));
}

void testInGameTime() {
    testInvalidMinutesCreate();
    testInvalidSecondsCreate();
    testInvalidMillisecondsCreate();
    testInvalidMinutesSet();
    testInvalidSecondsSet();
    testInvalidMillisecondsSet();
    testValidInGameTimes();
    testAddition();
    testSubtraction();
    testMaxAddition();
    testMinSubtraction();
    testCreateFromTotalMilliseconds();
    testInvalidCreateFromTotalMilliseconds();
}
