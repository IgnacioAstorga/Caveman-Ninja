#ifndef __GUICOMPONENT_H__
#define __GUICOMPONENT_H__

#include "Component.h"

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

class GUIComponent : public Component
{
public:
	GUIComponent(GUILocation location, bool start_enabled = true);
	virtual ~GUIComponent();

	bool OnStart();
	bool OnCleanUp();

public:
	// Los métodos convencionales no hacen nada en componentes de GUI
	// Estos son los métodos que serán llamados por el ModuleGUI
	// Las clases hijas redefinirán estos métodos para implementar su funcionalidad
	virtual bool GUIStart();
	virtual bool GUIPreUpdate();
	virtual bool GUIUpdate();
	virtual bool GUIPostUpdate();
	virtual bool GUICleanUp();

protected:
	GUILocation location;
};
#endif // __GUICOMPONENT_H__