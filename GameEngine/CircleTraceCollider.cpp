#include "CircleTraceCollider.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"
#include "RectangleBasicCollider.h"
#include "LineCollider.h"
#include "Transform.h"

CircleTraceCollider::CircleTraceCollider(CollisionListener * listener, Transform * transform, float radius, float offsetX, float offsetY, int type, bool start_enabled)
	: CircleCollider(listener, transform, radius, offsetX, offsetY, type, start_enabled) {}

CircleTraceCollider::CircleTraceCollider(CollisionListener * listener, Transform * transform, float radius, vector<int> collisionsTypes, float offsetX, float offsetY, int type, bool start_enabled)
	: CircleCollider(listener, transform, radius, collisionsTypes, offsetX, offsetY, type, start_enabled) {}

CircleTraceCollider::~CircleTraceCollider()
{
	// No hace nada
}

bool CircleTraceCollider::CallMe(Collider * self)
{
	return self->CheckCollision(this);
}

bool CircleTraceCollider::CheckCollision(CircleCollider * other)
{
	// Comprueba si colisionan el círculo o su trazo
	if (other->CollidesWith(&GetCircleCollider()))
		return true;
	if (other->CollidesWith(&GetTraceCollider()))
		return true;
	return false;
}

bool CircleTraceCollider::CheckCollision(CircleTraceCollider * other)
{
	// Comprueba si colisionan el círculo o su trazo
	if (other->CollidesWith(&GetCircleCollider()))
		return true;
	if (other->CollidesWith(&GetTraceCollider()))
		return true;
	return false;
}

bool CircleTraceCollider::CheckCollision(RectangleCollider * other)
{
	// Comprueba si colisionan el círculo o su trazo
	if (other->CollidesWith(&GetCircleCollider()))
		return true;
	if (other->CollidesWith(&GetTraceCollider()))
		return true;
	return false;
}

bool CircleTraceCollider::CheckCollision(RectangleBasicCollider * other)
{
	// Comprueba si colisionan el círculo o su trazo
	if (other->CollidesWith(&GetCircleCollider()))
		return true;
	if (other->CollidesWith(&GetTraceCollider()))
		return true;
	return false;
}

bool CircleTraceCollider::CheckCollision(LineCollider * other)
{
	// Comprueba si colisionan el círculo o su trazo
	if (other->CollidesWith(&GetCircleCollider()))
		return true;
	if (other->CollidesWith(&GetTraceCollider()))
		return true;
	return false;
}

void CircleTraceCollider::DrawCollider()
{
	// Pinta sus colliders característicos
	SDL_Color color;
	color.r = 179;
	color.g = 0;
	color.b = 179;
	color.a = 128;
	GetCircleCollider().DrawCollider();
	GetTraceCollider().DrawCollider(color);	// La traza es morada
}

bool CircleTraceCollider::OnStartCollider()
{
	// Establece la posición inicial
	lastFramePosition = transform->GetLocalPosition();
	return true;
}

void CircleTraceCollider::OnPostUpdate()
{
	// Guarda la posición actual del Collider
	lastFramePosition = transform->GetLocalPosition();
}

CircleCollider CircleTraceCollider::GetCircleCollider()
{
	return CircleCollider(NULL, transform, radius, offsetX, offsetY, type);
}

RectangleCollider CircleTraceCollider::GetTraceCollider()
{
	// La anchura de la traza es la distancia desde la posición anterior
	fPoint thisFramePosition = transform->GetLocalPosition();
	float width = lastFramePosition.DistanceTo(thisFramePosition);
	// La altura, el diámetro del círculo
	float height = radius * 2;
	// Su offset es la distancia desde su posición actual al punto medio entre ambas posiciones
	fPoint travelVector = (lastFramePosition - thisFramePosition) * (1.0f / 2.0f);
	// Su rotación, la pendiente del vector de posición
	float rotation = (float)(atan2(travelVector.y, travelVector.x) * 180 / M_PI);;

	return RectangleCollider(NULL, transform, width, height, travelVector.x, travelVector.y, rotation, type);
}
