#ifndef RKG_IN_GAME_TIME_HPP
#define RKG_IN_GAME_TIME_HPP

#include <cstdint>
#include <iomanip>
#include <ostream>
#include <tuple>
#include <variant>

namespace rkg::header {

/// @brief A class representing an in game lap or race finish time.
class InGameTime {
public:
    enum class Error {
        InvalidInGameTimeElement, ///< Minutes, seconds, or milliseconds field contains a
                                  ///< semantically invalid value.
    };

private:
    std::uint16_t m_minutes{};
    std::uint16_t m_seconds{};
    std::uint16_t m_milliseconds{};

    [[nodiscard]] constexpr InGameTime(std::uint16_t minutes, std::uint16_t seconds,
            std::uint16_t milliseconds);

    struct Timer {
        std::uint16_t minutes;
        std::uint16_t seconds;
        std::uint16_t milliseconds;
    };

    /// @brief Expects a total milliseconds value between 0 and 5,999,999 inclusive.
    static constexpr Timer totalMillisecondsToTimer(const std::uint32_t totalMilliseconds) {
        const auto minutes{static_cast<std::uint16_t>(totalMilliseconds / 60000)};
        const auto seconds{static_cast<std::uint16_t>(totalMilliseconds / 1000 % 60)};
        const auto milliseconds{static_cast<std::uint16_t>(totalMilliseconds % 1000)};

        return {minutes, seconds, milliseconds};
    }

public:
    static constexpr std::uint16_t kMaxMinutes{99};
    static constexpr std::uint16_t kMaxSeconds{59};
    static constexpr std::uint16_t kMaxMilliseconds{999};
    /// @brief 5,999,999 ms = 99m 59s 999ms
    static constexpr std::uint32_t kMaxTotalMilliseconds{5'999'999};

    [[nodiscard]] static constexpr std::variant<InGameTime, Error> create(std::uint16_t minutes,
            std::uint16_t seconds, std::uint16_t milliseconds);
    [[nodiscard]] static constexpr std::variant<InGameTime, Error> createFromTotalMilliseconds(
            std::uint32_t totalMilliseconds);

    [[nodiscard]] constexpr std::uint32_t totalMilliseconds() const;

    [[nodiscard]] constexpr std::uint16_t minutes() const {
        return m_minutes;
    }
    [[nodiscard]] constexpr std::uint16_t seconds() const {
        return m_seconds;
    }
    [[nodiscard]] constexpr std::uint16_t milliseconds() const {
        return m_milliseconds;
    }

    constexpr std::variant<std::monostate, InGameTime::Error> setMinutes(std::uint16_t minutes);
    constexpr std::variant<std::monostate, InGameTime::Error> setSeconds(std::uint16_t seconds);
    constexpr std::variant<std::monostate, InGameTime::Error> setMilliseconds(
            std::uint16_t milliseconds);

