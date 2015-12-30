#ifndef __PLAYERCAMERA_H__
#define __PLAYERCAMERA_H__

#include "Entity.h"

class PlayerCamera : public Entity
{
public:
	PlayerCamera(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~PlayerCamera() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();

private:
	Entity* wall;
};
#endif	// __PLAYERCAMERA_H__