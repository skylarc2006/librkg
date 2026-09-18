#include "test_in_game_time.hpp"
#include <rkg/header/InGameTime.hpp>
#include <cassert>
#include <expected>

static void testInvalidMinutesCreate() {
    const auto time{InGameTime::create(103, 0, 0)};
    assert(time == std::unexpected(InGameTime::Error::InvalidInGameTimeElement));
}

static void testInvalidSecondsCreate() {
    const auto time{InGameTime::create(0, 75, 0)};
    assert(time == std::unexpected(InGameTime::Error::InvalidInGameTimeElement));
}

static void testInvalidMillisecondsCreate() {
    const auto time{InGameTime::create(0, 0, 1564)};
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
    assert(time.setMilliseconds(1564) == std::unexpected(InGameTime::Error::InvalidInGameTimeElement));
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

void testInGameTime() {
    testInvalidMinutesCreate();
    testInvalidSecondsCreate();
    testInvalidMillisecondsCreate();
    testInvalidMinutesSet();
    testInvalidSecondsSet();
    testInvalidMillisecondsSet();
    testValidInGameTimes();
}