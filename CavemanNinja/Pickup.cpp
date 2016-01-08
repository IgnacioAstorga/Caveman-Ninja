#include "Pickup.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "CircleColliderComponent.h"
#include "ColliderTypes.h"
#include "OnFoodPickUpComponent.h"
#include "EffectLifespanComponent.h"

Pickup::Pickup(PickupType type, string name, float positionX, float positionY)
	: Entity(name, positionX, positionY) 
{
	this->type = type;
	OnCreate();
}

void Pickup::OnCreate()
{
	// Crea la animaci�n adecuada de la entidad
	BasicAnimation* animation = new BasicAnimation(256, 192, 8, 6, 0.0f, false);

	switch (type)
	{
		case FOOD_SMALL:
		{
			// Selecciona una imagen de las 4 primeras filas
			int column = rand() % animation->columns;
			int row = rand() % 4;
			animation->frames.push_back({ column, row });
			break;
		}
		case FOOD_MEAT:
		{
			// Selecciona una de las 3 primeras im�genes de la 5� fila
			int column = rand() % 3;
			animation->frames.push_back({ column, 4 });
			break;
		}
		case FOOD_BIG:
		{
			// Selecciona una de las 5 �ltimas im�genes de la 5� fila
			int column = animation->columns - rand() % 5;
			animation->frames.push_back({ column, 4 });
			break;
		}
		default:
			return;
	}

	// Crea los componentes de la entidad
	AddComponent(new SpriteRendererComponent("assets/images/pickups_food.png", animation, -16, -32));
	AddComponent(new CircleColliderComponent(16, 0, -16, PICKUP));
	AddComponent(new OnFoodPickUpComponent(type));
	AddComponent(new EffectLifespanComponent(10.0f));	// Reaprovecha este componente, la funcionalidad es la adecuada
}

void Pickup::OnDestroy()
{
	// En principio no hace nada
}