/*
 * Copyright (c) 2023 st1koo <https://github.com/st1koo>
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
 */


#include "../modules.h"



void Modules::Radar::run() {


    if (!Config::Misc::radarEnabled) return; 


    for (int i = 1; i <= Interfaces::engineClient->GetMaxClients(); i++) {
        CEntity *entity = Interfaces::entityList->GetClientEntity(i); 

        if (!entity) continue; 



        entity->spotted() = true; 
    }

}