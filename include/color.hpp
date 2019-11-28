#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include <array>
#include <cstdint>
#include <ostream>
#include <tuple>

class Color{
public:
    using value_type      = std::uint8_t;
    using array_type      = std::array<value_type, 3>;
    using tuple_type      = std::tuple<value_type, value_type, value_type>;

    using size_type       = typename array_type::size_type;
    using reference       = typename array_type::reference;
    using const_reference = typename array_type::const_reference;

    constexpr Color()                        noexcept = default;
    constexpr Color(const Color&)            noexcept = default;
    constexpr Color(Color&&)                 noexcept = default;
    constexpr Color& operator=(const Color&) noexcept = default;
    constexpr Color& operator=(Color&&)      noexcept = default;
    ~Color()                                 noexcept = default;

    constexpr Color(value_type R, value_type G, value_type B) noexcept
        : m_RGB{R, G, B}{}
    constexpr explicit Color(value_type (&RGB)[3])            noexcept
        : m_RGB{RGB[0], RGB[1], RGB[2]}{}
    constexpr explicit Color(const array_type &RGB)           noexcept
        : m_RGB{RGB}{}
    constexpr explicit Color(const tuple_type &RGB)           noexcept
        : m_RGB{std::get<0>(RGB), std::get<1>(RGB), std::get<2>(RGB)}{}

    constexpr reference       R()       noexcept{ return m_RGB[0]; }
    constexpr const_reference R() const noexcept{ return m_RGB[0]; }
    constexpr reference       G()       noexcept{ return m_RGB[1]; }
    constexpr const_reference G() const noexcept{ return m_RGB[1]; }
    constexpr reference       B()       noexcept{ return m_RGB[2]; }
    constexpr const_reference B() const noexcept{ return m_RGB[2]; }

    constexpr reference       operator[](unsigned i)       noexcept{ return m_RGB[i]; }
    constexpr const_reference operator[](unsigned i) const noexcept{ return m_RGB[i]; }

    constexpr array_type as_array() const noexcept{
        return m_RGB;
    }
    constexpr tuple_type as_tuple() const noexcept{
        return std::make_tuple(m_RGB[0], m_RGB[1], m_RGB[2]);
    }

    template <typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits> &os, const Color &color){
        os  << "\x1b[38;2;"
            << std::to_string(color.m_RGB[0]) << ';'
            << std::to_string(color.m_RGB[1]) << ';'
            << std::to_string(color.m_RGB[2]) << 'm';

        return os;
    }

private:
    array_type m_RGB{255, 255, 255};
};

#endif
