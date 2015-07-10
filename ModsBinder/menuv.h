#ifndef MENUV_H_
#define MENUV_H_

#include <vector>
#include <string>
#include <ctime>
#include <Windows.h>

using namespace std;

class MenuVItem
{
	string caption;

	int bgColor[4];
	int bgHighlightColor[4];

	int textColor[4];
	int textHighlightColor[4];

public:

	MenuVItem(string caption);

	MenuVItem(string caption, int bgColor[4], int textColor[4]);

	void setCaption(string caption);

	string getCaption();

	int* getBgColor();

	int* getBgHighlightColor();

	int* getTextColor();

	int* getTextHighlightColor();
};

class MenuV
{
	vector<MenuVItem> items;
	int activeItem = 0;

	string headerText;
	void(*callback) (int, MenuVItem*);

	DWORD tickCountInterval = 0;

	bool menuState = true;

	float screenWidth = 0;
	float screenHeight = 0;

	float menuMarginLeft = scaleX(15.0);
	float menuMarginTop = scaleY(15.0);

	float textMarginLeft = scaleX(4.0);

	float headerWidth = scaleX(400.0);
	float headerHeight = scaleY(45.0);

	float buttonWidth = scaleX(400.0);
	float buttonHeight = scaleY(35.0);

	float buttonSpace = scaleY(0.0);

	float headerFontScale = 0.6f;
	float buttonFontScale = 0.4f;

	int headerFont = 1;
	int buttonFont = 0;

	int headerBgColor[4];
	int headerTextColor[4];

public:

	MenuV();

	MenuV::MenuV(string header, void(*callback)(int, MenuVItem*));

	void addItem(MenuVItem item);

	void addItem(string caption);

	void addItem(string caption, int bgColor[4], int textColor[4]);

	void draw();

	void close();

private:

	void drawBackground(float posX, float posY, float width, float height, int color[4]);

	void drawText(string text, float size, int color[4], float posX, float posY, int font = 0);

	void handleControls();

	void resetSettings();

	void playSound();

	float scaleX(float value);

	float scaleY(float value);

	void updateScreenResolution();
};

#endif
