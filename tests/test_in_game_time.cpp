#include "test_in_game_time.hpp"
#include <cassert>
#include <iostream>
#include <rkg/header/InGameTime.hpp>
#include <variant>

using namespace rkg::header;

static void testInvalidMinutesCreate() {
    constexpr auto time{InGameTime::create(103, 0, 0)};
    assert(std::holds_alternative<InGameTime::Error>(time));
}

static void testInvalidSecondsCreate() {
    constexpr auto time{InGameTime::create(0, 75, 0)};
    assert(std::holds_alternative<InGameTime::Error>(time));
}

static void testInvalidMillisecondsCreate() {
    constexpr auto time{InGameTime::create(0, 0, 1564)};
    assert(std::holds_alternative<InGameTime::Error>(time));
}

static void testInvalidMinutesSet() {
    InGameTime time{std::get<InGameTime>(InGameTime::create(0, 0, 0))};
    assert(std::holds_alternative<InGameTime::Error>(time.setMinutes(102)));
}

static void testInvalidSecondsSet() {
    InGameTime time{std::get<InGameTime>(InGameTime::create(0, 0, 0))};
    assert(std::holds_alternative<InGameTime::Error>(time.setSeconds(75)));
}

static void testInvalidMillisecondsSet() {
    InGameTime time{std::get<InGameTime>(InGameTime::create(0, 0, 0))};
    assert(std::holds_alternative<InGameTime::Error>(time.setMilliseconds(1564)));
}

static void testValidInGameTimes() {
    InGameTime time1{std::get<InGameTime>(InGameTime::create(0, 0, 0))};
    InGameTime time2{std::get<InGameTime>(InGameTime::create(1, 3, 904))};
    InGameTime time3{std::get<InGameTime>(InGameTime::create(5, 59, 999))};
    InGameTime time4{std::get<InGameTime>(InGameTime::create(99, 59, 999))};
    InGameTime time5{std::get<InGameTime>(InGameTime::create(1, 44, 497))};

    time1.setMinutes(10);
    time1.setSeconds(1);
    time1.setMilliseconds(432);

    time2.setMinutes(4);
    time2.setSeconds(25);
    time2.setMilliseconds(290);

    time3.setMinutes(2);
    time3.setSeconds(16);
    time3.setMilliseconds(577);

    time4.setMinutes(3);
    time4.setSeconds(2);
    time4.setMilliseconds(1);

    time5.setMinutes(67);
    time5.setSeconds(41);
    time5.setMilliseconds(420);
}

static void testAddition() {
    constexpr InGameTime time1{
            std::get<InGameTime>(InGameTime::createFromTotalMilliseconds(59'796))};
    constexpr InGameTime time2{
            std::get<InGameTime>(InGameTime::createFromTotalMilliseconds(58'000))};

    assert((time1 + time2).totalMilliseconds() ==
            time1.totalMilliseconds() + time2.totalMilliseconds());
}

static void testSubtraction() {
    constexpr InGameTime time1{
            std::get<InGameTime>(InGameTime::createFromTotalMilliseconds(59'796))};
    constexpr InGameTime time2{
            std::get<InGameTime>(InGameTime::createFromTotalMilliseconds(58'000))};

    assert((time1 - time2).totalMilliseconds() ==
            time1.totalMilliseconds() - time2.totalMilliseconds());
}

static void testMaxAddition() {
    constexpr InGameTime time1{
            std::get<InGameTime>(InGameTime::createFromTotalMilliseconds(5'999'998))};
    constexpr InGameTime time2{std::get<InGameTime>(InGameTime::createFromTotalMilliseconds(10))};

    assert((time1 + time2).totalMilliseconds() == InGameTime::kMaxTotalMilliseconds);
}

static void testMinSubtraction() {
    constexpr InGameTime time1{
            std::get<InGameTime>(InGameTime::createFromTotalMilliseconds(5'999'998))};
    constexpr InGameTime time2{std::get<InGameTime>(InGameTime::createFromTotalMilliseconds(10))};

    assert((time2 - time1).totalMilliseconds() == 0);
}

static void testCreateFromTotalMilliseconds() {
    constexpr InGameTime time1{
            std::get<InGameTime>(InGameTime::createFromTotalMilliseconds(999'999))};
    assert(time1.totalMilliseconds() == 999'999);
}

static void testInvalidCreateFromTotalMilliseconds() {
    constexpr auto time1{InGameTime::createFromTotalMilliseconds(9'999'999)};
    assert(std::holds_alternative<InGameTime::Error>(time1));
}

static void testPrintInGameTime() {
    constexpr InGameTime time1{std::get<InGameTime>(InGameTime::create(1, 44, 497))};
    std::cout << "Expected: 01:44.497   Result: " << time1 << '\n';
}

static void testComparingInGameTime() {
    constexpr InGameTime time1{std::get<InGameTime>(InGameTime::create(0, 5, 399))};
    constexpr InGameTime time2{std::get<InGameTime>(InGameTime::create(1, 3, 904))};
    constexpr InGameTime time3{std::get<InGameTime>(InGameTime::create(1, 44, 497))};
    constexpr InGameTime time4{std::get<InGameTime>(InGameTime::create(1, 3, 904))};

    assert(time1 < time2);
    assert(time3 > time2);
    assert(time2 == time4);
    assert(time4 >= time2);
    assert(time2 <= time4);
    assert(time1 != time4);
    assert(time4 <= time2);
    assert(time2 >= time4);
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
    testPrintInGameTime();
    testComparingInGameTime();
}
