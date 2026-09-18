#include <rkg/header/InGameTime.hpp>

InGameTime::InGameTime(const std::uint16_t minutes, const std::uint16_t seconds,
        const std::uint16_t milliseconds)
    : m_minutes{minutes}, m_seconds{seconds}, m_milliseconds{milliseconds} {}

std::expected<InGameTime, InGameTime::Error> InGameTime::create(const std::uint16_t minutes,
        const std::uint16_t seconds, const std::uint16_t milliseconds) {
    if (minutes > kMaxMinutes || seconds > kMaxSeconds || milliseconds > kMaxMilliseconds) {
        return std::unexpected(Error::InvalidInGameTimeElement);
    }

    return InGameTime{minutes, seconds, milliseconds};
}

std::expected<void, InGameTime::Error> InGameTime::setMinutes(const std::uint16_t minutes) {
    if (minutes > kMaxMinutes) {
        return std::unexpected(Error::InvalidInGameTimeElement);
    }
    m_minutes = minutes;
    return {};
}

std::expected<void, InGameTime::Error> InGameTime::setSeconds(const std::uint16_t seconds) {
    if (seconds > kMaxSeconds) {
        return std::unexpected(Error::InvalidInGameTimeElement);
    }
    m_seconds = seconds;
    return {};
}

std::expected<void, InGameTime::Error> InGameTime::setMilliseconds(const std::uint16_t milliseconds) {
    if (milliseconds > kMaxMilliseconds) {
        return std::unexpected(Error::InvalidInGameTimeElement);
    }
    m_milliseconds = milliseconds;
    return {};
}
