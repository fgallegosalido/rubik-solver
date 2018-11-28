#ifndef _CUBE_STORAGE_HPP_
#define _CUBE_STORAGE_HPP_

#include <array>

template<typename T>
struct CubeStorage{
    using storage = std::array<std::array<T, 9>, 6>;

    storage data;

    using value_type             = typename storage::value_type;
    using size_type              = typename storage::size_type;
    using reference              = typename storage::reference;
    using const_reference        = typename storage::const_reference;
    using iterator               = typename storage::iterator;
    using const_iterator         = typename storage::const_iterator;
    using reverse_iterator       = typename storage::reverse_iterator;
    using const_reverse_iterator = typename storage::const_reverse_iterator;

    static constexpr size_type UP    = 0;
    static constexpr size_type FRONT = 1;
    static constexpr size_type RIGHT = 2;
    static constexpr size_type BACK  = 3;
    static constexpr size_type LEFT  = 4;
    static constexpr size_type DOWN  = 5;

    constexpr typename value_type::reference operator()(size_type face, size_type pos) noexcept {
        return data[face][pos];
    }
    constexpr typename value_type::const_reference operator()(size_type face, size_type pos) const noexcept {
        return data[face][pos];
    }

    /* Iterator functions to iterate through the storage
     *
     * It's based on the array's iterator, so this is just a wrapper
     */
    constexpr iterator begin() noexcept{
        return data.begin();
    }
    constexpr const_iterator begin() const noexcept{
        return data.begin();
    }

    constexpr iterator end() noexcept{
        return data.end();
    }
    constexpr const_iterator end() const noexcept{
        return data.end();
    }

    constexpr reverse_iterator rbegin() noexcept{
        return data.rbegin();
    }
    constexpr const_reverse_iterator rbegin() const noexcept{
        return data.rbegin();
    }

    constexpr reverse_iterator rend() noexcept{
        return data.rend();
    }
    constexpr const_reverse_iterator rend() const noexcept{
        return data.rend();
    }

    constexpr const_iterator cbegin() noexcept{
        return data.cbegin();
    }
    constexpr const_iterator cend() noexcept{
        return data.cend();
    }

    constexpr const_reverse_iterator crbegin() noexcept{
        return data.crbegin();
    }
    constexpr const_reverse_iterator crend() noexcept{
        return data.crend();
    }
};

#endif
