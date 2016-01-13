#ifndef __GUISCORETEXTCOMPONENT_H__
#define __GUISCORETEXTCOMPONENT_H__

#include "Component.h"

class GUITextRendererComponent;

class GUIScoreTextComponent : public Component
{
public:
	GUIScoreTextComponent();
	virtual ~GUIScoreTextComponent();

protected:
	bool OnStart();
	bool OnPostUpdate();

public:
	int storedScore;
	GUITextRendererComponent* textRenderer;
};
#endif //__GUISCORETEXTCOMPONENT_H__