    constexpr InGameTime operator+(const InGameTime &other) const;
    constexpr InGameTime operator-(const InGameTime &other) const;
    constexpr InGameTime &operator+=(const InGameTime &other);
    constexpr InGameTime &operator-=(const InGameTime &other);
    constexpr auto operator<(const InGameTime &other) const;
    constexpr auto operator<=(const InGameTime &other) const;
    constexpr auto operator==(const InGameTime &other) const;
    constexpr auto operator>=(const InGameTime &other) const;
    constexpr auto operator>(const InGameTime &other) const;
    constexpr auto operator!=(const InGameTime &other) const;
};

constexpr std::uint32_t InGameTime::totalMilliseconds() const {
    return minutes() * 60'000U + seconds() * 1'000U + milliseconds();
}

constexpr InGameTime::InGameTime(const std::uint16_t minutes, const std::uint16_t seconds,
        const std::uint16_t milliseconds)
    : m_minutes{minutes}, m_seconds{seconds}, m_milliseconds{milliseconds} {}

constexpr std::variant<InGameTime, InGameTime::Error> InGameTime::create(
        const std::uint16_t minutes, const std::uint16_t seconds,
        const std::uint16_t milliseconds) {
    if (minutes > kMaxMinutes || seconds > kMaxSeconds || milliseconds > kMaxMilliseconds) {
        return Error::InvalidInGameTimeElement;
    }

    return InGameTime{minutes, seconds, milliseconds};
}

constexpr std::variant<InGameTime, InGameTime::Error> InGameTime::createFromTotalMilliseconds(
        const std::uint32_t totalMilliseconds) {
    if (totalMilliseconds > kMaxTotalMilliseconds) {
        return Error::InvalidInGameTimeElement;
    }
    const auto [minutes, seconds, milliseconds]{totalMillisecondsToTimer(totalMilliseconds)};
    return InGameTime{minutes, seconds, milliseconds};
}

constexpr std::variant<std::monostate, InGameTime::Error> InGameTime::setMinutes(
        const std::uint16_t minutes) {
    if (minutes > kMaxMinutes) {
        return Error::InvalidInGameTimeElement;
    }
    m_minutes = minutes;
    return {};
}

constexpr std::variant<std::monostate, InGameTime::Error> InGameTime::setSeconds(
        const std::uint16_t seconds) {
    if (seconds > kMaxSeconds) {
        return Error::InvalidInGameTimeElement;
    }
    m_seconds = seconds;
    return {};
}

constexpr std::variant<std::monostate, InGameTime::Error> InGameTime::setMilliseconds(
        const std::uint16_t milliseconds) {
    if (milliseconds > kMaxMilliseconds) {
        return Error::InvalidInGameTimeElement;
    }
    m_milliseconds = milliseconds;
    return {};
}

constexpr InGameTime &InGameTime::operator+=(const InGameTime &other) {
    std::uint32_t total{totalMilliseconds() + other.totalMilliseconds()};

    if (total > kMaxTotalMilliseconds) {
        total = kMaxTotalMilliseconds;
    }
    const auto [minutes, seconds, milliseconds]{totalMillisecondsToTimer(total)};
    m_minutes = minutes;
    m_seconds = seconds;
    m_milliseconds = milliseconds;
    return *this;
}

constexpr InGameTime &InGameTime::operator-=(const InGameTime &other) {
    const std::uint32_t total{totalMilliseconds() > other.totalMilliseconds() ?
                    totalMilliseconds() - other.totalMilliseconds() :
                    0U};
    const auto [minutes, seconds, milliseconds]{totalMillisecondsToTimer(total)};
    m_minutes = minutes;
    m_seconds = seconds;
    m_milliseconds = milliseconds;
    return *this;
}

/// @brief Adds two InGameTime objects, clamping time to 99m 59s 999ms if the result exceeds that.
constexpr InGameTime InGameTime::operator+(const InGameTime &other) const {
    InGameTime result{*this};
    result += other;
    return result;
}

/// @brief Subtracts two InGameTime objects, clamping time to 0m 0s 000ms if the result exceeds
/// that.
constexpr InGameTime InGameTime::operator-(const InGameTime &other) const {
    InGameTime result{*this};
    result -= other;
    return result;
}

constexpr auto InGameTime::operator<(const InGameTime &other) const {
    return std::tie(m_minutes, m_seconds, m_milliseconds) <
            std::tie(other.m_minutes, other.m_seconds, other.m_milliseconds);
}

constexpr auto InGameTime::operator<=(const InGameTime &other) const {
    return std::tie(m_minutes, m_seconds, m_milliseconds) <=
            std::tie(other.m_minutes, other.m_seconds, other.m_milliseconds);
}

constexpr auto InGameTime::operator==(const InGameTime &other) const {
    return std::tie(m_minutes, m_seconds, m_milliseconds) ==
            std::tie(other.m_minutes, other.m_seconds, other.m_milliseconds);
}

constexpr auto InGameTime::operator>=(const InGameTime &other) const {
    return std::tie(m_minutes, m_seconds, m_milliseconds) >=
            std::tie(other.m_minutes, other.m_seconds, other.m_milliseconds);
}

constexpr auto InGameTime::operator>(const InGameTime &other) const {
    return std::tie(m_minutes, m_seconds, m_milliseconds) >
            std::tie(other.m_minutes, other.m_seconds, other.m_milliseconds);
}

constexpr auto InGameTime::operator!=(const InGameTime &other) const {
    return std::tie(m_minutes, m_seconds, m_milliseconds) !=
            std::tie(other.m_minutes, other.m_seconds, other.m_milliseconds);
}

/// @brief Formats InGameTime object as 'MM:SS.sss'.
inline std::ostream &operator<<(std::ostream &out, const InGameTime &inGameTime) {
    // grab current ostream fill to restore after sending in game time
    const char previousFill = out.fill();

    out << std::setfill('0') << std::setw(2) << inGameTime.minutes() << ':' << std::setw(2)
        << inGameTime.seconds() << '.' << std::setw(3) << inGameTime.milliseconds();

    out << std::setfill(previousFill);
    return out;
}

} // namespace rkg::header

#endif // RKG_IN_GAME_TIME_HPP
