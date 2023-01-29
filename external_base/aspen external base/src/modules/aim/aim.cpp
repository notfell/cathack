#include "../../all.h"

namespace aim
{
    UINT32 getClosetPlayer()
    { 
        UINT32 tempPlayer = NULL;

        float maxDistance = gui::maxDistances;

        for (const auto& entity : world::getEntities())
        {
            float distance = utils::getDistance3D(entity.positionHead, localPlayer::getPosition());
           
            if (entity.health > 0)
            {
                if (gui::bAimFov)
                {
                    vector3 dTarget = utils::calculateAngles(localPlayer::getHeadPosition(), entity.positionHead);
                    float spaceYaw = localPlayer::getRotation().x - dTarget.x;
                    float spacePitch = localPlayer::getRotation().y - dTarget.y;

                    if (spaceYaw < (gui::aimFov * 100) && spaceYaw > -(gui::aimFov * 100) && spacePitch < (gui::aimFov * 100) && spacePitch > -(gui::aimFov * 100))
                    {
                        if (distance < maxDistance)
                        {
                            maxDistance = distance;
                            tempPlayer = entity.base;
                        }
                    }    
                }
                else 
                {
                    if (distance < maxDistance)
                    {
                        maxDistance = distance;
                        tempPlayer = entity.base;
                    }
                } 
            }
        }
        return tempPlayer;
    }

    void fov()
    {
        static float fovLerp;

        fovLerp = utils::lerp(fovLerp, gui::aimFov, 0.1f);

        components::circle(0.5f + (gui::aimFov / 2), 0.5f + (gui::aimFov / 2), fovLerp, 3.0f, 0.0f, 0.0f, 0.0f, 1.0f, false);
        components::circle(0.5f + (gui::aimFov / 2), 0.5f + (gui::aimFov / 2), fovLerp, 1.0f, (float)gui::aimFovColor.r / 255.0f, (float)gui::aimFovColor.g / 255.0f, (float)gui::aimFovColor.b / 255.0f, 1.0f, false);
    }

