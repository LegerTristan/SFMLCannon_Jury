#include "IOManager.h"
#include <windows.h>

void IOManager::Init()
{
	isEnvironmentValid = IsDirectoryValid(GetSaveDirectory());
	if(!isEnvironmentValid)
		isEnvironmentValid = CreateSaveDirectory();
}

std::string IOManager::GetExeDirectory() const
{
	char _exePathBuffer[MAX_PATH];
	GetModuleFileNameA(NULL, _exePathBuffer, MAX_PATH);
	const std::string _exePath(_exePathBuffer);
	return _exePath.substr(0, _exePath.find_last_of("\\/"));
}

bool IOManager::IsDirectoryValid(const std::string _directoryPath)
{
	DWORD _filesAttributes = GetFileAttributesA(_directoryPath.c_str());
	if (_filesAttributes == INVALID_FILE_ATTRIBUTES) {
		return false;
	}

	return (_filesAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

bool IOManager::CreateSaveDirectory()
{
	bool _result = CreateDirectoryA(GetSaveDirectory().c_str(), NULL);
	if(!_result)
		std::cerr << "Erreur lors de la creation du dossier de sauvegarde. Code d'erreur : " << GetLastError() << std::endl;
	return _result;
}
