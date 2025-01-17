#pragma once
#include "Math/Vector2.h"

struct MenuItem
{
	using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected)
	{
		size_t length = strlen(text);
		menuText = new char[length + 1];
		strcpy_s(menuText, length + 1, text);

		this->onSelected = onSelected;
	}

	~MenuItem()
	{
		delete[] menuText;
	}

	char* menuText;
	OnSelected onSelected;
};