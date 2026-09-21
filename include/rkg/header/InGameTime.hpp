#ifndef RKG_IN_GAME_TIME_HPP
#define RKG_IN_GAME_TIME_HPP

#include <cstdint>
#include <expected>
#include <iostream>
#include <iomanip>

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

        return {.minutes = minutes, .seconds = seconds, .milliseconds = milliseconds};
    }

public:
    static constexpr std::uint16_t kMaxMinutes{99};
    static constexpr std::uint16_t kMaxSeconds{59};
    static constexpr std::uint16_t kMaxMilliseconds{999};
    /// @brief 5,999,999 ms = 99m 59s 999ms
    static constexpr std::uint32_t kMaxTotalMilliseconds{5'999'999};

    [[nodiscard]] static constexpr std::expected<InGameTime, Error> create(std::uint16_t minutes,
            std::uint16_t seconds, std::uint16_t milliseconds);
    [[nodiscard]] static constexpr std::expected<InGameTime, Error> createFromTotalMilliseconds(
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

    constexpr std::expected<void, InGameTime::Error> setMinutes(std::uint16_t minutes);
    constexpr std::expected<void, InGameTime::Error> setSeconds(std::uint16_t seconds);
    constexpr std::expected<void, InGameTime::Error> setMilliseconds(std::uint16_t milliseconds);

    friend constexpr InGameTime operator+(const InGameTime &i1, const InGameTime &i2);
    friend constexpr InGameTime operator-(const InGameTime &i1, const InGameTime &i2);
};

constexpr std::uint32_t InGameTime::totalMilliseconds() const {
    return minutes() * 60'000U + seconds() * 1'000U + milliseconds();
}

constexpr InGameTime::InGameTime(const std::uint16_t minutes, const std::uint16_t seconds,
        const std::uint16_t milliseconds)
    : m_minutes{minutes}, m_seconds{seconds}, m_milliseconds{milliseconds} {}

constexpr std::expected<InGameTime, InGameTime::Error> InGameTime::create(
        const std::uint16_t minutes, const std::uint16_t seconds,
        const std::uint16_t milliseconds) {
    if (minutes > kMaxMinutes || seconds > kMaxSeconds || milliseconds > kMaxMilliseconds) {
        return std::unexpected(Error::InvalidInGameTimeElement);
    }

    return InGameTime{minutes, seconds, milliseconds};
}

constexpr std::expected<InGameTime, InGameTime::Error> InGameTime::createFromTotalMilliseconds(
        const std::uint32_t totalMilliseconds) {
    if (totalMilliseconds > kMaxTotalMilliseconds) {
        return std::unexpected(Error::InvalidInGameTimeElement);
    }
    const auto timer{totalMillisecondsToTimer(totalMilliseconds)};
    return InGameTime{timer.minutes, timer.seconds, timer.milliseconds};
}

constexpr std::expected<void, InGameTime::Error> InGameTime::setMinutes(
        const std::uint16_t minutes) {
    if (minutes > kMaxMinutes) {
        return std::unexpected(Error::InvalidInGameTimeElement);
    }
    m_minutes = minutes;
    return {};
}

constexpr std::expected<void, InGameTime::Error> InGameTime::setSeconds(
        const std::uint16_t seconds) {
    if (seconds > kMaxSeconds) {
        return std::unexpected(Error::InvalidInGameTimeElement);
    }
    m_seconds = seconds;
    return {};
}

constexpr std::expected<void, InGameTime::Error> InGameTime::setMilliseconds(
        const std::uint16_t milliseconds) {
    if (milliseconds > kMaxMilliseconds) {
        return std::unexpected(Error::InvalidInGameTimeElement);
    }
    m_milliseconds = milliseconds;
    return {};
}

/// @brief Adds two InGameTime objects, clamping time to 99m 59s 999ms if the result exceeds that.
constexpr InGameTime operator+(const InGameTime &i1, const InGameTime &i2) {
    std::uint32_t totalMilliseconds{i1.totalMilliseconds() + i2.totalMilliseconds()};

    if (totalMilliseconds > InGameTime::kMaxTotalMilliseconds) {
        totalMilliseconds = InGameTime::kMaxTotalMilliseconds;
    }
    const auto timer{InGameTime::totalMillisecondsToTimer(totalMilliseconds)};
    return InGameTime{timer.minutes, timer.seconds, timer.milliseconds};
}

/// @brief Adds two InGameTime objects, clamping time to 0m 0s 000ms if the result exceeds that.
constexpr InGameTime operator-(const InGameTime &i1, const InGameTime &i2) {
    const std::uint32_t totalMilliseconds{i1.totalMilliseconds() > i2.totalMilliseconds() ?
                    i1.totalMilliseconds() - i2.totalMilliseconds() :
                    0U};
    const auto timer{InGameTime::totalMillisecondsToTimer(totalMilliseconds)};
    return InGameTime{timer.minutes, timer.seconds, timer.milliseconds};
}

/// @brief Formats InGameTime object as 'MM:SS.sss'.
constexpr std::ostream& operator<<(std::ostream& out, const InGameTime& inGameTime) {
    // grab current ostream fill to restore after sending in game time
    char previousFill = out.fill();

    out << std::setfill('0') << std::setw(2) << inGameTime.minutes() << ':'
        << std::setw(2) << inGameTime.seconds() << '.' << std::setw(3)
        << inGameTime.milliseconds();

    out << std::setfill(previousFill);
    return out;
}

} // namespace rkg::header

#endif // RKG_IN_GAME_TIME_HPP
