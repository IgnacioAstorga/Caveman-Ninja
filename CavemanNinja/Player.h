#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

enum WeaponPickupType;
class WeaponComponent;
class CircleColliderComponent;

class Player : public Entity
{
public:
	Player(std::string name, float positionX = 0.0f, float positionY = 0.0f) : Entity(name, positionX, positionY) { OnCreate(); };	// Chapuza: C++ no soporta delegados en los constructores
	~Player() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();

public:
	void SetWeapon(WeaponPickupType newWeaponType);

private:
	CircleColliderComponent* meleeComponent;
};
#endif	// __PLAYER_H__