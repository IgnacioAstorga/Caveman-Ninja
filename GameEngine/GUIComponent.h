#ifndef __GUICOMPONENT_H__
#define __GUICOMPONENT_H__

#include "Component.h"
#include "Application.h"
#include "ModuleGUI.h"
#include "Entity.h"
#include "Transform.h"

enum GUILocation {
	ABSOLUTE,
	CENTER,
	TOP,
	BOTTOM,
	RIGHT,
	LEFT,
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT
};

using namespace std;

class GUIComponent : public Component
{
public:
	GUIComponent(GUILocation location, bool start_enabled = true) : Component(start_enabled)
	{
		this->location = location;
	}

	virtual ~GUIComponent()
	{
		// En principio no hace nada
	}

	bool OnStart()
	{
		App->gui->RegisterGUIComponent(this);
		return GUIStart();
	}

	bool OnCleanUp()
	{
		App->gui->UnregisterGUIComponent(this);
		return GUICleanUp();
	}

public:
	// Los métodos convencionales no hacen nada en componentes de GUI
	// Estos son los métodos que serán llamados por el ModuleGUI
	// Las clases hijas redefinirán estos métodos para implementar su funcionalidad
	virtual bool GUIStart() { return true; };
	virtual bool GUIPreUpdate() { return true; };
	virtual bool GUIUpdate() { return true; };
	virtual bool GUIPostUpdate() { return true; };
	virtual bool GUICleanUp() { return true; };

protected:
	GUILocation location;
};
#endif // __GUICOMPONENT_H__