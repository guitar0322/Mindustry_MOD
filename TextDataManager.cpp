#include "stdafx.h"
#include "TextDataManager.h"

HRESULT TextDataManager::Init()
{
	return S_OK;
}

void TextDataManager::release()
{
}

void TextDataManager::txtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;
	DWORD write;

	char str[2048];

	strncpy_s(str, 2048, vectorArrayCombine(vStr), 2046);

	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 2048, &write, NULL);

	CloseHandle(file);
}

char* TextDataManager::vectorArrayCombine(vector<string> vArray)
{
	char str[2048];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); ++i)
	{
		strncat_s(str, 2048, vArray[i].c_str(), 2046);
		if (i + 1 < vArray.size()) strcat_s(str, ",");
	}

	return str;
}

vector<string> TextDataManager::txtLoad(const char* loadFileName)
{
	HANDLE file;
	DWORD read;

	char str[2048];

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 2048, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> TextDataManager::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* temp;
	const char* separator = ",";
	char* token;

	token = strtok_s(charArray, separator, &temp);
	vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		vArray.push_back(token);
	}

	return vArray;
}
