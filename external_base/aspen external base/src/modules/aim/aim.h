#pragma once

namespace aim
{
	enum class aimType
	{
		aim,
		silent,
		smooth,
		fov,
		window,
		line
	};

	UINT32 getClosetPlayer();
	void aimbot(aimType _type, time_t _frametime);
	void fov();
}