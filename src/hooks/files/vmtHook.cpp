/*
 * Copyright (c) 2023 st1koo <https://github.com/st1koo>
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
 */



#include "../hooks.h"


int pageSize = sysconf(_SC_PAGE_SIZE);
int pageMask = ~(pageSize - 1);


/**
 * 
 * @param interface 
 * @param hookFunction 
 * @param offset 
 * @returns 
 */
void *Hooks::VMT::hookVMT(void *interface, void *hookFunction, int offset) {

    intptr_t vTableBase = *((intptr_t *) interface);


    intptr_t vTableFunc = vTableBase + sizeof(intptr_t) * offset;

    intptr_t vTableOriginalFunc = *((intptr_t *) vTableFunc);


    mprotect((void *) (vTableFunc & pageMask), pageSize, PROT_READ | PROT_WRITE | PROT_EXEC);


    *((intptr_t *) vTableFunc) = (intptr_t) hookFunction;



    mprotect((void *) (vTableFunc & pageMask), pageSize, PROT_READ | PROT_EXEC);



    return (void *) vTableOriginalFunc;
}