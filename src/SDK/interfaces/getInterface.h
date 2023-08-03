/*
 * Copyright (c) 2023 st1koo <https://github.com/st1koo>
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
 */

#pragma once


#include "../../main.h"

typedef void* (*InstantiateInterfaceFn)();

class InterfaceReg {
public:
    InstantiateInterfaceFn m_CreateFn;
    const char* m_pName;
    InterfaceReg* m_pNext;
};



template <typename T>
T* getInterface(const char* libname, const char* name, bool exactVersion = false) {

    void* handle = dlopen(libname, RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL); 

    if (!handle) {
        logger("getInterface() error: Could not open library!");


        dlclose(handle);
        return nullptr;
    }


    void* addr = dlsym(handle, "s_pInterfaceRegs");

    if (!addr) {
        logger("getInterface() error: Function address could not be found!");


        dlclose(handle);
        return nullptr;
    }

    InterfaceReg* interfaces = *reinterpret_cast<InterfaceReg**>(addr);

    dlclose(handle);

    for (InterfaceReg* cur = interfaces; cur; cur = cur->m_pNext) {

        if (exactVersion) {
            if (strcmp(cur->m_pName, name) == 0) return reinterpret_cast<T*>(cur->m_CreateFn());
        } else {
            if (strstr(cur->m_pName, name) && strlen(cur->m_pName) - 3 == strlen(name)) return reinterpret_cast<T*>(cur->m_CreateFn());
        }

    }
}