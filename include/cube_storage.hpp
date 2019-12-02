#ifndef _CUBE_STORAGE_HPP_
#define _CUBE_STORAGE_HPP_

#include <array>
#include <cstdint>

// Class that abstracts the storage of the cube from its functionality
struct CubeStorage{
public:
    using value_type = std::uint_fast8_t;

    using face_type = std::array<value_type, 9>;
    using cube_type = std::array<face_type, 6>;

    using face_size_type = typename face_type::size_type;
    using cube_size_type = typename cube_type::size_type;

    using reference       = typename face_type::reference;
    using const_reference = typename face_type::const_reference;

    using face_iterator               = typename face_type::iterator;
    using face_const_iterator         = typename face_type::const_iterator;
    using face_reverse_iterator       = typename face_type::reverse_iterator;
    using face_const_reverse_iterator = typename face_type::const_reverse_iterator;

    using cube_iterator               = typename cube_type::iterator;
    using cube_const_iterator         = typename cube_type::const_iterator;
    using cube_reverse_iterator       = typename cube_type::reverse_iterator;
    using cube_const_reverse_iterator = typename cube_type::const_reverse_iterator;

    // To access a specific face, use these variables
    static constexpr cube_size_type UP    = 0;
    static constexpr cube_size_type FRONT = 1;
    static constexpr cube_size_type RIGHT = 2;
    static constexpr cube_size_type BACK  = 3;
    static constexpr cube_size_type LEFT  = 4;
    static constexpr cube_size_type DOWN  = 5;

    // Returns the storage to its initial state
    constexpr void reset() noexcept {
        m_data = {{
            {UP   , UP   , UP   , UP   , UP   , UP   , UP   , UP   , UP   },
            {FRONT, FRONT, FRONT, FRONT, FRONT, FRONT, FRONT, FRONT, FRONT},
            {RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT},
            {BACK , BACK , BACK , BACK , BACK , BACK , BACK , BACK , BACK },
            {LEFT , LEFT , LEFT , LEFT , LEFT , LEFT , LEFT , LEFT , LEFT },
            {DOWN , DOWN , DOWN , DOWN , DOWN , DOWN , DOWN , DOWN , DOWN }
        }};
    }

    // Access a specific sticker by face and position inside the face
    [[nodiscard]] constexpr reference
    get(cube_size_type face, face_size_type pos) noexcept {
        return m_data[face][pos];
    }

    [[nodiscard]] constexpr const_reference
    get(cube_size_type face, face_size_type pos) const noexcept {
        return m_data[face][pos];
    }

    [[nodiscard]] constexpr reference
    operator()(cube_size_type face, face_size_type pos) noexcept {
        return get(face, pos);
    }

    [[nodiscard]] constexpr const_reference
    operator()(cube_size_type face, face_size_type pos) const noexcept {
        return get(face, pos);
    }

    // Iterator functions to iterate through each face of the cube.
    constexpr cube_iterator       begin()       noexcept{ return m_data.begin(); }
    constexpr cube_const_iterator begin() const noexcept{ return m_data.begin(); }

    constexpr cube_iterator       end()       noexcept{ return m_data.end(); }
    constexpr cube_const_iterator end() const noexcept{ return m_data.end(); }

    constexpr cube_reverse_iterator       rbegin()       noexcept{ return m_data.rbegin(); }
    constexpr cube_const_reverse_iterator rbegin() const noexcept{ return m_data.rbegin(); }

    constexpr cube_reverse_iterator       rend()       noexcept{ return m_data.rend(); }
    constexpr cube_const_reverse_iterator rend() const noexcept{ return m_data.rend(); }

    constexpr cube_const_iterator cbegin() const noexcept{ return m_data.cbegin(); }
    constexpr cube_const_iterator cend()   const noexcept{ return m_data.cend();   }

    constexpr cube_const_reverse_iterator crbegin() const noexcept{ return m_data.crbegin(); }
    constexpr cube_const_reverse_iterator crend()   const noexcept{ return m_data.crend();   }

    /***********************************************/

    // Iterators to iterate through the stikers of a specific face
    constexpr face_iterator       begin(cube_size_type face)       noexcept{ return m_data[face].begin(); }
    constexpr face_const_iterator begin(cube_size_type face) const noexcept{ return m_data[face].begin(); }

    constexpr face_iterator       end(cube_size_type face)       noexcept{ return m_data[face].end(); }
    constexpr face_const_iterator end(cube_size_type face) const noexcept{ return m_data[face].end(); }

    constexpr face_reverse_iterator       rbegin(cube_size_type face)       noexcept{ return m_data[face].rbegin(); }
    constexpr face_const_reverse_iterator rbegin(cube_size_type face) const noexcept{ return m_data[face].rbegin(); }

    constexpr face_reverse_iterator       rend(cube_size_type face)       noexcept{ return m_data[face].rend(); }
    constexpr face_const_reverse_iterator rend(cube_size_type face) const noexcept{ return m_data[face].rend(); }

    constexpr face_const_iterator cbegin(cube_size_type face) const noexcept{ return m_data[face].cbegin(); }
    constexpr face_const_iterator cend(cube_size_type face)   const noexcept{ return m_data[face].cend();   }

    constexpr face_const_reverse_iterator crbegin(cube_size_type face) const noexcept{ return m_data[face].crbegin(); }
    constexpr face_const_reverse_iterator crend(cube_size_type face)   const noexcept{ return m_data[face].crend();   }

private:
    // This is the representation in memory of the cube
    cube_type m_data{{
        {UP   , UP   , UP   , UP   , UP   , UP   , UP   , UP   , UP   },
        {FRONT, FRONT, FRONT, FRONT, FRONT, FRONT, FRONT, FRONT, FRONT},
        {RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT},
        {BACK , BACK , BACK , BACK , BACK , BACK , BACK , BACK , BACK },
        {LEFT , LEFT , LEFT , LEFT , LEFT , LEFT , LEFT , LEFT , LEFT },
        {DOWN , DOWN , DOWN , DOWN , DOWN , DOWN , DOWN , DOWN , DOWN }
    }};
};

#endif
