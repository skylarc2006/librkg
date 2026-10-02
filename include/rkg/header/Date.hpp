#ifndef RKG_DATE_HPP
#define RKG_DATE_HPP

#include <cstdint>
#include <tuple>
#include <variant>

namespace rkg::header {

class Date {
public:
    enum class Error {
        YearInvalid,
        MonthInvalid,
        DayInvalid,
    };

    static constexpr std::uint16_t kMaxYear{2099};
    static constexpr std::uint16_t kMinYear{2000};
    static constexpr std::uint16_t kMaxMonth{12};
    static constexpr std::uint16_t kMaxDay{31};

private:
    std::uint16_t m_year{};
    std::uint16_t m_month{};
    std::uint16_t m_day{};

    constexpr Date(std::uint16_t year, std::uint16_t month, std::uint16_t day);

public:
    [[nodiscard]] static constexpr std::variant<Date, Error> create(std::uint16_t year,
            std::uint16_t month, std::uint16_t day);

    [[nodiscard]] constexpr std::uint16_t year() const {
        return m_year;
    }

    [[nodiscard]] constexpr std::uint16_t month() const {
        return m_month;
    }

    [[nodiscard]] constexpr std::uint16_t day() const {
        return m_day;
    }

    constexpr auto operator<(const Date &other) const;
    constexpr auto operator<=(const Date &other) const;
    constexpr auto operator==(const Date &other) const;
    constexpr auto operator>=(const Date &other) const;
    constexpr auto operator>(const Date &other) const;
    constexpr auto operator!=(const Date &other) const;
};

constexpr Date::Date(const std::uint16_t year, const std::uint16_t month, const std::uint16_t day)
    : m_year{year}, m_month{month}, m_day{day} {}

constexpr std::variant<Date, Date::Error> Date::create(const std::uint16_t year,
        const std::uint16_t month, const std::uint16_t day) {
    if (year < kMinYear || year > kMaxYear) {
        return Error::YearInvalid;
    }

    if (month > kMaxMonth) {
        return Error::MonthInvalid;
    }

    if (day > kMaxDay) {
        return Error::DayInvalid;
    }

    return Date{year, month, day};
}

constexpr auto Date::operator<(const Date &other) const {
    return std::tie(m_year, m_month, m_day) < std::tie(other.m_year, other.m_month, other.m_day);
}

constexpr auto Date::operator<=(const Date &other) const {
    return std::tie(m_year, m_month, m_day) <= std::tie(other.m_year, other.m_month, other.m_day);
}

constexpr auto Date::operator==(const Date &other) const {
    return std::tie(m_year, m_month, m_day) == std::tie(other.m_year, other.m_month, other.m_day);
}

constexpr auto Date::operator>=(const Date &other) const {
    return std::tie(m_year, m_month, m_day) >= std::tie(other.m_year, other.m_month, other.m_day);
}

constexpr auto Date::operator>(const Date &other) const {
    return std::tie(m_year, m_month, m_day) > std::tie(other.m_year, other.m_month, other.m_day);
}

constexpr auto Date::operator!=(const Date &other) const {
    return std::tie(m_year, m_month, m_day) != std::tie(other.m_year, other.m_month, other.m_day);
}

} // namespace rkg::header

#endif // RKG_DATE_HPP
