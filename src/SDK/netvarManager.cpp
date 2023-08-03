/*
 * Copyright (c) 2023 st1koo <https://github.com/st1koo>
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
 */


#include "sdk.h"



void NetvarManager::dump(const char *baseClass, RecvTable *table, uint32_t offset) {


    for (uint32_t i = 0; i < table->m_nProps; i++) { 


        RecvProp *thisProp = &table->m_pProps[i];

        if (!thisProp || isdigit(thisProp->m_pVarName[0])) continue;
        if (fnv::hash(thisProp->m_pVarName) == fnv::hashConst("baseclass")) continue; 
        if (thisProp->m_RecvType == 6 && thisProp->m_pDataTable && thisProp->m_pDataTable->m_pNetTableName[0] == 'D') {
            dump(baseClass, thisProp->m_pDataTable, thisProp->m_Offset + offset);
        }
        char name[128] = "";

        snprintf(name, 128, "%s->%s", baseClass, thisProp->m_pVarName);

        netvarMap[fnv::hash(name)] = thisProp->m_Offset + offset;
    }
}
void NetvarManager::setup() {
    
    logger("Getting netvars...");

    for (ClientClass *clientClass = Interfaces::client->GetAllClasses(); clientClass; clientClass = clientClass->m_pNext) { 

        if (clientClass->m_pRecvTable) dump(clientClass->m_pNetworkName, clientClass->m_pRecvTable, 0);

    }

}