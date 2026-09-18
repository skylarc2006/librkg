#ifndef RKG_IN_GAME_TIME_HPP
#define RKG_IN_GAME_TIME_HPP

#include <cstdint>
#include <expected>

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

    InGameTime(std::uint16_t minutes, std::uint16_t seconds, std::uint16_t milliseconds);

public:
    static constexpr std::uint16_t kMaxMinutes{99};
    static constexpr std::uint16_t kMaxSeconds{59};
    static constexpr std::uint16_t kMaxMilliseconds{999};

    static std::expected<InGameTime, Error> create(std::uint16_t minutes, std::uint16_t seconds,
            std::uint16_t milliseconds);

    [[nodiscard]] std::uint16_t minutes() const {
        return m_minutes;
    }
    [[nodiscard]] std::uint16_t seconds() const {
        return m_seconds;
    }
    [[nodiscard]] std::uint16_t milliseconds() const {
        return m_milliseconds;
    }

    std::expected<void, InGameTime::Error> setMinutes(std::uint16_t minutes);
    std::expected<void, InGameTime::Error> setSeconds(std::uint16_t seconds);
    std::expected<void, InGameTime::Error> setMilliseconds(std::uint16_t milliseconds);

    // TODO: operator overloads
};

#endif // RKG_IN_GAME_TIME_HPP
