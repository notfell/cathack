#pragma once

namespace modules
{
	void waitProcess();
	uintptr_t waitModule(const wchar_t* _module, uintptr_t _var);
}