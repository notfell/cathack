#include "../all.h"

namespace mem
{
	void patchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess)
	{
		DWORD oldprotect;
		VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
		WriteProcessMemory(hProcess, dst, src, size, nullptr);
		VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
	}

	void nopEx(BYTE* dst, unsigned int size, HANDLE hProcess)
	{
		BYTE* nopArray = new BYTE[size];
		memset(nopArray, 0x90, size);

		patchEx(dst, nopArray, size, hProcess);
		delete[] nopArray;
	}

	void writeStrEx(BYTE* dst, const std::string _string, HANDLE hProcess)
	{
		DWORD oldprotect;
		VirtualProtectEx(hProcess, dst, _string.size(), PAGE_EXECUTE_READWRITE, &oldprotect);
		WriteProcessMemory(hProcess, dst, _string.data(), _string.size(), nullptr);
		VirtualProtectEx(hProcess, dst, _string.size(), oldprotect, &oldprotect);
	}

    bool injectDLL(DWORD _processId, const WCHAR* _dllPath)
    {
        static WCHAR fullPath[MAX_PATH];

        // Get full path of the dll.
        DWORD pathLength = GetFullPathName(_dllPath, MAX_PATH, fullPath, NULL);
        if (pathLength == NULL)
        {
            printf("GetFullPathName (Error: %u)\n", GetLastError());

            return false;
        }

        // Allow all access for the dll.
        HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, _processId);
        if (!process)
        {
            printf("openProcess (error: %u)\n", GetLastError());

            return false;
        }

        // Alloc memory for the dll.
        LPVOID virtualAlloc = VirtualAllocEx(process, NULL, pathLength * sizeof(WCHAR), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (!virtualAlloc)
        {
            printf("virtualAlloc (error: %u)\n", GetLastError());

            return false;
        }

        // Check if we are able to write in memory.
        BOOL ableToWrite = WriteProcessMemory(process, virtualAlloc, fullPath, pathLength * sizeof(WCHAR), NULL);
        if (!ableToWrite)
        {
            printf("writeProcessMemory (error: %u)\n", GetLastError());

            return false;
        }

        // Check if we are able to load the dll.
        HMODULE kernel32 = LoadLibrary(L"kernel32");
        if (!kernel32)
        {
            printf("loadLibrary (error: %u)\n", GetLastError());

            return false;
        }

        // Check if we can get process address.
        LPTHREAD_START_ROUTINE loadLibrary = reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(kernel32, "LoadLibraryW"));
        if (!loadLibrary)
        {
            printf("getProcAddress (error: %u)\n", GetLastError());

            return false;
        }

        // Create a remote thread to load the dll.
        DWORD threadId = 0;
        HANDLE threadHandle = CreateRemoteThread(process, NULL, NULL, loadLibrary, virtualAlloc, NULL, &threadId);
        if (!threadHandle)
        {
            printf("createRemoteThread (error: %u)\n", GetLastError());

            return false;
        }

        return true;
    }
}

