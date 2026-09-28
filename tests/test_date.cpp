#include "test_date.hpp"
#include <cassert>
#include <rkg/header/Date.hpp>
#include <variant>

using namespace rkg::header;

void testDate() {
    assert(std::holds_alternative<Date>(Date::create(2000, 1, 1)));
    assert(std::holds_alternative<Date>(Date::create(2099, 12, 31)));
    assert(std::holds_alternative<Date>(Date::create(2055, 2, 31)));
    assert(std::holds_alternative<Date>(Date::create(2040, 5, 1)));

    assert(std::holds_alternative<Date::Error>(Date::create(2100, 12, 31)));
    assert(std::holds_alternative<Date::Error>(Date::create(2020, 13, 31)));
    assert(std::holds_alternative<Date::Error>(Date::create(2080, 1, 35)));
    assert(std::holds_alternative<Date::Error>(Date::create(1995, 2, 2)));

    constexpr auto date1 = std::get<Date>(Date::create(2010, 1, 1));
    constexpr auto date2 = std::get<Date>(Date::create(2011, 1, 1));
    constexpr auto date3 = std::get<Date>(Date::create(2010, 5, 26));
    constexpr auto date4 = std::get<Date>(Date::create(2010, 3, 1));
    constexpr auto date5 = std::get<Date>(Date::create(2010, 2, 31));
    constexpr auto date6 = std::get<Date>(Date::create(2010, 1, 1));

    assert(date1 == date6);
    assert(date1 >= date6);
    assert(date2 >= date1);
    assert(date4 > date5);
    assert(date4 < date3);
    assert(date1 <= date6);
    assert(date5 <= date2);
    assert(date3 != date4);
}
