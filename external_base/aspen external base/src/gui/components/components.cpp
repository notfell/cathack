#include "../../all.h"

namespace components
{
	bool isLeftPressed = false;
	bool isRightPressed = false;
	bool isSelectedPressed = false;

	gui::submenu submenus[1024];
	int options[1024];

	int submenuLevel = 0;

	void changeSubmenu(gui::submenu _submenu)
	{
		submenus[submenuLevel] = gui::currentSubmenu;
		options[submenuLevel] = gui::currentOption;

		submenuLevel++;

		gui::currentSubmenu = _submenu;
		gui::currentOption = 1;
	}

	void backSubmenu()
	{
		if (submenuLevel > 0)
		{
			submenuLevel--;

			gui::currentSubmenu = submenus[submenuLevel];
			gui::currentOption = options[submenuLevel];
		}
	}

	void rect(float _x, float _y, float _width, float _height, float _r, float _g, float _b, float _a, float _thickness)
	{
		DrawBox((_x * utils::screenWidth) - ((_width * utils::screenWidth) / 2), (_y * utils::screenHeight) - ((_height * utils::screenHeight) / 2), _width * utils::screenWidth, _height * utils::screenHeight, _thickness, _r, _g, _b, _a, _thickness > 0.0f ? false : true);
	}

	void circle(float _x, float _y, float _radius, float _thickness, float _r, float _g, float _b, float _a, bool _filled)
	{
		DrawCircle((_x * utils::screenWidth) - ((_radius * utils::screenWidth) / 2), (_y * utils::screenHeight) - ((_radius * utils::screenHeight) / 2), _radius * utils::screenHeight, _thickness, _r, _g, _b, _a, _filled);
	}

	void line(float _x1, float _y1, float _x2, float _y2, float _thickness, float _r, float _g, float _b, float _a)
	{
		DrawLine
		(
			(_x1 * utils::screenWidth),
			(_y1 * utils::screenHeight),

			(_x2 * utils::screenWidth),
			(_y2 * utils::screenHeight),

			_thickness,

			_r,
			_g,
			_b,
			_a
		);
	}

	void text(std::string text, float _x, float _y, float _fontSize, float _r, float _g, float _b, float _a, gui::textType _type)
	{
		switch (_type)
		{
		case gui::textType::right:
			{
				DrawString(text, _fontSize * utils::screenWidth, (_x * utils::screenWidth) - (text.length() * _fontSize * utils::screenHeight), _y * utils::screenHeight, _r, _g, _b, _a);
			}
			break;

		case gui::textType::left:
			{
				DrawString(text, _fontSize * utils::screenWidth, _x * utils::screenWidth, _y * utils::screenHeight, _r, _g, _b, _a);
			}
			break;

		case gui::textType::center:
			{
				DrawString(text, _fontSize * utils::screenWidth, (_x * utils::screenWidth) - ((text.length() * _fontSize * utils::screenHeight) / 2), _y * utils::screenHeight, _r, _g, _b, _a);
			}
			break;
		}
	}

	void breakOption(const std::string& _text)
	{
		option("");

		bool selected = (gui::currentOption == gui::optionsCount);

		if (selected)
		{
			if (gui::previousCurrentOption < gui::currentOption)
			{
				gui::currentOption++;
			}

			if (gui::previousCurrentOption > gui::currentOption)
			{
				gui::currentOption--;
			}
		}

		text("[" + _text + "]", gui::menuPosition.x + gui::basicTextSize - 0.0025f, gui::menuPosition.y + (gui::menuSize.h / 2) + (gui::menuSize.h * gui::optionsCount) - gui::basicTextSize, gui::basicTextSize, 0.85f, 0.85f, 0.85f, gui::alpha, gui::textType::left);
	}

	void submenu(const std::string& _text, gui::submenu _submenu, std::function<void()> _function)
	{
		option(_text);

		bool selected = (gui::currentOption == gui::optionsCount);

		if (selected && isSelectedPressed)
		{
			changeSubmenu(_submenu);
		}

		text(">", gui::menuPosition.x + gui::menuSize.w - 0.005f, gui::menuPosition.y + (gui::menuSize.h / 2) + (gui::menuSize.h * gui::optionsCount) - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, gui::alpha, gui::textType::right);
	}

