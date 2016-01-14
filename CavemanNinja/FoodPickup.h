#ifndef __FOODPICKUP_H__
#define __FOODPICKUP_H__

#include "Entity.h"

enum FoodPickupType
{
	FOOD_SMALL,
	FOOD_MEAT,
	FOOD_BIG
};

class FoodPickup : public Entity
{
public:
	FoodPickup(FoodPickupType type, string name, float positionX = 0.0f, float positionY = 0.0f);
	~FoodPickup() { OnDestroy(); };

protected:
	void OnCreate();
	void OnDestroy();

public:
	FoodPickupType type;
};
#endif	// __FOODPICKUP_H__