#ifndef MODSBINDER_SETTINGS_H_
#define MODSBINDER_SETTINGS_H_

#include <stdlib.h>
#include <map>
#include <boost/property_tree/ptree.hpp>

using namespace std;

namespace ModsBinder
{
	class Settings
	{
		string filename;
		boost::property_tree::ptree propertyTree;

		string shortcut;
		string closeCurrentShortcut;
		bool autoscan;
		map<string, string> mods;

	public:

		void load();
		void load(string filename);

		void scanForMods();

		void addMod(string name, string key);

		string getShortcut();

		string getCloseCurrentShortcut();

		bool isAutoscanEnabled();

		map<string, string> getMods();
	};
}

#endif