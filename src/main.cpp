/*
 * Copyright (c) 2023 st1koo <https://github.com/st1koo>
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
 */


#include "main.h"



void logger(const char* str) { std::cout << str << std::endl; }
void logger(std::string str) { std::cout << str.c_str() << std::endl; }



void __attribute__((constructor)) libLoad();
void __attribute__((destructor))  libUnload();



void MainThread() {

    logger("Loading hooks & interfaces...");


    Interfaces::initInterfaces();

    NetvarManager::setup();

    Hooks::initHooks();

    while(true) {
        Modules::Radar::run();
    }
    
}



void libLoad() {

    std::thread mainThread(MainThread); 
    

    mainThread.detach();

}



void libUnload() {

    logger("Unloading hooks...");

    Hooks::unloadHooks();

}