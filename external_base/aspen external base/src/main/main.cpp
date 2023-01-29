#include "../all.h"

DWORD bah::procId = NULL;
HANDLE bah::hProcess = NULL;
uintptr_t bah::mainModule = NULL;
HWND bah::gameWindow = NULL;

int main()
{
	utils::init();

	cli::logo();

	system("color 0A");

	modules::waitProcess();
	bah::mainModule = modules::waitModule(utils::stringToWstring(app).c_str(), bah::mainModule);

	bah::hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, bah::procId);

	bah::gameWindow = FindWindow(NULL, L"AssaultCube");

	DirectOverlaySetOption(D2DOV_REQUIRE_FOREGROUND | D2DOV_FONT_PIXEL);
	DirectOverlaySetup(gui::draw, bah::gameWindow);

	printf("\n                          [+] cathack has been initialized !\n");

	Sleep(1500);

	//utils::hideConsole();

	/*
	#ifdef DEV_BUILD
		utils::showConsole();
	#endif
	*/

	DWORD dwExit = 0;

	while (GetExitCodeProcess(bah::hProcess, &dwExit) && dwExit == STILL_ACTIVE)
	{

	}

	#ifdef DEV_BUILD
		if (utils::isConsoleVisible)
		{
			utils::showConsole();
			printf("\n[+] process crashed or killed !");
			Sleep(3000);
		}
	#endif 

	return EXIT_SUCCESS;
}

