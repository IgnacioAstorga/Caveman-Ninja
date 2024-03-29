#include "RectangleCollider.h"
#include "Transform.h"
#include "CollisionListener.h"
#include "CircleCollider.h"
#include "CircleTraceCollider.h"
#include "RectangleBasicCollider.h"
#include "LineCollider.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

RectangleCollider::RectangleCollider(CollisionListener* listener, Transform* transform, float width, float height, float offsetX, float offsetY, float rotation, int type, bool start_enabled)
	: Collider(listener, transform, type, start_enabled)
{
	this->width = width;
	this->height = height;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->rotation = rotation;
}

RectangleCollider::RectangleCollider(CollisionListener * listener, Transform * transform, float width, float height, vector<int> collisionsTypes, float offsetX, float offsetY, float rotation, int type, bool start_enabled)
	: Collider(listener, transform, collisionsTypes, type, start_enabled)
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

bool RectangleCollider::CallMe(const Collider* self) const
{
	return self->CheckCollision(this);
}

bool RectangleCollider::CheckCollision(const CircleCollider* other) const
{
	float angle = -(float)(GetRotation() * M_PI / 180.0f);
	fPoint thisCenter = GetCenter();
	fPoint thisScale = transform->GetGlobalScale();
	fPoint circleCenter = other->GetCenter();

	// Calcula la posici�n del c�rculo como si el ret�ngulo no estuviese rotado
	fPoint newCirclePosition;
	newCirclePosition.x = cos(angle) * (circleCenter.x - thisCenter.x) - sin(angle) * (circleCenter.y - thisCenter.y) + thisCenter.x;
	newCirclePosition.y = sin(angle) * (circleCenter.x - thisCenter.x) + cos(angle) * (circleCenter.y - thisCenter.y) + thisCenter.y;

	// Encuentra la x del rect�ngulo m�s pr�xima al nuevo centro
	float closestX;
	if (newCirclePosition.x  < thisCenter.x - width * thisScale.x / 2)
		closestX = thisCenter.x - width * thisScale.x / 2;
	else if (newCirclePosition.x  > thisCenter.x + width * thisScale.x / 2)
		closestX = thisCenter.x + width * thisScale.x / 2;
	else
		closestX = newCirclePosition.x;

	// Encuentra la y del rect�ngulo m�s pr�xima al nuevo centro
	float closestY;
	if (newCirclePosition.y  < thisCenter.y - height * thisScale.y / 2)
		closestY = thisCenter.y - height * thisScale.y / 2;
	else if (newCirclePosition.y  > thisCenter.y + height * thisScale.y / 2)
		closestY = thisCenter.y + height * thisScale.y / 2;
	else
		closestY = newCirclePosition.y;

	// Si tanto la x como la y m�s cercanas son el propio centro del c�rculo, el centro esta dentro y hay colisi�n
	if (closestX == newCirclePosition.x && closestY == newCirclePosition.y)
		return true;

	// Determina si la distancia al punto m�s cercano es inferior al radio
	return fPoint(closestX, closestY).DistanceTo(newCirclePosition) < other->GetRadius();
}

bool RectangleCollider::CheckCollision(const CircleTraceCollider* other) const
{
	// Delega la responsabilidad en el otro collider
	return other->CheckCollision(this);
}

bool RectangleCollider::CheckCollision(const RectangleCollider* other) const
{
	// Si el rect�ngulo no tiene altura ni anchura, es un punto
	if (height == 0.0f && width == 0.0f)
		return other->CheckCollision(new CircleCollider(NULL, transform, 0.0f, offsetX, offsetY, type));

	// Primero comprueba que est�n cerca
	CircleCollider thisBound = this->GetBoundingCircle();
	CircleCollider otherBound = other->GetBoundingCircle();
	if (!thisBound.CheckCollision(&otherBound))
		return false;

	// Obtiene los puntos de los rect�ngulos
	fPoint* thisPoints = this->GetPoints();
	fPoint* otherPoints = other->GetPoints();

	// Calcula los ejes de proyecci�n
	fPoint* axis = new fPoint[4];
	axis[0] = thisPoints[1] - thisPoints[0];
	axis[1] = thisPoints[3] - thisPoints[0];
	axis[2] = otherPoints[1] - otherPoints[0];
	axis[3] = otherPoints[3] - otherPoints[0];

	// Comprueba los casos especiales, utilizando perpendiculares
	if (this->width == 0.0f)
		axis[0] = fPoint(-axis[1].y, axis[1].x);
	if (this->height == 0.0f)
		axis[1] = fPoint(axis[0].y, -axis[0].x);
	if (other->width == 0.0f)
		axis[2] = fPoint(-axis[3].y, axis[3].x);
	if (other->height == 0.0f)
		axis[3] = fPoint(axis[2].y, -axis[2].x);

	// Recorre los ejes
	bool collides = false;
	for (unsigned int i = 0; i < 4; ++i)
	{
		// Calcula la proyecci�n de todos los puntos de cada rect�ngulo sobre el eje
		// Hace el producto escalar para obtener un valor normalizado con el que comparar
		float* thisProyections = new float[4];
		float* otherProyections = new float[4];
		for (unsigned int j = 0; j < 4; ++j)
		{
			float factor;
			fPoint proyection;

			factor = thisPoints[j].x * axis[i].x + thisPoints[j].y * axis[i].y;
			factor /= pow(axis[i].x, 2) + pow(axis[i].y, 2);
			proyection = axis[i] * factor;
			thisProyections[j] = proyection.x * axis[i].x + proyection.y * axis[i].y;

			factor = otherPoints[j].x * axis[i].x + otherPoints[j].y * axis[i].y;
			factor /= pow(axis[i].x, 2) + pow(axis[i].y, 2);
			proyection = axis[i] * factor;
			otherProyections[j] = proyection.x * axis[i].x + proyection.y * axis[i].y;
		}

		// Calcula la menor y mayor proyecci�n de cada rect�ngulo
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

		// Libera la memoria utilizada
		RELEASE_ARRAY(otherProyections);
		RELEASE_ARRAY(thisProyections);

		// Comprueba si hay solapamiento en el eje
		if (thisMin < otherMax && otherMax < thisMax)
			collides = true;
		else if (otherMin < thisMax && thisMax < otherMax)
			collides = true;
		else
		{
			collides = false;
			break;
		}
	}

	// Libera la memoria utilizada
	RELEASE_ARRAY(axis);
	RELEASE_ARRAY(otherPoints);
	RELEASE_ARRAY(thisPoints);

	return collides;
}

