#pragma once

namespace components
{
	extern ULONGLONG keyPressPreviousTick;
	extern int keyPressDelay;

	void rect(float _x, float _y, float _width, float _height, float _r, float _g, float _b, float _a, float _thickness = 0.0f);
	void line(float _x1, float _y1, float _x2, float _y2, float _thickness, float _r, float _g, float _b, float _a); //certifier x3 baw
	void text(std::string text, float _x, float _y, float _fontSize, float _r, float _g, float _b, float _a, gui::textType _type);
	void circle(float _x, float _y, float _radius, float _thickness, float _r, float _g, float _b, float _a, bool _filled = true);
	void menuBase(int _width, int _height, time_t _frametime);

	void watermark();
	void notifications(gui::notifType _type, std::string _text);

	void submenu(const std::string& _text, gui::submenu _submenu, std::function<void()> _function = nullptr);
	void option(const std::string& _text, std::function<void()> _function = nullptr);
	void boolean(const std::string& _text, bool& _funct, std::function<void()> _function = nullptr);
	void intSlider(const std::string& _text, int& _startValue, int _minValue, int _maxValue, int _step, std::function<void()> _function = nullptr);
	void floatSlider(const std::string& _text, float& _startValue, float _minValue, float _maxValue, float _step, int _decimals = 2, std::function<void()> _function = nullptr);
	void array(const std::string& _text, std::vector<std::string> vector, int& _start, std::function<void()> function = nullptr);
	void breakOption(const std::string& _text);
}