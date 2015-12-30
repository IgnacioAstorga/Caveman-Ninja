#include "CircleCollider.h"
#include "Transform.h"
#include "CollisionListener.h"
#include "CircleTraceCollider.h"
#include "RectangleCollider.h"
#include "LineCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

CircleCollider::CircleCollider(CollisionListener* listener, Transform* transform, float radius, float offsetX, float offsetY, int type, bool start_enabled) : Collider(listener, transform, type, start_enabled)
{
	this->radius = radius;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

CircleCollider::~CircleCollider()
{
	// No hace nada
}

bool CircleCollider::CallMe(Collider* self)
{
	return self->CheckCollision(this);
}

bool CircleCollider::CheckCollision(CircleCollider* other)
{
	// Comprueba si la distancia entre ambos centros es menor que la suma de sus radios
	return this->GetCenter().DistanceTo(other->GetCenter()) < (this->GetRadius() + other->GetRadius());
}

bool CircleCollider::CheckCollision(CircleTraceCollider* other)
{
	// Delega la responsabilidad en el otro collider
	return other->CheckCollision(this);
}

bool CircleCollider::CheckCollision(RectangleCollider* other)
{
	// Delega la responsabilidad en el otro collider
	return other->CheckCollision(this);
}

bool CircleCollider::CheckCollision(LineCollider* other)
{
	// Delega la responsabilidad en el otro collider
	return other->CheckCollision(this);
}

void CircleCollider::DrawCollider()
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

fPoint CircleCollider::GetCenter()
{
	fPoint offset = fPoint(offsetX, offsetY);
	offset.x *= transform->GetGlobalScale().x;
	offset.y *= transform->GetGlobalScale().y;
	return transform->GetGlobalPosition() + offset.Rotate(transform->GetGlobalRotation());
}

float CircleCollider::GetRadius()
{
	// Por simpleza solo se toma la media de su escala horizontal y vertical
	// Este collider no esta diseñado para elementos cuya relación de escala varíe
	return radius * transform->GetGlobalScale().x;
}