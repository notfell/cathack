#pragma once

namespace mem
{
	void patchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void nopEx(BYTE* dst, unsigned int size, HANDLE hProcess);
	void writeStrEx(BYTE* dst, const std::string _string, HANDLE hProcess);

	bool injectDLL(DWORD _processId, const WCHAR* _dllPath);

	template <typename Type>
	void write(UINT64 _memoryAddress, HANDLE hProcess, Type value)
	{
		DWORD oldprotect;
		VirtualProtectEx(hProcess, (LPVOID)_memoryAddress, sizeof(value), PAGE_EXECUTE_READWRITE, &oldprotect);
		WriteProcessMemory(hProcess, (LPVOID)_memoryAddress, &value, sizeof(value), nullptr);
		VirtualProtectEx(hProcess, (LPVOID)_memoryAddress, sizeof(value), oldprotect, &oldprotect);
	}

    template <typename Type>
    Type read(UINT64 _memoryAddress, HANDLE hProcess)
    {
        Type value;
		DWORD oldprotect;

		VirtualProtectEx(hProcess, (LPVOID)_memoryAddress, sizeof(value), PAGE_EXECUTE_READWRITE, &oldprotect);
        ReadProcessMemory(hProcess, (LPVOID)_memoryAddress, &value, sizeof(value), NULL);
		VirtualProtectEx(hProcess, (LPVOID)_memoryAddress, sizeof(value), oldprotect, &oldprotect);

        return value;
    }
}