#pragma once

#include "Constants.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

/// <summary>
/// Handles all I/O manipulations such as create folder, save file etc.
/// </summary>
class IOManager
{
public:
#pragma region Constructor/Destructor
	IOManager() : isEnvironmentValid(false) {}
	~IOManager() = default;
#pragma endregion

#pragma region PublicMethods
	void Init();

	/// <summary>
	/// Save any data as JSON value in the save file.
	/// </summary>
	/// <typeparam name="T">Data's type</typeparam>
	/// <param name="_value">Data's value</param>
	/// <param name="_valueName">Name of the data, used for the JSON in order to save and retrieve the data correctly.</param>
	/// <returns>True if the value was saved, else false.</returns>
	template<typename T>
	inline bool Save(T _value, const std::string& _valueName)
	{
		if (!isEnvironmentValid)
			return false;

		std::ofstream _saveStream(GetSaveFile());
		if (_saveStream.is_open())
		{
			json _jsonSave;
			_jsonSave[_valueName] = _value;
			_saveStream << std::setw(4) << _jsonSave << std::endl;
			return true;
		}
		else
		{
			char _errorBuffer[50];
			if (strerror_s(_errorBuffer, sizeof(_errorBuffer), errno))
				std::cerr << "Erreur lors de l'ouverture du fichier de sauvegarde : " << _errorBuffer << std::endl;
		}

		return false;
	}

	/// <summary>
	/// Reads a data from a JSON value in the save file and retrieve it if it exists.
	/// </summary>
	/// <typeparam name="T">Data's type</typeparam>
	/// <param name="_valueName">Name of the data, used for the JSON in order to save and retrieve the data correctly.</param>
	/// <returns>The value in the save file, or the default value of the data type in template if no data is found from the JSON.</returns>
	template<typename T>
	inline T Read(const std::string& _valueName)
	{
		if (!isEnvironmentValid)
			return T();
		
		std::ifstream _saveStream(GetSaveFile());
		if (_saveStream.is_open())
		{
			json _jsonSave;
			_saveStream >> _jsonSave;
			return _jsonSave[_valueName];
		}
		else
		{
			char _errorBuffer[50];
			if (strerror_s(_errorBuffer, sizeof(_errorBuffer), errno))
				std::cerr << "Erreur lors de l'ouverture du fichier de sauvegarde : " << _errorBuffer << std::endl;
		}

		return T();
	}
#pragma endregion

private:

#pragma region PrivateMethods
	std::string GetExeDirectory() const;

	inline std::string GetSaveDirectory() const { return GetExeDirectory() + SAVE_DIRECTORY_NAME;}

	inline std::string GetSaveFile() const { return GetSaveDirectory() + SAVE_FILE_NAME + SAVE_FILE_EXT; }

	bool IsDirectoryValid(const std::string directoryPath);

	bool CreateSaveDirectory();
#pragma endregion

	/// <summary>
	/// True if the save directory exists or has been created, else false.
	/// If false, then the I/OManager can not save files in the save directory.
	/// </summary>
	bool isEnvironmentValid;
};