	void option(const std::string& _text, std::function<void()> _function)
	{
		gui::optionsCount++;

		if (gui::optionsCount == gui::currentOption)
		{
			rect(gui::menuPosition.x + (gui::menuSize.w / 2), gui::scrollerPosition, gui::menuSize.w, gui::menuSize.h, (float)gui::accentColor.r / 255.0f, (float)gui::accentColor.g / 255.0f, (float)gui::accentColor.b / 255.0f, gui::alpha);
		}

		text(_text, gui::menuPosition.x + 0.005f, gui::menuPosition.y + (gui::menuSize.h / 2) + (gui::menuSize.h * gui::optionsCount) - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, gui::alpha, gui::textType::left);

		if (gui::optionsCount == gui::currentOption && isSelectedPressed)
		{
			if (_function != nullptr)
				_function();
		}
	}

	void boolean(const std::string& _text, bool& _funct, std::function<void()> _function)
	{
		option(_text);

		bool selected = (gui::currentOption == gui::optionsCount);

		if (selected && isSelectedPressed)
		{
			_funct = !_funct;

			if (_function != nullptr)
				_function();
		}

		if (_funct)
		{
			circle(gui::menuPosition.x + gui::menuSize.w - 0.005f, gui::menuPosition.y + (gui::menuSize.h / 2) + (gui::menuSize.h * gui::optionsCount) + (0.0035f / 2), 0.0035f, 0.0f, (float)gui::on.r / 255.0f, (float)gui::on.g / 255.0f, (float)gui::on.b / 255.0f, gui::alpha);
		}
		else
		{
			circle(gui::menuPosition.x + gui::menuSize.w - 0.005f, gui::menuPosition.y + (gui::menuSize.h / 2) + (gui::menuSize.h * gui::optionsCount) + (0.0035f / 2), 0.0035f, 0.0f, (float)gui::off.r / 255.0f, (float)gui::off.g / 255.0f, (float)gui::off.b / 255.0f, gui::alpha);
		}
	}

	void intSlider(const std::string& _text, int& _startValue, int _minValue, int _maxValue, int _step, std::function<void()> _function)
	{
		option(_text);

		bool selected = (gui::currentOption == gui::optionsCount);

		if (selected)
		{
			if (isLeftPressed)
			{
				_startValue -= _step;

				if (_startValue <= _minValue)
				{
					_startValue = _minValue;
				}
			}

			if (isRightPressed)
			{
				_startValue += _step;

				if (_startValue >= _maxValue)
				{
					_startValue = _maxValue;
				}
			}
		}
		text("<" + std::to_string(_startValue) + ">", gui::menuPosition.x + gui::menuSize.w - 0.005f, gui::menuPosition.y + (gui::menuSize.h / 2) + (gui::menuSize.h * gui::optionsCount) - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, gui::alpha, gui::textType::right);
	}

	void floatSlider(const std::string& _text, float& _startValue, float _minValue, float _maxValue, float _step, int _decimals, std::function<void()> _function)
	{
		option(_text);

		bool selected = (gui::currentOption == gui::optionsCount);

		if (selected)
		{
			if (isLeftPressed)
			{
				_startValue -= _step;

				if (_startValue <= _minValue)
				{
					_startValue = _minValue;
				}
			}

			if (isRightPressed)
			{
				_startValue += _step;

				if (_startValue >= _maxValue)
				{
					_startValue = _maxValue;
				}
			}
		}
		text("<" + utils::roundFloat(_startValue, _decimals) + ">", gui::menuPosition.x + gui::menuSize.w - 0.005f, gui::menuPosition.y + (gui::menuSize.h / 2) + (gui::menuSize.h * gui::optionsCount) - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, gui::alpha, gui::textType::right);
		_startValue;
	}

