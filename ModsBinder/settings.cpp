/*
  Author: MakG (http://www.gta-mods.pl)
*/

#include <sys/stat.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "settings.h"

using namespace std;

namespace ModsBinder
{
	void Settings::load()
	{
		load("ModsBinder.ini");
	}

	void Settings::load(string filename)
	{
		this->filename = filename;

		struct stat buffer;
		if (stat(this->filename.c_str(), &buffer) == 0)
		{
			read_ini(filename, this->propertyTree);

			shortcut = this->propertyTree.get_optional<string>("ModsBinder.shortcut").get_value_or("F5");
			closeCurrentShortcut = this->propertyTree.get_optional<string>("ModsBinder.closeCurrentShortcut").get_value_or("CTRL+BACKSPACE");
			autoscan = this->propertyTree.get_optional<bool>("ModsBinder.autoscan").get_value_or(true);
			autoscan = true;

			try
			{
				for (auto& key : this->propertyTree.get_child("Mods"))
					mods[key.first] = key.second.get_value<std::string>();
			} catch(...) {
				// Pusta sekcja "Mods"
			}
		}
	}

	void Settings::scanForMods()
	{
		if (this->isAutoscanEnabled())
		{
			map<string, vector<string>> supportedMods;
			supportedMods["Native Trainer (Blade)"] = {"NativeTrainer.asi", "F4"};
			supportedMods["Enhanced Native Trainer"] = { "EnhancedNativeTrainer.asi", "F4" };
			supportedMods["Simple Trainer for GTA V"] = { "TrainerV.asi", "F3" };
			supportedMods["PC Trainer V"] = { "PCTrainerV.asi", "F4" };
			supportedMods["Nice Fly"] = { "Nice Fly.asi", "H" };
			supportedMods["Riot Mode"] = { "RiotMode.asi", "F7" };
			supportedMods["Police Mod"] = { "PoliceMod.asi", "F3" };
			supportedMods["Vehicle Cannon"] = { "vehicle cannon.asi", "F11" };
			supportedMods["Bodyguard Menu"] = { "BodyguardMenu.asi", "F8" };
			supportedMods["Object Spooner"] = { "ObjectSpooner.asi", "F8" };
			supportedMods["The Inner Force"] = { "innerforce.asi", "-" };
			supportedMods["The Flash Mod"] = { "flash.asi", "SPACE" };
			supportedMods["Grand Theft Zombies"] = { "GTZ.dll", "F7" };
			supportedMods["Mayhem Mod"] = { "Mayhem Mod.asi", "NUMLOCK" };

			struct stat buffer;
			for (auto &mod : supportedMods)
			{
				if (stat(mod.second.at(0).c_str(), &buffer) == 0)
				{
					string iniMod = this->propertyTree.get_optional<string>("Mods." + mod.first).get_value_or("NULL");
					if (iniMod == "NULL")
					{
						this->addMod(mod.first, mod.second.at(1));

						this->propertyTree.put("Mods." + mod.first, mod.second.at(1));
					}
				}
			}

			write_ini(this->filename, this->propertyTree);
		}
	}

	void Settings::addMod(string name, string key)
	{
		this->mods[name] = key;
	}

	string Settings::getShortcut()
	{
		return this->shortcut;
	}

	string Settings::getCloseCurrentShortcut()
	{
		return this->closeCurrentShortcut;
	}

	bool Settings::isAutoscanEnabled()
	{
		return autoscan;
	}

	map<string, string> Settings::getMods()
	{
		return this->mods;
	}
}
