#include "stdafx.h"
#include "Text.h"

Text::Text()
{
}

Text::~Text()
{
}

void Text::Init()
{
	memset(&font, 0, sizeof(font));
	strcpy_s(this->text, "basic text");
	strcpy_s(this->fontName, "±Ã¼­");
	this->fontSize = 12;
	this->fontWidth = FW_NORMAL;
	fontStyle = 0;
	characterSet = 0;

	font.lfHeight = fontSize;
	font.lfWeight = fontWidth;
	strcpy_s(font.lfFaceName, TEXT(fontName));
	hFont = CreateFontIndirect(&font);
}

void Text::Init(const char* fontName, int fontSize, const char* text)
{
	strcpy_s(this->text, text);
	strcpy_s(this->fontName, fontName);
	sprintf_s(this->fontPath, "%s.ttf", fontName);
	AddFontResourceA(fontPath);
	memset(&font, 0, sizeof(font));
	this->fontSize = fontSize;
	this->fontWidth = FW_NORMAL;
	fontStyle = 0;
	characterSet = 0;

	font.lfHeight = fontSize;
	font.lfWeight = fontWidth;
	strcpy_s(font.lfFaceName, TEXT(fontName));
	hFont = CreateFontIndirect(&font);
}

void Text::Update()
{
}

void Text::Render()
{

}
