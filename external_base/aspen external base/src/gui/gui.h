#pragma once

namespace gui
{
	enum class submenu
	{
		// default tab
		mainMenu,

		// aim
		aimAssistance,

		// visuals
		visuals,

		esp,
		player,
		box,
		boxF,
		name,
		health,
		flags,
		lines,
		espSettings,

		world,

		// misc
		misc,

		// settings
		settings,
		windows,
		gui,

		// dev
		dev
	};

	enum class textType
	{
		right,
		left,
		center
	};

	enum class notifType
	{
		info,
		hit,
		hitReceived,
		alert
	};

	inline float dpiScale = 1.0f;

	inline float basicTextSize = 0.00625f;

	inline size menuSize = size(0.15f, 0.030f);
	inline position menuPosition = position(0.5f, 0.01f);

	inline size twSize = size(0.10f, 0.030f);
	inline position twP = position(0.005f, 0.5f);

	inline color on = color(51, 255, 115);
	inline color off = color(255 , 51, 25);

	// aim assist
	inline color aimLinesColor = color(252, 77, 77);
	inline color aimFovColor = color(254, 225, 168);

	//player esp
	inline color boxColor = color(240, 221, 189, 230);
	inline color boxFColor = color(220, 201, 169, 100);
	inline color nameColor = color(221, 211, 255, 230);
	inline color healthColor = color(159, 251, 198);
	inline color linesColor = color(237, 251, 160);

	inline color gradientHealth = color(254, 225, 168);

	// accent color
	inline color accentColor = color(129, 191, 128); // 0.66f, 0.69f, 0.99f

	inline float smoothScrollingSpeed = 1.0f;

	inline int currentOption = 1;
	inline int previousCurrentOption = 1;
	inline int optionsCount = 0;

	inline gui::submenu currentSubmenu = gui::submenu::mainMenu;

	inline float scrollerPosition = gui::menuPosition.y + (gui::menuSize.h / 2) + (gui::menuSize.h * gui::currentOption);

	extern bool closeCalled;

	inline bool gradient = false;

	extern float alpha;

	extern float aimSmooth;
	extern float aimFov;
	extern float maxDistances;
	extern bool bAimFov;

	void draw(int _width, int _height, time_t _frameTime);
}

// 1920 1080
// 2048 1080