#include "FileSystem.h"

#ifdef _WIN32
#include <Windows.h>
#endif

void ChangeWorkingDirectory()
{
#ifdef _WIN32
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string exeFullname(buffer);
	string exeDirectory = exeFullname.substr(0, exeFullname.find_last_of("\\"));
	SetCurrentDirectory(exeDirectory.c_str());
#endif
}