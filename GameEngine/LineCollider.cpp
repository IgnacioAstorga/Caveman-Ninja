#include "LineCollider.h"
#include "Transform.h"
#include "CollisionListener.h"
#include "CircleCollider.h"
#include "CircleTraceCollider.h"
#include "RectangleCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

#include <algorithm>

bool comparePointsByX(fPoint a, fPoint b) { return a.x < b.x; }

LineCollider::LineCollider(CollisionListener* listener, Transform* transform, vector<fPoint> points, float thickness, int type, bool start_enabled) : Collider(listener, transform, type, start_enabled)
{
	this->points = points;
	this->thickness = thickness;

	// Ordena los puntos de menor a mayor X
	sort(this->points.begin(), this->points.end(), comparePointsByX);
}

LineCollider::~LineCollider()
{
	// No hace nada
}

bool LineCollider::CallMe(Collider* self)
{
	return self->CheckCollision(this);
}

bool LineCollider::CheckCollision(CircleCollider* other)
{
	// Por las propiedades del c�rculo, solo comprueba en el segmento que contiene la X del centro del c�rculo
	int leftBoundIndex = -1;
	fPoint center = other->GetCenter();

	for (unsigned int i = 0; i < points.size() - 1 && leftBoundIndex == -1; ++i)	// Empieza desde el primero y acaba en el pen�ltimo
		if (center.x <= GetPointGlobalCoordinates(leftBoundIndex).x)
			leftBoundIndex = i;

	if (leftBoundIndex == -1)	// Est� m�s a la derecha que el �ltimo punto, comprueba la colision con el �ltimo segmento
		leftBoundIndex = points.size() - 2;	// size - 2 es el �ndice del pen�ltimo elemento

	// Crea el rect�ngulo del segmento adecuado y comprueba la colision
	RectangleCollider rc = CreateSegmentCollider(leftBoundIndex);
	return rc.CollidesWith(other);
}

bool LineCollider::CheckCollision(CircleTraceCollider* other)
{
	// Delega la responsabilidad en el otro collider
	return other->CheckCollision(this);
}

bool LineCollider::CheckCollision(RectangleCollider* other)
{
	// Para cada segmento, comprueba si colisiona con el rect�ngulo
	for (unsigned int i = 0; i < points.size() - 1; ++i)	// Empieza desde el primero y acaba en el pen�ltimo
		if (CreateSegmentCollider(i).CollidesWith(other))
			return true;
	return false;	// Llegados a este punto, ning�n segmento colisiona con el rect�ngulo
}

bool LineCollider::CheckCollision(LineCollider* other)
{
	// Para cada segmento, comprueba si colisiona con la l�nea
	for (unsigned int i = 0; i < points.size() - 1; ++i)	// Empieza desde el primero y acaba en el pen�ltimo
		if (CreateSegmentCollider(i).CollidesWith(other))
			return true;
	return false;	// Llegados a este punto, ning�n segmento colisiona con la l�nea
}

void LineCollider::DrawCollider()
{
	// Determina el color del collider
	SDL_Color color;
	color.r = 179;
	color.g = 179;
	color.b = 0;
	color.a = 128;

	// Renderiza cada uno de los cuadrados que conforman la l�nea
	for (unsigned int i = 0; i < points.size() - 1; ++i)	// Empieza desde el primero y acaba en el pen�ltimo
		CreateSegmentCollider(i).DrawCollider(color);
}

fPoint LineCollider::GetPointGlobalCoordinates(unsigned int index)
{
	fPoint coordinates = points[index];
	coordinates.x *= transform->GetGlobalScale().x;
	coordinates.y *= transform->GetGlobalScale().y;
	return transform->GetGlobalPosition() + coordinates.Rotate(transform->GetGlobalRotation());
}

RectangleCollider LineCollider::CreateSegmentCollider(int leftBoundIndex)
{
	// Calcula el centro del segmento
	// Las coordenadas ser�n locales dado que el rect�ngulo poseer� el mismo transform
	fPoint leftBound = points[leftBoundIndex];
	fPoint rightBound = points[leftBoundIndex + 1];
	fPoint segment = rightBound - leftBound;
	fPoint center = leftBound + segment * (1.0f / 2.0f);

	// Calcula las dimensiones del segmento
	float width = leftBound.DistanceTo(rightBound) + thickness;
	float height = thickness;

	// Calcula la pendiente del segmento
	float rotation = (float) (atan2(segment.y, segment.x) * 180 / M_PI);

	// Crea y devuelve el rect�ngulo adecuado
	return RectangleCollider(NULL, transform, width, height, center.x, center.y, rotation, type);
}
