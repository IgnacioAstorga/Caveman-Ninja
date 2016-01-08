#ifndef __GUISCORETEXTCOMPONENT_H__
#define __GUISCORETEXTCOMPONENT_H__

#include "Component.h"

#include <list>

class GUITextRendererComponent;

using namespace std;

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
	list<GUITextRendererComponent*> textRenderers;
};
#endif //__GUISCORETEXTCOMPONENT_H__