#include "../../all.h"

std::vector<playerEntity> world::getEntities()
{
	std::vector<playerEntity> entities = {};

	UINT32 entityBase = mem::read<UINT32>(bah::mainModule + ENTITIES_LIST_BASE, bah::hProcess);

	if (entityBase)
	{
		for (int i = 1; i < world::getEntitiesAmount(); i++)
		{
			playerEntity player;

			player.base = mem::read<UINT32>(entityBase + (0x4 * i), bah::hProcess);

			ReadProcessMemory(bah::hProcess, (PBYTE*)(player.base + 0x225), &player.name, sizeof(player.name), nullptr);

			player.health = mem::read<int>(player.base + 0xF8, bah::hProcess);
			player.positionHead = mem::read<vector3>(player.base + 0x0004, bah::hProcess);
			player.positionFeet = mem::read<vector3>(player.base + 0x34, bah::hProcess);
			player.team = mem::read<int>(player.base + 0x32C, bah::hProcess);

			entities.push_back(player);
		}
	}

	return entities;
}

int world::getEntitiesAmount()
{
	return mem::read<int>(bah::mainModule + PLAYER_BASE + 0xC, bah::hProcess);
}