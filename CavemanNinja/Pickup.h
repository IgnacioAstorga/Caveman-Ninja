#ifndef __PICKUP_H__
#define __PICKUP_H__

#include "Entity.h"

enum PickupType {
	FOOD_SMALL,
	FOOD_MEAT,
	FOOD_BIG
};

class Pickup : public Entity
{
public:
	Pickup(PickupType type, string name, float positionX = 0.0f, float positionY = 0.0f);
	~Pickup() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();

public:
	PickupType type;
};
#endif	// __PLAYER_H__