#ifndef __GUIPORTRAIT_H__
#define __GUIPORTRAIT_H__

#include "Entity.h"

class GUIPortrait : public Entity
{
public:
	GUIPortrait(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~GUIPortrait() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __GUIPORTRAIT_H__