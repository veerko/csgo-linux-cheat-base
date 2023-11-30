/*
 * Copyright (c) 2023 st1koo <https://github.com/st1koo>
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
 */


#include "menu.h"



void Menu::onPollEvent(SDL_Event* event, const int result) {
    if (result && ImGui_ImplSDL2_ProcessEvent(event) && Menu::active) {
        event->type = 0;
    }
}


void Menu::onSwapWindow(SDL_Window* window) {

    if (!isInit) {
        gl3wInit();
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplOpenGL3_Init("#version 100");
        ImGui_ImplSDL2_InitForOpenGL(window, nullptr);

        isInit = true;
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);

    ImGuiIO& io = ImGui::GetIO();

    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    screenSizeX = w;
    screenSizeY = h;

    io.DisplaySize = ImVec2((float)w, (float)h);

    ImGui::NewFrame();

    
    if (Menu::active) {
        io.MouseDrawCursor = true;
        Menu::showMenu();
    } else {
        io.MouseDrawCursor = false;
    }


    if (ImGui::IsKeyPressed(Menu::openKey, false)) {
        Menu::active = !Menu::active;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}



void Menu::showMenu() {


    ImGui::Begin(("csgo-linux-cheat-base v" + version + " by st1koo").c_str(), &Menu::active);



    if (ImGui::Button("Aimbot", buttonWidth)) Menu::currentPage = 0;
    
    ImGui::SameLine();
    if (ImGui::Button("Visuals", buttonWidth)) Menu::currentPage = 1;
    
    ImGui::SameLine();
    if (ImGui::Button("Misc", buttonWidth)) Menu::currentPage = 2;

    ImGui::SameLine();
    if (ImGui::Button("Info", buttonWidth)) Menu::currentPage = 3;
uhy


    switch (currentPage) {
        case 1:
            Menu::showVisualsPage();
            break;
        case 2:
            Menu::showMiscPage();
            break;
        case 3:
            Menu::showInfoPage();
            break;
        case 4: 
            Menu::showSkinchanger();
        default:
            Menu::showAimbotPage();
            Menu::currentPage = 0;
    }

    ImGui::End();
}