#pragma once
class TextDataManager : public singletonBase<TextDataManager>
{
public:
	TextDataManager() {};
	~TextDataManager() {};
	HRESULT Init();
	void release();

	//Save
	void txtSave(const char* saveFileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	//Load
	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);
};

