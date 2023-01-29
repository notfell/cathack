#pragma once

namespace utils
{
	extern int screenWidth;
	extern int screenHeight;

	void unHook();

	void hideConsole();
	void showConsole();
	bool isConsoleVisible();

	void init();
	const std::string getModulePathA();
	bool isFileExistA(const std::string& _path);

	float lerp(float _a, float _b, float _t);

	const std::wstring getRegeditKeyStringValue(const TCHAR* _groupPath, const TCHAR* _keyName);
	const std::wstring stringToWstring(const std::string& str, const std::locale& loc = std::locale{});

	const std::string roundFloat(float _float, int _decimals);

	void exit();

	std::string randomString(int ch);

	void isKeyJustPressed(DWORD _key, std::function<void()> _function);

	bool worldToScreen(vector3 pos, vector3& screen, viewMatrix matrix, int windowWidth, int windowHeight);
	float getDistance3D(vector3 m_pos, vector3 en_pos);
	float getDistance2D(vector3 m_pos, vector3 en_pos);
	vector3 calculateAngles(vector3 m_pos, vector3 en_pos);

	float radianToDegree(float radian);
	float degreeToRadian(float degree);
	vector3 radianToDegree(vector3 radians);
	vector3 degreeToRadian(vector3 degrees);
	vector3 lerp(vector3 _a, vector3 _b, float _t);
}