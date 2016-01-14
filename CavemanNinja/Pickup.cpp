#include "Pickup.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "CircleColliderComponent.h"
#include "ColliderTypes.h"
#include "OnFoodPickUpComponent.h"
#include "EntityLifetimeComponent.h"

#define PICKUP_LIFETIME 10.0f

Pickup::Pickup(PickupType type, string name, float positionX, float positionY)
	: Entity(name, positionX, positionY) 
{
	this->type = type;
	OnCreate();
}

void Pickup::OnCreate()
{
	// Crea la animación adecuada de la entidad
	BasicAnimation* animation = new BasicAnimation(256, 192, 8, 6, 0.0f, false);
	switch (type)
	{
		case FOOD_SMALL:
		{
			// Selecciona una comida de las 4 primeras filas
			int column = rand() % animation->columns;
			int row = rand() % 4;
			animation->frames.push_back({ column, row });
			break;
		}
		case FOOD_MEAT:
		{
			// Selecciona una comida de las 3 primeras imágenes de la 5ª fila
			int column = rand() % 3;
			animation->frames.push_back({ column, 4 });
			break;
		}
		case FOOD_BIG:
		{
			// Selecciona una comida de las 5 últimas imágenes de la 5ª fila
			int column = animation->columns - rand() % 5;
			animation->frames.push_back({ column, 4 });
			break;
		}
		default:
			return;
	}

	// Crea el vector con los tipos de colliders ("{}" no soporta un solo elemento)
	vector<int> collisionsTypes;
	collisionsTypes.push_back(PLAYER);

	// Crea los componentes de la entidad
	AddComponent(new SpriteRendererComponent("assets/images/pickups_food.png", animation, -16, -32));
	AddComponent(new CircleColliderComponent(16, collisionsTypes, 0, -16, PICKUP));
	AddComponent(new OnFoodPickUpComponent(type));
	AddComponent(new EntityLifetimeComponent(PICKUP_LIFETIME));
}

void Pickup::OnDestroy()
{
	// En principio no hace nada
}
