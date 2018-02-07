#pragma once

#include <array>
#include <algorithm>
#include <utility>

template<typename T>
struct storage{
      std::array<T, 54> data;

      using value_type = typename decltype(data)::value_type;
      using size_type = typename decltype(data)::size_type;
      using reference = typename decltype(data)::reference;
      using const_reference = typename decltype(data)::const_reference;
      using iterator = typename decltype(data)::iterator;
      using const_iterator = typename decltype(data)::const_iterator;
      using reverse_iterator = typename decltype(data)::reverse_iterator;
      using const_reverse_iterator = typename decltype(data)::const_reverse_iterator;

      constexpr reference at(size_type face, size_type pos){
         return data.at(face+pos);
      }
      constexpr const_reference at(size_type face, size_type pos) const{
         return data.at(face+pos);
      }

      constexpr reference operator()(size_type face, size_type pos){
         return data[face+pos];
      }
      constexpr const_reference operator()(size_type face, size_type pos) const{
         return data[face+pos];
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
