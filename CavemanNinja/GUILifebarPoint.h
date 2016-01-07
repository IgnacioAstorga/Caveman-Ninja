#ifndef __GUILIFEBARPOINT_H__
#define __GUILIFEBARPOINT_H__

#include "Entity.h"

class GUILifebarPoint : public Entity
{
public:
	GUILifebarPoint(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~GUILifebarPoint() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __GUILIFEBARPOINT_H__