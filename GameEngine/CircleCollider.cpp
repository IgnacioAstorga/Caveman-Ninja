#include "CircleCollider.h"
#include "Transform.h"
#include "CollisionListener.h"
#include "CircleTraceCollider.h"
#include "RectangleCollider.h"
#include "RectangleBasicCollider.h"
#include "LineCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

CircleCollider::CircleCollider(CollisionListener* listener, Transform* transform, float radius, float offsetX, float offsetY, int type, bool start_enabled)
	: Collider(listener, transform, type, start_enabled)
{
	this->radius = radius;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

CircleCollider::CircleCollider(CollisionListener * listener, Transform * transform, float radius, vector<int> collisionsTypes, float offsetX, float offsetY, int type, bool start_enabled)
	: Collider(listener, transform, collisionsTypes, type, start_enabled)
{
	this->radius = radius;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

CircleCollider::~CircleCollider()
{
	// No hace nada
}

bool CircleCollider::CallMe(const Collider* self) const
{
	return self->CheckCollision(this);
}

bool CircleCollider::CheckCollision(const CircleCollider* other) const
{
	// Comprueba si la distancia entre ambos centros es menor que la suma de sus radios
	return this->GetCenter().DistanceTo(other->GetCenter()) < (this->GetRadius() + other->GetRadius());
}

bool CircleCollider::CheckCollision(const CircleTraceCollider* other) const
{
	// Delega la responsabilidad en el otro collider
	return other->CheckCollision(this);
}

bool CircleCollider::CheckCollision(const RectangleCollider* other) const
{
	// Delega la responsabilidad en el otro collider
	return other->CheckCollision(this);
}

bool CircleCollider::CheckCollision(const RectangleBasicCollider * other) const
{
	// Delega la responsabilidad en el otro collider
	return other->CheckCollision(this);
}

bool CircleCollider::CheckCollision(const LineCollider* other) const
{
	// Delega la responsabilidad en el otro collider
	return other->CheckCollision(this);
}

void CircleCollider::DrawCollider() const
{
	// Determina la posición del dibujo en pantalla
	fPoint renderPosition = transform->GetGlobalPosition();
	fPoint offset = fPoint(offsetX, offsetY);
	offset.x *= transform->GetGlobalScale().x;
	offset.y *= transform->GetGlobalScale().y;
	renderPosition += offset.Rotate(transform->GetGlobalRotation());

	// Determina la escala del dibujo
	float radius = GetRadius();
	if (radius <= 0)
		radius = 1;	// Le da un radio mínimo para que se vea dibujado
	float renderScale = radius / 32;

	// Determina el color y opacidad del dibujo
	SDL_Color renderColor;
	renderColor.r = 0;
	renderColor.g = 179;
	renderColor.b = 0;
	renderColor.a = 128;

	App->renderer->Blit(App->collisions->circle, (int)(renderPosition.x - radius), (int)(renderPosition.y - radius), 0, NULL, &renderColor, NULL, fPoint(renderScale, renderScale));
}

fPoint CircleCollider::GetCenter() const
{
	fPoint offset = fPoint(offsetX, offsetY);
	offset.x *= transform->GetGlobalScale().x;
	offset.y *= transform->GetGlobalScale().y;
	return transform->GetGlobalPosition() + offset.Rotate(transform->GetGlobalRotation());
}

fPoint CircleCollider::GetExternalPositionFromCoordinates(fPoint coordinates) const
{
	// Calcula la intersección entre el centro del círculo y las coordenadas
	fPoint center = GetCenter();
	fPoint distance = coordinates - center;
	return center + distance.Normalize() * GetRadius();
}

float CircleCollider::GetRadius() const
{
	// Por simpleza solo se toma la media de su escala horizontal y vertical
	// Este collider no esta diseñado para elementos cuya relación de escala varíe
	return radius * transform->GetGlobalScale().x;
}