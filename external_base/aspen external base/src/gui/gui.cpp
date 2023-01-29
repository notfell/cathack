#include "../all.h"

POINT cursor;

ULONGLONG components::keyPressPreviousTick = 0;
int components::keyPressDelay = 200;

bool showMenu = true;

float smooth = 3.0f;

bool watermark = true;
bool test = false;

int intest;
int intest2;

bool aimAssist;
bool windowTarget;
bool drawTarget;

bool discordRpc = true;

float gui::maxDistances = 500;

bool bAimSmooth;
float gui::aimSmooth = 0.1f;

bool gui::bAimFov = false;
float gui::aimFov = 0.05f;

std::vector<std::string> hitbox = {"head", "chest", "legs", "feet"};

bool name = true;
bool box = true;
bool filledBox = true;
bool health = true;
bool flags;
bool lines = false;
bool test2;

static int hitboxI = 0;

Discord* g_Discord;

namespace gui
{
	bool closeCalled = false;

	float alpha = 0.0f;

	void draw(int _width, int _height, time_t _frameTime)
	{

		// Retrieve screen size values.
		utils::screenWidth = _width;
		utils::screenHeight = _height;

		if (showMenu)
		{
			if (!closeCalled)
			{
				if (alpha < 1.0f)
				{
					alpha += _frameTime * (smooth * 0.001f);

					if (alpha > 1.0f)
					{
						alpha = 1.0f;
					}
				}
			}
		}

		if (closeCalled)
		{
			if (alpha > 0.0f)
			{
				alpha -= _frameTime * (smooth * 0.001f);

				if (alpha < 0.0f)
				{
					alpha = 0.0f;
				}
			}
			else
			{
				closeCalled = false;
				showMenu = false;
			}
		}

		utils::isKeyJustPressed(VK_INSERT, []
		{
			if (showMenu)
			{
				closeCalled = true;
			}
			else
			{
				showMenu = true;
			}
		});

		if (aimAssist)
			aim::aimbot(aim::aimType::aim, _frameTime);

		if (windowTarget)
			aim::aimbot(aim::aimType::window, _frameTime);

		if (drawTarget)
			aim::aimbot(aim::aimType::line, _frameTime);

		if (bAimFov)
			aim::fov();

		if (watermark)
			components::watermark();

		if (name)
			visuals::drawEntitiesEsp(visuals::espType::name, maxDistances);

		if (box)
			visuals::drawEntitiesEsp(visuals::espType::box, maxDistances);

		if (visuals::FilledBox)
			visuals::drawEntitiesEsp(visuals::espType::boxF, maxDistances);

		if (health)
			visuals::drawEntitiesEsp(visuals::espType::health, maxDistances);

		if (lines)
			visuals::drawEntitiesEsp(visuals::espType::lines, maxDistances);

		if (discordRpc)
		{
			g_Discord->Initialize();
			g_Discord->Update();
		}
		else
		{
			g_Discord->Shutdown();
		}

		if (showMenu)
		{
			components::menuBase(_width, _height, _frameTime);

			switch (gui::currentSubmenu)
			{
				case gui::submenu::mainMenu:
				{
					components::submenu("aim assistance", gui::submenu::aimAssistance);
					components::submenu("visuals", gui::submenu::visuals);
					components::submenu("misc", gui::submenu::misc);
					components::submenu("settings", gui::submenu::settings);

					components::option("unhook", []
					{
						utils::unHook();
					});
					
				}
				break;

				// aim assistance

				case gui::submenu::aimAssistance:
				{
					components::boolean("enable", aimAssist);

					//components::array("hitbox", hitbox, hitboxI);
					components::floatSlider("smooth value", aimSmooth, 0.1f, 1.0f, 0.1f);
					components::boolean("fov", bAimFov);

					components::breakOption("visuals");
					components::boolean("target window", windowTarget);
					components::boolean("target line", drawTarget);

					if (bAimFov)
					{
						components::breakOption("fov");
						components::floatSlider("fov size", gui::aimFov, 0.05f, 1.0f, 0.01f);
						components::intSlider("red", healthColor.r, 0, 255, 1);
						components::intSlider("green", healthColor.g, 0, 255, 1);
						components::intSlider("blue", healthColor.b, 0, 255, 1);
						components::intSlider("alpha", healthColor.a, 0, 255, 1);
					}						
					
					if (drawTarget)
					{
						components::breakOption("line");
						components::intSlider("red", aimLinesColor.r, 0, 255, 1);
						components::intSlider("green", aimLinesColor.g, 0, 255, 1);
						components::intSlider("blue", aimLinesColor.b, 0, 255, 1);
						components::intSlider("alpha", aimLinesColor.a, 0, 255, 1);
					}		
				}
				break;

				// visuals 					

				case gui::submenu::visuals:
				{
					components::submenu("players", gui::submenu::player);
					components::submenu("world", gui::submenu::world);				
				}
				break;

				// visuals->player
				
				case gui::submenu::player:
				{
					components::submenu("name", gui::submenu::name);
					components::submenu("box", gui::submenu::box);
					components::submenu("health", gui::submenu::health);
					components::submenu("flags", gui::submenu::flags);
					components::submenu("lines", gui::submenu::lines);
				}
				break;
				
				case gui::submenu::box:
				{
					components::submenu("box filled ", gui::submenu::boxF);
					components::boolean("box", box);
					components::breakOption("colors");
					components::intSlider("red", boxColor.r, 0, 255, 1);
					components::intSlider("green", boxColor.g, 0, 255, 1);
					components::intSlider("blue", boxColor.b, 0, 255, 1);
					components::intSlider("alpha", boxColor.a, 0, 255, 1);
				}
				break;

				case gui::submenu::boxF:
				{
					components::boolean("box", visuals::FilledBox);
					components::breakOption("colors");
					components::intSlider("red", boxFColor.r, 0, 255, 1);
					components::intSlider("green", boxFColor.g, 0, 255, 1);
					components::intSlider("blue", boxFColor.b, 0, 255, 1);
					components::intSlider("alpha", boxFColor.a, 0, 255, 1);
				}
				break;

				case gui::submenu::name:
				{
					components::boolean("name", name);
					components::breakOption("colors");
					components::intSlider("red", nameColor.r, 0, 255, 1);
					components::intSlider("green", nameColor.g, 0, 255, 1);
					components::intSlider("blue", nameColor.b, 0, 255, 1);
					components::intSlider("alpha", nameColor.a, 0, 255, 1);
				}
				break;

				case gui::submenu::health:
				{
					components::boolean("health", health);
					components::breakOption("colors");
					components::boolean("gradient", gradient);

					if (!gradient)
					{
						components::intSlider("red", healthColor.r, 0, 255, 1);
						components::intSlider("green", healthColor.g, 0, 255, 1);
						components::intSlider("blue", healthColor.b, 0, 255, 1);
						components::intSlider("alpha", healthColor.a, 0, 255, 1);
					}
				}
				break;

				case gui::submenu::flags:
				{
					components::boolean("flags #1", box);
					components::breakOption("todo !");
				}
				break;

				case gui::submenu::lines:
				{
					components::boolean("lines", lines);
					components::breakOption("colors");
					components::intSlider("red", healthColor.r, 0, 255, 1);
					components::intSlider("green", healthColor.g, 0, 255, 1);
					components::intSlider("blue", healthColor.b, 0, 255, 1);
					components::intSlider("alpha", healthColor.a, 0, 255, 1);
				}
				break;

				// visuals -> world

				case gui::submenu::world:
				{
					components::option("todo");
				}
				break;

				// visuals -> esp settings

				case gui::submenu::espSettings:
				{
				}
				break;

				// misc

				case gui::submenu::misc:
				{
					components::floatSlider("max distance", maxDistances, 10.0f, 1000.0f, 10.0f);
				}
				break;

				// settings

				case gui::submenu::settings:
				{
					components::submenu("windows", gui::submenu::windows);
					components::submenu("gui", gui::submenu::gui);
					components::boolean("discord rpc", discordRpc);
				}
				break;

				case gui::submenu::windows:
				{
					components::boolean("watermark", watermark);
				}
				break;

				case gui::submenu::gui:
				{
					components::floatSlider("menu x", gui::menuPosition.x, 0.0f, 1.0f, 0.01f);
					components::floatSlider("menu y", gui::menuPosition.y, 0.0f, 1.0f, 0.01f);

					components::breakOption("size");
					components::floatSlider("menu width", gui::menuSize.w, 0.0f, 1.0f, 0.01f);
					components::floatSlider("menu height", gui::menuSize.h, 0.0f, 1.0f, 0.01f);

					components::breakOption("anim");
					components::floatSlider("menu fading", smooth, 1.0f, 10.0f, 0.1f);
					components::floatSlider("smooth scroller", gui::smoothScrollingSpeed, 1.0f, 10.0f, 0.1f);

					components::breakOption("accent color");
					components::intSlider("red", accentColor.r, 0, 255, 1);
					components::intSlider("green", accentColor.g, 0, 255, 1);
					components::intSlider("blue", accentColor.b, 0, 255, 1);
					components::intSlider("alpha", accentColor.a, 0, 255, 1);
				}
				break;

				case gui::submenu::dev:
				{
					components::option("test set position", [] { localPlayer::setPosition(vector3(100.0f, 100.0f, 0.0f)); });
					components::option("test get position", []
					{
						vector3 position = localPlayer::getPosition();

						printf("\n%f | %f | %f\n", position.x, position.y, position.z);
					});

					components::breakOption("test 2");

					components::option("test set rotation", [] { localPlayer::setRotation(vector3(0.0f, 0.0f, 0.0f)); });
					components::option("test get rotation", []
					{
						vector3 rotation = localPlayer::getRotation();

						printf("\n%f | %f | %f\n", rotation.x, rotation.y, rotation.z);
					});
				}
				break;
			}	
		}	
	}
}