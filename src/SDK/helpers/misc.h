/*
 * Copyright (c) 2023 st1koo <https://github.com/st1koo>
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
 */

#pragma once



inline uintptr_t getAbsoluteAddress(uintptr_t pointer, int offset, int size) {
	return pointer + *reinterpret_cast<int32_t *>(pointer + offset) + size;
}


inline void**& getVTable(void *c, size_t offset = 0) {
	return *reinterpret_cast<void ***>((size_t) c + offset);
}


template <typename T>
inline T getVirtualFunc(void *c, size_t i, size_t offset = 0) {
    return reinterpret_cast<T>(getVTable(c, offset)[i]);
}