	void array(const std::string& _text, std::vector<std::string> vector, int& _start, std::function<void()> function)
	{
		option(_text);

		bool selected = (gui::currentOption == gui::optionsCount);

		if (selected)
		{
			if (isLeftPressed)
			{
				_start--;

				if (_start <= 0)
				{
					_start = 0;
				}
			}

			if (isRightPressed)
			{
				_start++;

				if (_start >= static_cast<int>(vector.size()) - 1)
				{
					_start = static_cast<int>(vector.size()) - 1;
				}
			}
		}
		
		text("<" + vector[_start] + ">", gui::menuPosition.x + gui::menuSize.w - 0.005f, gui::menuPosition.y + (gui::menuSize.h / 2) + (gui::menuSize.h * gui::optionsCount) - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, gui::alpha, gui::textType::right);
	}

	void notifications(gui::notifType _type,std::string _text) // todo calctextsize
	{
		float sizeX = 0.35f;
		float sizeY = 0.025f;

		uint8_t currentNotif;
		uint8_t maxNotif = 5;

		switch (_type)
		{
		case gui::notifType::info:
			{

			rect(0.0f + (sizeX / 2) + 0.005f, 0.0f + (sizeY / 2) + 0.005f, sizeX, sizeY, 0.04f, 0.04f, 0.04f, 1.0f);

			rect(0.0f + (sizeX / 2) + 0.005f, 0.0f + (sizeY / 2) + 0.005f, sizeX, sizeY, 0.66f, 0.69f, 0.99f, 1.0f, 0.2f);

			const std::string title = "aspen";

			// Menu title text.
			text(title, 1.0f - (sizeX), (sizeY / 2) + 0.005f - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, 1.0f, gui::textType::left);
			text(".ws[dev]", 1.0f - (sizeX)+0.001f + (title.length() * (gui::basicTextSize / 2)), (sizeY / 2) + 0.005f - gui::basicTextSize, gui::basicTextSize, 0.66f, 0.69f, 0.99f, 1.0f, gui::textType::left);

			}
			break;

		case gui::notifType::hit:

			break;

		case gui::notifType::hitReceived:

			break;

		case gui::notifType::alert:

			break;
		}
	}

	void watermark()
	{
		float sizeX = 0.105f;
		float sizeY = 0.025f;

		rect
		(
			// Position
			1.0f - (sizeX / 2) - 0.005f,
			(sizeY / 2) + 0.005f,

			// Size
			sizeX,
			sizeY,
			
			// Colors
			0.04f,
			0.04f,
			0.04f,
			1.0f
		);

		rect
		(
			// Position
			1.0f - (sizeX / 2) - 0.005f,
			(sizeY / 2) + 0.005f,

			// Size
			sizeX,
			sizeY,

			// Colors
			0.66f,
			0.69f,
			0.99f,
			1.0f,
			0.2f
		);

		const std::string title = "cathack";

		// Menu title text.
		text(title, 1.0f - (sizeX), (sizeY / 2) + 0.005f - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, 1.0f, gui::textType::left);
		text(" me0wing on </ac_cli3nt>", 1.0f - (sizeX) + 0.001f + (title.length() * (gui::basicTextSize / 2)), (sizeY / 2) + 0.005f - gui::basicTextSize, gui::basicTextSize, (float)gui::accentColor.r / 255.0f, (float)gui::accentColor.g / 255.0f, (float)gui::accentColor.b / 255.0f, (float)gui::accentColor.a / 255.0f, gui::textType::left);
	}

	void keys()
	{
		isLeftPressed = false;
		isRightPressed = false;
		isSelectedPressed = false;

		utils::isKeyJustPressed(VK_UP, []
		{
			if (gui::currentOption > 1)
			{
				gui::previousCurrentOption = gui::currentOption;
				gui::currentOption--;
			}
			else
			{
				gui::previousCurrentOption = 1;
				gui::currentOption = gui::optionsCount;
			}
		});

		utils::isKeyJustPressed(VK_DOWN, []
		{
			if (gui::currentOption < gui::optionsCount)
			{
				gui::previousCurrentOption = gui::currentOption;
				gui::currentOption++;
			}
			else
			{
				gui::previousCurrentOption = gui::optionsCount;
				gui::currentOption = 1;
			}
		});

		utils::isKeyJustPressed(VK_BACK, []
		{
			if (gui::currentSubmenu == gui::submenu::mainMenu)
			{
				gui::closeCalled = true;
			}
			else
			{
				backSubmenu();
			}
		});

		utils::isKeyJustPressed(VK_LEFT, []
		{
			isLeftPressed = true;
		});

		utils::isKeyJustPressed(VK_RIGHT, []
		{
			isRightPressed = true;
		});

		utils::isKeyJustPressed(VK_RETURN, []
		{
			isSelectedPressed = true;
		});
	}

