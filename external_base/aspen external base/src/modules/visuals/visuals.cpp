#include "../../all.h"

namespace visuals
{
	void colorGradient(int _health) //159, 251, 198)
	{
		gui::gradientHealth.r = 255 - gui::gradientHealth.g;
		gui::gradientHealth.g = (251 * _health) / 100;
		gui::gradientHealth.b = 198;
	}

	void drawEntitiesEsp(espType _type, int _distance)
	{
		for (const auto& entity : world::getEntities())
		{
			vector3 screenCoords;
			vector3 centerPosition = entity.positionHead;
			centerPosition.z -= 1.8f;

			if (utils::worldToScreen(centerPosition, screenCoords, localPlayer::getViewMatrix(), utils::screenWidth, utils::screenHeight))
			{
				float distance = utils::getDistance3D(centerPosition, localPlayer::getPosition());

				//printf("center position x -> %f y -> %f z -> %f\n", centerPosition.x, centerPosition.y, centerPosition.z);

				if (distance != 0.0f && distance <= _distance)
				{
					float clamped = 5.0f / distance;

					switch (_type)
					{
						case visuals::espType::name:
						{
							float clampedTextSize = clamped;

							if (clampedTextSize < 0.20f)
							{
								clampedTextSize = 0.20f;
							}

							//components::text(entity.name, screenCoords.x / utils::screenWidth, (screenCoords.y / utils::screenHeight) - (clamped / 2.0f) - (clampedTextSize * 0.09f), clampedTextSize * 0.0309f, 0.0f, 0.0f, 0.0f, 1.0f, gui::textType::center);
							components::text(entity.name, screenCoords.x / utils::screenWidth, (screenCoords.y / utils::screenHeight) - (clamped / 2.0f) - (clampedTextSize * 0.09f), clampedTextSize * 0.03f, (float)gui::nameColor.r / 255.0f, (float)gui::nameColor.g / 255.0f, (float)gui::nameColor.b / 255.0f, (float)gui::nameColor.a / 255.0f, gui::textType::center);
						}
						break;

						case visuals::espType::box:
						{
							components::rect(screenCoords.x / utils::screenWidth, screenCoords.y / utils::screenHeight, clamped * 0.35f, clamped, 0.0f, 0.0f, 0.0f, 1.0f, 3.0f);
							components::rect(screenCoords.x / utils::screenWidth, screenCoords.y / utils::screenHeight, clamped * 0.35f, clamped, (float)gui::boxColor.r / 255.0f, (float)gui::boxColor.g / 255.0f, (float)gui::boxColor.b / 255.0f, (float)gui::boxColor.a / 255.0f, 1.0f);

						}
						break;

						case visuals::espType::boxF:
						{
							components::rect(screenCoords.x / utils::screenWidth, screenCoords.y / utils::screenHeight, clamped * 0.35f, clamped, (float)gui::boxFColor.r / 255.0f, (float)gui::boxFColor.g / 255.0f, (float)gui::boxFColor.b / 255.0f, (float)gui::boxFColor.a / 255.0f);
						}
						break;

						case visuals::espType::health:
						{
							float maxHealth = 100.0f;
							float health = (float)entity.health;
							float factor = health / maxHealth;

							components::rect((screenCoords.x / utils::screenWidth) - ((clamped * 0.35f) / 2) - (0.0020f * 2), screenCoords.y / utils::screenHeight, 0.0012f, clamped + 0.0015f, 0.0f, 0.0f, 0.0f, 1.0f);
							
							if (health > 0.0f)
							{
								if (!gui::gradient)
								{
									components::rect((screenCoords.x / utils::screenWidth) - ((clamped * 0.35f) / 2) - (0.0020f * 2), (screenCoords.y / utils::screenHeight) - ((clamped / 2) * factor) + (clamped / 2), 0.0010f, clamped * factor, (float)gui::healthColor.r / 255.0f, (float)gui::healthColor.g / 255.0f, (float)gui::healthColor.b / 255.0f, (float)gui::healthColor.a / 255.0f);
								}
								else
								{
									colorGradient(health);
									components::rect((screenCoords.x / utils::screenWidth) - ((clamped * 0.35f) / 2) - (0.0020f * 2), (screenCoords.y / utils::screenHeight) - ((clamped / 2) * factor) + (clamped / 2), 0.0010f, clamped * factor, (float)gui::gradientHealth.r / 255.0f, (float)gui::gradientHealth.g / 255.0f, (float)gui::gradientHealth.b / 255.0f, (float)gui::gradientHealth.a / 255.0f);
								}
							}
						}
						break;

						case visuals::espType::flags:
						{

						}
						break;

						case visuals::espType::lines:
						{
							components::line(0.5f, 0.5f, (screenCoords.x / utils::screenWidth), (screenCoords.y / utils::screenHeight), 3.0f, 0.0f, 0.0f, 0.0f, 1.0f);
							components::line(0.5f, 0.5f, (screenCoords.x / utils::screenWidth), (screenCoords.y / utils::screenHeight), 1.0f, (float)gui::linesColor.r / 255.0f, (float)gui::linesColor.g / 255.0f, (float)gui::linesColor.b / 255.0f, (float)gui::linesColor.a / 255.0f);
						}
						break;
					}
				}
			}
		}
	}
}