    void aimbot(aimType _type, time_t _frametime)
    {
        playerEntity player;

        player.base = getClosetPlayer();

        if (player.base == NULL)
        {
            return;
        }

        ReadProcessMemory(bah::hProcess, (PBYTE*)(player.base + 0x225), &player.name, sizeof(player.name), nullptr);

        player.health = mem::read<int>(player.base + 0xF8, bah::hProcess);
        player.positionHead = mem::read<vector3>(player.base + 0x4, bah::hProcess);
        player.positionFeet = mem::read<vector3>(player.base + 0x34, bah::hProcess);
        player.team = mem::read<int>(player.base + 0x32C, bah::hProcess);

        float distance = utils::getDistance3D(player.positionHead, localPlayer::getPosition());
        vector3 dTarget = utils::calculateAngles(localPlayer::getHeadPosition(), player.positionHead);

        float spaceYaw = localPlayer::getRotation().x - dTarget.x;
        float spacePitch = localPlayer::getRotation().y - dTarget.y;

        switch (_type)
        {
            case aim::aimType::aim:
            {
                static vector3 previousRot;
               // vector3 test = { 0, 0, 0 };

                UINT32 localplayer = mem::read<UINT32>(bah::mainModule + PLAYER_BASE, bah::hProcess);

                if (localplayer)
                {
                    if (isKeyPressed(VK_XBUTTON2))
                    {
                        previousRot = utils::lerp(localPlayer::getRotation(), dTarget, gui::aimSmooth * _frametime * 0.1f);

                        mem::write(localplayer + 0x40, bah::hProcess, previousRot.x);
                        mem::write(localplayer + 0x44, bah::hProcess, previousRot.y);
                    }             
                }
            }
            break;

            case aim::aimType::silent:
            {

            }
            break;

            case aim::aimType::window:
            {
                // Window title header.
                components::rect(gui::twP.x + (gui::twSize.w / 2), gui::twP.y + (gui::twSize.h / 2), gui::twSize.w, gui::twSize.h, 0.04f, 0.04f, 0.04f, 1.0f); // back
                components::rect(0.005f + (gui::twSize.w / 2), gui::twP.y + (gui::twSize.h / 2), gui::twSize.w, gui::twSize.h, (float)gui::accentColor.r / 255.0f, (float)gui::accentColor.g / 255.0f, (float)gui::accentColor.b / 255.0f, 1.0f, 0.2f); // border

                const std::string title = "target info";
                char* name = player.name;

                // Window header title text.
                components::text(title, 0.005f + 0.005f, gui::twP.y + (gui::twSize.h / 2) - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, 1.0f, gui::textType::left);
                components::text("[" + static_cast<std::string>(name) + "]", 0.005f + 0.005f + 0.001f + (title.length() * (gui::basicTextSize / 2)), gui::twP.y + (gui::twSize.h / 2) - gui::basicTextSize, gui::basicTextSize, (float)gui::accentColor.r / 255.0f, (float)gui::accentColor.g / 255.0f, (float)gui::accentColor.b / 255.0f, 1.0f, gui::textType::left);

                // Back
                components::rect(gui::twP.x + (gui::twSize.w / 2), gui::twP.y + (gui::twSize.h * 2.5f), gui::twSize.w, gui::twSize.h * 3, 0.04f, 0.04f, 0.04f, 1.0f); // back
                components::rect(gui::twP.x + (gui::twSize.w / 2), gui::twP.y + (gui::twSize.h * 2.5f), gui::twSize.w, gui::twSize.h * 3, (float)gui::accentColor.r / 255.0f, (float)gui::accentColor.g / 255.0f, (float)gui::accentColor.b / 255.0f, 1.0f, 0.2f); // border

                // Infos
                const std::string healthStr = "health";
                int healthPlr = player.health;
                components::text(healthStr, 0.005f + 0.005f, gui::twP.y + (gui::twSize.h * 1.5f) - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, 1.0f, gui::textType::left);
                components::text("[" + std::to_string(player.health) + "]", 0.005f + 0.005f + 0.001f + (healthStr.length() * (gui::basicTextSize / 2)), gui::twP.y + (gui::twSize.h * 1.5f) - gui::basicTextSize, gui::basicTextSize, (float)gui::accentColor.r / 255.0f, (float)gui::accentColor.g / 255.0f, (float)gui::accentColor.b / 255.0f, 1.0f, gui::textType::left);

                const std::string distSTR = "distance";
                std::string newDist = utils::roundFloat(distance, 0);

                components::text(distSTR, 0.005f + 0.005f, gui::twP.y + (gui::twSize.h * 2) - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, 1.0f, gui::textType::left);
                components::text("[" + newDist + "m]", 0.005f + 0.005f + 0.001f + (distSTR.length() * (gui::basicTextSize / 2)), gui::twP.y + (gui::twSize.h * 2) - gui::basicTextSize, gui::basicTextSize, (float)gui::accentColor.r / 255.0f, (float)gui::accentColor.g / 255.0f, (float)gui::accentColor.b / 255.0f, 1.0f, gui::textType::left);
                
                components::text("yaw : " + std::to_string(spaceYaw) + " pitch : " + std::to_string(spacePitch), 0.005f + 0.005f, gui::twP.y + (gui::twSize.h * 2.5f) - gui::basicTextSize, gui::basicTextSize, (float)gui::accentColor.r / 255.0f, (float)gui::accentColor.g / 255.0f, (float)gui::accentColor.b / 255.0f, 1.0f, gui::textType::left);

            }
            break;

            case aim::aimType::line:
            {
                vector3 screenCoords;
                vector3 centerPosition = player.positionHead;

                if (utils::worldToScreen(centerPosition, screenCoords, localPlayer::getViewMatrix(), utils::screenWidth, utils::screenHeight))
                {
                    components::line(0.5f, 0.5f, (screenCoords.x / utils::screenWidth), (screenCoords.y / utils::screenHeight), 3.0f, 0.0f, 0.0f, 0.0f, 1.0f);
                    components::line(0.5f, 0.5f, (screenCoords.x / utils::screenWidth), (screenCoords.y / utils::screenHeight), 1.0f, (float)gui::aimLinesColor.r / 255.0f, (float)gui::aimLinesColor.g / 255.0f, (float)gui::aimLinesColor.b / 255.0f, (float)gui::aimLinesColor.a / 255.0f);

                }
            }
            break;


        }
    }
}

