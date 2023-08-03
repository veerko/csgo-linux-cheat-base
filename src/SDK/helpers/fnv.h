/*
 * Copyright (c) 2023 st1koo <https://github.com/st1koo>
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
 */


#pragma once


#include <cstring>
#include <cstdint>
 

namespace fnv {
    inline constexpr uint32_t base = 0x811C9DC5;
    inline constexpr uint32_t prime = 0x1000193;

    constexpr uint32_t hashConst(const char* data, const uint32_t value = base) noexcept {
        return (data[0] == '\0') ? value : hashConst(&data[1], (value ^ uint32_t(data[0])) * prime);
    }

    inline uint32_t hash(const char* data) noexcept {
        uint32_t hashed = base;
 
        for (size_t i = 0U; i < strlen(data); ++i) {
            hashed ^= data[i];
            hashed *= prime;
        }
 
        return hashed;
    }
}