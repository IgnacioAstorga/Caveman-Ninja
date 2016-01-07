#ifndef __GUILIFEBARCOMPONENT_H__
#define __GUILIFEBARCOMPONENT_H__

#include "Component.h"

#include <vector>

class PlayerLifeComponent;
class GUILifebarPoint;

using namespace std;

enum LifebarPointColor
{
	EMPTY,
	GREEN,
	YELLOW,
	RED
};

class GUILifebarComponent : public Component
{
public:
	GUILifebarComponent();
	virtual ~GUILifebarComponent();

protected:
	bool OnStart();
	bool OnCleanUp();
	bool OnPostUpdate();

public:
	PlayerLifeComponent* lifeComponent;
	vector<GUILifebarPoint*> lifebarPoints;
};
#endif //__ENEMYGRAVITYCOMPONENT_H__