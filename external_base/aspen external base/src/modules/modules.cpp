#include "../all.h"

namespace modules
{
	void waitProcess()
	{
		do
		{
			bah::procId = proc::getProcId(utils::stringToWstring(app).c_str());
			printf("\r                          [~] waiting for the game (%s) !", app);

		} while (!bah::procId);

		printf("\n                          [+] (%s) found !", app);
		printf("\n                          [+] (%s) id : %d", app, bah::procId);

		printf("\n");
		printf("\n");
	}

	uintptr_t waitModule(const wchar_t* _module, uintptr_t _var)
	{
		do
		{
			_var = proc::getModuleBaseAddress(bah::procId, _module);
			printf("\r                          [~] waiting for the %ls!", _module);

		} while (!_var);

		printf("\n                          [+] %ls found !", _module);
		printf("\n                          [+] %ls address : 0x%llx", _module, _var);

		printf("\n");

		Sleep(500);

		return _var;
	}
}