#include "../../all.h"

void localPlayer::setPosition(vector3 _newPosition)
{
	UINT32 localplayer = mem::read<UINT32>(bah::mainModule + PLAYER_BASE, bah::hProcess);

	if (localplayer)
	{
		mem::write(localplayer + PLAYER_POSITION, bah::hProcess, _newPosition);
	}
}

vector3 localPlayer::getPosition()
{
	UINT32 localplayer = mem::read<UINT32>(bah::mainModule + PLAYER_BASE, bah::hProcess);

	if (localplayer)
	{
		return mem::read<vector3>(localplayer + PLAYER_POSITION, bah::hProcess);
	}

	return vector3();
}

void localPlayer::setRotation(vector3 _newRotation)
{
	UINT32 localplayer = mem::read<UINT32>(bah::mainModule + PLAYER_BASE, bah::hProcess);

	if (localplayer)
	{
		mem::write(localplayer + PLAYER_ROTATION, bah::hProcess, _newRotation);
	}
}

vector3 localPlayer::getRotation()
{
	UINT32 localplayer = mem::read<UINT32>(bah::mainModule + PLAYER_BASE, bah::hProcess);

	if (localplayer)
	{
		return mem::read<vector3>(localplayer + PLAYER_ROTATION, bah::hProcess);
	}

	return vector3();
}

vector3 localPlayer::getHeadPosition()
{

	UINT32 localplayer = mem::read<UINT32>(bah::mainModule + PLAYER_BASE, bah::hProcess);

	if (localplayer)
	{
		return mem::read<vector3>(localplayer + 0x4, bah::hProcess);
	}

	return vector3();
}

viewMatrix localPlayer::getViewMatrix()
{
	return mem::read<viewMatrix>(bah::mainModule + VIEW_MATRIX, bah::hProcess);
}