bool RectangleCollider::CheckCollision(const RectangleBasicCollider * other) const
{
	return CheckCollision((RectangleCollider*) other);
}

bool RectangleCollider::CheckCollision(const LineCollider* other) const
{
	// Delega la responsabilidad en el otro collider
	return other->CheckCollision(this);
}

void RectangleCollider::DrawCollider() const
{
	// Determina el color y opacidad del dibujo
	SDL_Color renderColor;
	renderColor.r = 179;
	renderColor.g = 0;
	renderColor.b = 0;
	renderColor.a = 128;
	DrawCollider(renderColor);
}

void RectangleCollider::DrawCollider(SDL_Color color) const
{
	// Determina la posici�n del dibujo en pantalla
	fPoint renderPosition = transform->GetGlobalPosition();
	fPoint offset = fPoint(offsetX, offsetY);
	offset.x *= transform->GetGlobalScale().x;
	offset.y *= transform->GetGlobalScale().y;
	renderPosition += offset.Rotate(transform->GetGlobalRotation());

	// Determina la escala del dibujo
	float renderWidth = width * transform->GetGlobalScale().x;
	float renderHeight = height * transform->GetGlobalScale().y;
	if (renderWidth <= 0)
		renderWidth = 1;	// Le da una anchura m�nima para que se vea dibujado
	if (renderHeight <= 0)
		renderHeight = 1;	// Le da una altura m�nima para que se vea dibujado
	fPoint renderScale = fPoint(renderWidth / 64, renderHeight / 64);

	App->renderer->Blit(App->collisions->square, (int)(renderPosition.x - renderWidth / 2), (int)(renderPosition.y - renderHeight / 2), GetRotation(), NULL, &color, NULL, renderScale);
}

fPoint RectangleCollider::GetExternalPositionFromCoordinates(fPoint coordinates) const
{
	// Se limita a devolver las coordenadas adecuadas en el lado superior
	fPoint center = GetCenter();
	fPoint scale = transform->GetGlobalScale();
	float totalRotation = GetRotation();
	fPoint upperLeft = center + fPoint(-width * scale.x / 2, -height * scale.y / 2).Rotate(totalRotation);
	double rads = totalRotation * 2 * M_PI / 360.0;
	float yCoordinate = (float) tan(rads) * (coordinates.x - upperLeft.x) + upperLeft.y;

	return fPoint(coordinates.x, yCoordinate);
}

fPoint RectangleCollider::GetCenter() const
{
	fPoint offset = fPoint(offsetX, offsetY);
	offset.x *= transform->GetGlobalScale().x;
	offset.y *= transform->GetGlobalScale().y;
	return transform->GetGlobalPosition() + offset.Rotate(transform->GetGlobalRotation());
}

float RectangleCollider::GetRotation() const
{
	return transform->GetGlobalRotation() + rotation;
}

fPoint* RectangleCollider::GetPoints() const
{
	fPoint center = GetCenter();
	fPoint scale = transform->GetGlobalScale();
	float pointOffsetX = width * scale.x / 2;
	float pointOffsetY = height * scale.y / 2;
	float totalRotation = GetRotation();
	fPoint* points = new fPoint[4];
	points[0] = center + fPoint(-pointOffsetX, -pointOffsetY).Rotate(totalRotation);
	points[1] = center + fPoint(+pointOffsetX, -pointOffsetY).Rotate(totalRotation);
	points[2] = center + fPoint(+pointOffsetX, +pointOffsetY).Rotate(totalRotation);
	points[3] = center + fPoint(-pointOffsetX, +pointOffsetY).Rotate(totalRotation);
	return points;
}

CircleCollider RectangleCollider::GetBoundingCircle() const
{
	fPoint center = GetCenter();
	float radius = center.DistanceTo(fPoint(center.x + width / 2, center.y + height / 2));
	return CircleCollider(NULL, transform, radius, offsetX, offsetY);
}
