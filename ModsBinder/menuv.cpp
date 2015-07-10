/*
  Author: MakG (http://www.gta-mods.pl)
*/

#include <vector>
#include <string>
#include <algorithm>

#include "menuv.h"
#include "keyboard.h"

#include "natives.h"
#include "types.h"
#include "enums.h"

using namespace std;
#pragma warning( disable : 4996 )

MenuV::MenuV()
{
	this->resetSettings();
	this->updateScreenResolution();
}

MenuV::MenuV(string headerText, void(*callback)(int, MenuVItem*))
{
	this->resetSettings();

	this->headerText = headerText;
	this->callback = callback;
}

void MenuV::addItem(MenuVItem item)
{
	items.push_back(item);
}

void MenuV::addItem(string caption)
{
	MenuVItem newItem = MenuVItem(caption);

	items.push_back(caption);
}

void MenuV::addItem(string caption, int bgColor[4], int textColor[4])
{
	MenuVItem newItem = MenuVItem(caption, bgColor, textColor);

	items.push_back(newItem);
}

void MenuV::close()
{
	this->menuState = false;
}

void MenuV::draw()
{
	menuState = true;

	this->updateScreenResolution();
	this->handleControls();

	// Header
	this->drawText(headerText, headerFontScale, headerTextColor, menuMarginLeft + textMarginLeft, menuMarginTop + headerHeight * 0.2f, headerFont);
	this->drawBackground(menuMarginLeft, menuMarginTop, headerWidth, headerHeight, headerBgColor);

	for (int i = 0; i < items.size(); i++)
	{
		MenuVItem item = items.at(i);

		int* bgColor = this->activeItem == i ? item.getBgHighlightColor() : item.getBgColor();
		int* textColor = this->activeItem == i ? item.getTextHighlightColor() : item.getTextColor();

		float posX = menuMarginLeft;
		float posY = menuMarginTop + (buttonHeight + buttonSpace) * i;
		if (!headerText.empty()) posY += headerHeight;

		this->drawText(item.getCaption(), buttonFontScale, textColor, menuMarginLeft + textMarginLeft, posY + buttonHeight * 0.2f, buttonFont);
		this->drawBackground(posX, posY, buttonWidth, buttonHeight, bgColor);
	}
}

void MenuV::drawBackground(float posX, float posY, float width, float height, int color[4])
{
	GRAPHICS::DRAW_RECT(posX + width * 0.5f, posY + height * 0.5f, width, height, color[0], color[1], color[2], color[3]);
}

void MenuV::drawText(string text, float size, int color[4], float posX, float posY, int font)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, size);
	UI::SET_TEXT_COLOUR(color[0], color[1], color[2], color[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)text.c_str());
	UI::_DRAW_TEXT(posX, posY);
}

void MenuV::handleControls()
{
	if (this->tickCountInterval < GetTickCount())
	{
		if (IsKeyDown(VK_NUMPAD2))
		{
			this->playSound();

			this->activeItem++;

			if (this->activeItem >= this->items.size())
			{
				this->activeItem = 0;
			}

			this->tickCountInterval = GetTickCount() + 200;
		}

		if (IsKeyDown(VK_NUMPAD8))
		{
			this->playSound();

			this->activeItem--;

			if (this->activeItem < 0)
			{
				this->activeItem = (int)this->items.size() - 1;
			}

			this->tickCountInterval = GetTickCount() + 200;
		}

		if (IsKeyDown(VK_NUMPAD5))
		{
			this->playSound();

			this->callback(this->activeItem, &this->items.at(this->activeItem));
		}

		if (IsKeyDown(VK_BACK))
		{
			this->playSound();
			this->close();
		}
	}
}

void MenuV::resetSettings()
{
	int defaultBgColor[4] = { 10, 10, 10, 255 };
	int defaultTextColor[4] = { 245, 245, 245, 255 };

	copy(defaultBgColor, defaultBgColor + 4, this->headerBgColor);
	copy(defaultTextColor, defaultTextColor + 4, this->headerTextColor);
}

void MenuV::playSound()
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}

float MenuV::scaleX(float value)
{
	if(screenWidth <= 0) this->updateScreenResolution();

	return value / screenWidth;
}

float MenuV::scaleY(float value)
{
	if (screenHeight <= 0) this->updateScreenResolution();

	return value / screenHeight;
}

void MenuV::updateScreenResolution()
{
	//int width, height;
	//GRAPHICS::_GET_SCREEN_ACTIVE_RESOLUTION(&width, &height);

	this->screenWidth = (float)1280;
	this->screenHeight = (float)720;
}


MenuVItem::MenuVItem(string caption)
{
	this->caption = caption;

	int defaultBgColor[4] = { 56, 95, 94, 210 };
	int defaultBgHighlightColor[4] = { 218, 242, 216, 255 };
	int defaultTextColor[4] = { 243, 255, 255, 255 };
	int defaultTextHighlightColor[4] = { 10, 10, 10, 255 };

	copy(defaultBgColor, defaultBgColor + 4, this->bgColor);
	copy(defaultBgHighlightColor, defaultBgHighlightColor + 4, this->bgHighlightColor);
	copy(defaultTextColor, defaultTextColor + 4, this->textColor);
	copy(defaultTextHighlightColor, defaultTextHighlightColor + 4, this->textHighlightColor);
}

MenuVItem::MenuVItem(string caption, int bgColor[4], int textColor[4])
{
	this->caption = caption;
	copy(bgColor, bgColor + 4, this->bgColor);
	copy(textColor, textColor + 4, this->textColor);
}

void MenuVItem::setCaption(string caption)
{
	this->caption = caption;
}

string MenuVItem::getCaption()
{
	return this->caption;
}

int* MenuVItem::getBgColor()
{
	return this->bgColor;
}

int* MenuVItem::getBgHighlightColor()
{
	return this->bgHighlightColor;
}

int* MenuVItem::getTextColor()
{
	return this->textColor;
}

int* MenuVItem::getTextHighlightColor()
{
	return this->textHighlightColor;
}
