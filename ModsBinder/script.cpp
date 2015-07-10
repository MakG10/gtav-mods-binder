/*
  Author: MakG (http://www.gta-mods.pl)
*/

#include <string>
#include <ctime>
#include <Windows.h>
#include <map>

#include "script.h"
#include "menuv.h"
#include "keyboard.h"
#include "settings.h"

#pragma warning(disable : 4244 4305) // double <-> float conversions
#pragma warning( disable : 4996 )

ModsBinder::Settings settings;
MenuV menu;
std::vector<std::string> lastKeyCombination;
bool menuState = false;

void processMenuSelection(int index, MenuVItem* item)
{
	map<string, string> mods = settings.getMods();
	map<string, string>::iterator it = mods.find(item->getCaption());

	if (it != mods.end())
	{
		lastKeyCombination = SplitKeyCombination(settings.getMods()[item->getCaption()]);

		PressKeyCombination(lastKeyCombination);

		menuState = false;
	}
}


void main()
{
	menu = MenuV("Mods Binder by MakG", processMenuSelection);
	
	settings.load("ModsBinder.ini");
	if (settings.isAutoscanEnabled()) settings.scanForMods();

	for (auto &item : settings.getMods())
	{
		menu.addItem(item.first);
	}

	int statusCode = 0;
	DWORD inputWait = 0;
	while (true)
	{
		if (inputWait < GetTickCount() && IsKeyCombinationDown(settings.getShortcut()))
		{
			menuState = !menuState;
			inputWait = GetTickCount() + 200;
		}

		if (inputWait < GetTickCount() && IsKeyCombinationDown(settings.getCloseCurrentShortcut()))
		{
			PressKeyCombination(lastKeyCombination);
			inputWait = GetTickCount() + 200;
		}

		if (menuState)
		{
			menu.draw();
		}

		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}