	void handleSmoothScrolling(time_t _frametime)
	{
		static float scrollerNextPosition;

		scrollerNextPosition = gui::menuPosition.y + (gui::menuSize.h / 2) + (gui::menuSize.h * gui::currentOption);

		const float step = abs(scrollerNextPosition - gui::scrollerPosition) * _frametime * gui::smoothScrollingSpeed * 0.01f;

		if (gui::scrollerPosition > scrollerNextPosition)
		{
			gui::scrollerPosition -= step;

			if (gui::scrollerPosition < scrollerNextPosition)
				gui::scrollerPosition = scrollerNextPosition;
		}
		else
		{
			gui::scrollerPosition += step;

			if (gui::scrollerPosition > scrollerNextPosition)
				gui::scrollerPosition = scrollerNextPosition;
		}
	}

	void menuBase(int _width, int _height, time_t _frametime)
	{
		// We handle the menu inputs keys here.
		keys();

		// Our smooth scroller function.
		handleSmoothScrolling(_frametime);

		// Menu title header.
		rect(gui::menuPosition.x + (gui::menuSize.w / 2), gui::menuPosition.y + (gui::menuSize.h / 2), gui::menuSize.w, gui::menuSize.h, 0.04f, 0.04f, 0.04f, gui::alpha); // back
		rect(gui::menuPosition.x + (gui::menuSize.w / 2), gui::menuPosition.y + (gui::menuSize.h / 2), gui::menuSize.w, gui::menuSize.h, (float)gui::accentColor.r / 255.0f, (float)gui::accentColor.g / 255.0f, (float)gui::accentColor.b / 255.0f, gui::alpha, 0.2f); // border

		const std::string title = "cathack";

		// Menu title text.
		text(title, gui::menuPosition.x + 0.005f, gui::menuPosition.y + (gui::menuSize.h / 2) - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, gui::alpha, gui::textType::left);
		text("[debug]", gui::menuPosition.x + 0.005f + 0.001f + (title.length() * (gui::basicTextSize / 2)), gui::menuPosition.y + (gui::menuSize.h / 2) - gui::basicTextSize, gui::basicTextSize, (float)gui::accentColor.r / 255.0f, (float)gui::accentColor.g / 255.0f, (float)gui::accentColor.b / 255.0f, gui::alpha, gui::textType::left);

		// Menu options counter.
		text(std::to_string(gui::currentOption) + "/" + std::to_string(gui::optionsCount), gui::menuPosition.x + gui::menuSize.w - 0.005f, gui::menuPosition.y + (gui::menuSize.h / 2) - gui::basicTextSize, gui::basicTextSize, 0.60f, 0.60f, 0.60f, gui::alpha, gui::textType::right);

		// Menu background.
		rect(gui::menuPosition.x + (gui::menuSize.w / 2), gui::menuPosition.y + gui::menuSize.h + ((gui::menuSize.h * gui::optionsCount) / 2), gui::menuSize.w, gui::menuSize.h * gui::optionsCount, 0.04f, 0.04f, 0.04f, gui::alpha);
		rect(gui::menuPosition.x + (gui::menuSize.w / 2), gui::menuPosition.y + gui::menuSize.h + ((gui::menuSize.h * gui::optionsCount) / 2), gui::menuSize.w, gui::menuSize.h * gui::optionsCount, (float)gui::accentColor.r / 255.0f, (float)gui::accentColor.g / 255.0f, (float)gui::accentColor.b / 255.0f, gui::alpha, 0.2f);

		// Reset options count (this prevent the menu from increasing every frames more options that we want).
		gui::optionsCount = 0;
	}
}