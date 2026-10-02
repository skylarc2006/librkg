#ifndef RKG_BIRTHDAY_HPP
#define RKG_BIRTHDAY_HPP

#include <cstdint>
#include <variant>

namespace rkg::header::mii {

class Birthday {
public:
    enum class Error {
        MonthInvalid,
        DayInvalid,
    };

private:
    std::uint16_t m_month{};
    std::uint16_t m_day{};

    constexpr Birthday(std::uint16_t month, std::uint16_t day);

public:
    [[nodiscard]] static constexpr std::variant<std::monostate, Birthday, Error> create(
            std::uint16_t month, std::uint16_t day);

    [[nodiscard]] constexpr std::uint16_t month() const {
        return m_month;
    }
    [[nodiscard]] constexpr std::uint16_t day() const {
        return m_day;
    }
};

constexpr Birthday::Birthday(const std::uint16_t month, const std::uint16_t day)
    : m_month{month}, m_day{day} {}

constexpr std::variant<std::monostate, Birthday, Birthday::Error> Birthday::create(
        const std::uint16_t month, const std::uint16_t day) {
    if (month == 0) {
        if (day != 0) {
            return Error::DayInvalid;
        }
        return std::monostate{};
    }

    if (month > 12) {
        return Error::MonthInvalid;
    }

    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (day > 31) {
            return Error::DayInvalid;
        }

    case 2:
        if (day > 29) {
            return Error::DayInvalid;
        }

    default:
        if (day > 30) {
            return Error::DayInvalid;
        }
    }

    return Birthday{month, day};
}

} // namespace rkg::header::mii

#endif // RKG_BIRTHDAY_HPP
