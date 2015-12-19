#include "RectangleCollider.h"
#include "Transform.h"
#include "CollisionListener.h"
#include "CircleCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

RectangleCollider::RectangleCollider(CollisionListener* listener, Transform* trasnform, float width, float height, float offsetX, float offsetY, float rotation, int type, bool start_enabled) : Collider(listener, trasnform, type, start_enabled)
{
	this->width = width;
	this->height = height;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->rotation = rotation;
}

RectangleCollider::~RectangleCollider()
{
	// No hace nada
}

bool RectangleCollider::CallMe(Collider* self)
{
	return self->CheckCollision(this);
}

bool RectangleCollider::CheckCollision(CircleCollider* other)
{
	float angle = (float)(GetRotation() * M_PI / 180.0f);
	fPoint thisCenter = GetCenter();
	fPoint thisScale = transform->GetGlobalScale();
	fPoint circleCenter = other->GetCenter();

	// Calcula la posición del círculo como si el retángulo no estuviese rotado
	fPoint newCirclePosition;
	newCirclePosition.x = cos(angle) * (circleCenter.x - thisCenter.x) - sin(angle) * (circleCenter.y - thisCenter.y) + thisCenter.x;
	newCirclePosition.y = sin(angle) * (circleCenter.x - thisCenter.x) + cos(angle) * (circleCenter.y - thisCenter.y) + thisCenter.y;

	// Encuentra la x del rectángulo más próxima al nuevo centro
	float closestX;
	if (newCirclePosition.x  < thisCenter.x - width * thisScale.x / 2)
		closestX = thisCenter.x - width * thisScale.x / 2;
	else if (newCirclePosition.x  > thisCenter.x + width * thisScale.x / 2)
		closestX = thisCenter.x + width * thisScale.x / 2;
	else
		closestX = newCirclePosition.x;

	// Encuentra la y del rectángulo más próxima al nuevo centro
	float closestY;
	if (newCirclePosition.y  < thisCenter.y - height * thisScale.y / 2)
		closestY = thisCenter.y - height * thisScale.y / 2;
	else if (newCirclePosition.y  > thisCenter.y + height * thisScale.y / 2)
		closestY = thisCenter.y + height * thisScale.y / 2;
	else
		closestY = newCirclePosition.y;

	// Si tanto la x como la y más cercanas son el propio centro del círculo, el centro esta dentro y hay colisión
	if (closestX == newCirclePosition.x && closestY == newCirclePosition.y)
		return true;

	// Determina si la distancia al punto más cercano es inferior al radio
	return fPoint(closestX, closestY).DistanceTo(newCirclePosition) <= other->GetRadius();
}

bool RectangleCollider::CheckCollision(RectangleCollider* other)
{
	// Obtiene los puntos de los rectángulos
	fPoint* thisPoints = this->GetPoints();
	fPoint* otherPoints = other->GetPoints();

	// Calcula los ejes de proyección
	fPoint* axis = new fPoint[4];
	axis[0] = thisPoints[1] - thisPoints[0];
	axis[1] = thisPoints[1] - thisPoints[2];
	axis[2] = otherPoints[0] - otherPoints[3];
	axis[3] = otherPoints[0] - otherPoints[1];

	// Recorre los ejes
	for (unsigned int i = 0; i < 4; ++i)
	{
		// Calcula la proyección de todos los puntos de cada rectángulo sobre el eje
		// Hace el producto escalar para obtener un valor normalizado con el que comparar
		float* thisProyections = new float[4];
		float* otherProyections = new float[4];
		for (unsigned int j = 0; j < 4; ++j)
		{
			float factor;
			fPoint proyection;

			factor = thisPoints[j].x * axis[i].x + thisPoints[j].y * axis[i].y;
			factor /= pow(axis[j].x, 2) + pow(axis[j].y, 2);
			proyection = axis[i] * factor;
			thisProyections[j] = proyection.x * axis[i].x + proyection.y * axis[i].y;

			factor = otherPoints[j].x * axis[i].x + otherPoints[j].y * axis[i].y;
			factor /= pow(axis[j].x, 2) + pow(axis[j].y, 2);
			proyection = axis[i] * factor;
			otherProyections[j] = proyection.x * axis[i].x + proyection.y * axis[i].y;
		}

		// Calcula la menor y mayor proyección de cada rectángulo
		float thisMin, thisMax;
		thisMin = thisMax = thisProyections[0];
		float otherMin, otherMax;
		otherMin = otherMax = otherProyections[0];
		for (unsigned int j = 1; j < 4; ++j)
		{
			if (thisProyections[j] < thisMin)
				thisMin = thisProyections[j];
			else if (thisProyections[j] > thisMax)
				thisMax = thisProyections[j];

			if (otherProyections[j] < otherMin)
				otherMin = otherProyections[j];
			else if (otherProyections[j] > otherMax)
				otherMax = otherProyections[j];
		}

		// Comprueba si hay solapamiento en el eje
		if (!((otherMin <= thisMax) || (otherMax >= thisMin)))
			return false;	// Se ha encontrado un eje que separa a ambos rectángulos

							// Libera la memoria utilizada
		RELEASE_ARRAY(otherProyections);
		RELEASE_ARRAY(thisProyections);
	}

	// Libera la memoria utilizada
	RELEASE_ARRAY(axis);
	RELEASE_ARRAY(otherPoints);
	RELEASE_ARRAY(thisPoints);

	// No se ha encontrado un eje que separa a ambos rectángulos. Hay solapamiento
	return true;
}

void RectangleCollider::DrawCollider()
{
	// TODO
}

fPoint RectangleCollider::GetCenter()
{
	fPoint offset = fPoint(offsetX, offsetY);
	offset.x *= transform->GetGlobalScale().x;
	offset.y *= transform->GetGlobalScale().y;
	return transform->GetGlobalPosition() + offset.Rotate(transform->GetGlobalRotation());
}

float RectangleCollider::GetRotation()
{
	return transform->GetGlobalRotation() + rotation;
}

fPoint* RectangleCollider::GetPoints()
{
	fPoint center = GetCenter();
	fPoint scale = transform->GetGlobalScale();
	float pointOffsetX = width * scale.x / 2;
	float pointOffsetY = height * scale.y / 2;
	fPoint* points = new fPoint[4];
	points[0] = fPoint(center.x - pointOffsetX, center.y - pointOffsetY);
	points[1] = fPoint(center.x + pointOffsetX, center.y - pointOffsetY);
	points[2] = fPoint(center.x + pointOffsetX, center.y + pointOffsetY);
	points[3] = fPoint(center.x - pointOffsetX, center.y + pointOffsetY);
	return points;
}