/*
 * Copyright (c) 2023 st1koo <https://github.com/st1koo>
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
 */

#include "../../main.h"


const char *_hitboxes[]{"Head", "Neck", "Chest", "Stomach", "Pelvis"};


void Menu::showAimbotPage() {
    ImGui::Checkbox("Active", &Config::Aimbot::enabled);
    ImGui::SliderFloat("FOV", &Config::Aimbot::fov, 0.0, 360.0, "%.1f");
    ImGui::SliderFloat("Smoothness", &Config::Aimbot::smoothness, 0.0, 100.0, "%.1f");
    ImGui::Combo("Hitbox", &Config::Aimbot::hitboxSelected, _hitboxes, IM_ARRAYSIZE(_hitboxes));
    ImGui::Checkbox("Silent Aim", &Config::Aimbot::silentAimEnabled);
    ImGui::Checkbox("Triggerbot", &Config::Aimbot::triggerbotEnabled);
    ImGui::SliderInt("Delay", &Config::Aimbot::triggerbotDelay, 0, 2500);
}