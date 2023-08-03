/*
 * Copyright (c) 2023 st1koo <https://github.com/st1koo>
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
 */


#include "interfaces.h"


typedef IClientMode* (*getClientModeFunc)();


void Interfaces::initInterfaces() {


    client       = getInterface<IBaseClientDLL>("./csgo/bin/linux64/client_client.so", "VClient");
    entityList   = getInterface<IEntityList>("./csgo/bin/linux64/client_client.so", "VClientEntityList");
    engineClient = getInterface<IVEngineClient>("./bin/linux64/engine_client.so", "VEngineClient");



    uintptr_t hudProcessInput = reinterpret_cast<uintptr_t>(getVTable(client)[10]);
    
    getClientModeFunc getClientMode = reinterpret_cast<getClientModeFunc>(getAbsoluteAddress(hudProcessInput + 11, 1, 5)); 
    clientMode = getClientMode();
}