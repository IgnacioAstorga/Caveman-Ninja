#ifndef __DINOSAUREYE_H__
#define __DINOSAUREYE_H__

#include "Entity.h"

class DinosaurEye : public Entity
{
public:
	DinosaurEye(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~DinosaurEye() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();
};
#endif	// __DINOSAUREYE_H__