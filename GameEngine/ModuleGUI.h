#ifndef __MODULEGUI_H__
#define __MODULEGUI_H__

#include "Module.h"

#include <list>

class GUIComponent;

using namespace std;

class ModuleGUI : public Module
{
public:
	ModuleGUI(bool start_enabled = true);
	~ModuleGUI();

public:
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

public:
	void RegisterGUIComponent(GUIComponent* guiComponent);
	void UnregisterGUIComponent(GUIComponent* guiComponent);

private:
	list<GUIComponent*> guiComponents;
};
#endif // __MODULEGUI_H__