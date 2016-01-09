#include "RectangleBasicCollider.h"
#include "Transform.h"
#include "CircleCollider.h"
#include "CircleTraceCollider.h"
#include "LineCollider.h"

RectangleBasicCollider::RectangleBasicCollider(CollisionListener * listener, Transform * transform, float width, float height, float offsetX, float offsetY, int type, bool start_enabled)
	: RectangleCollider(listener, transform, width, height, offsetX, offsetY, 0.0f, type, start_enabled) {}

RectangleBasicCollider::RectangleBasicCollider(CollisionListener * listener, Transform * transform, float width, float height, vector<int> collisionsTypes, float offsetX, float offsetY, int type, bool start_enabled)
	: RectangleCollider(listener, transform, width, height, collisionsTypes, offsetX, offsetY, 0.0f, type, start_enabled) {}

RectangleBasicCollider::~RectangleBasicCollider()
{
	// No hace nada
}

bool RectangleBasicCollider::CallMe(Collider * self)
{
	return self->CheckCollision(this);
}

bool RectangleBasicCollider::CheckCollision(CircleCollider * other)
{
	fPoint circleCenter = other->GetCenter();
	fPoint thisCenter = this->GetCenter();
	fPoint thisScale = transform->GetGlobalScale();

	// Encuentra la x del rectángulo más próxima al centro del círculo
	float closestX;
	if (circleCenter.x  < thisCenter.x - width * thisScale.x / 2)
		closestX = thisCenter.x - width * thisScale.x / 2;
	else if (circleCenter.x  > thisCenter.x + width * thisScale.x / 2)
		closestX = thisCenter.x + width * thisScale.x / 2;
	else
		closestX = circleCenter.x;

	// Encuentra la y del rectángulo más próxima al centro del círculo
	float closestY;
	if (circleCenter.y  < thisCenter.y - height * thisScale.y / 2)
		closestY = thisCenter.y - height * thisScale.y / 2;
	else if (circleCenter.y  > thisCenter.y + height * thisScale.y / 2)
		closestY = thisCenter.y + height * thisScale.y / 2;
	else
		closestY = circleCenter.y;

	// Si tanto la x como la y más cercanas son el propio centro del círculo, el centro esta dentro y hay colisión
	if (closestX == circleCenter.x && closestY == circleCenter.y)
		return true;

	// Determina si la distancia al punto más cercano es inferior al radio
	return fPoint(closestX, closestY).DistanceTo(circleCenter) < other->GetRadius();
}

bool RectangleBasicCollider::CheckCollision(RectangleBasicCollider * other)
{
	fPoint otherCenter = other->GetCenter();
	fPoint thisCenter = this->GetCenter();
	fPoint otherMinMax;
	fPoint thisMinMax;

	// Comprueba si hay solapamiento en el eje X
	otherMinMax.x = otherCenter.x - other->width / 2;
	otherMinMax.y = otherCenter.x + other->width / 2;
	thisMinMax.x = thisCenter.x - this->width / 2;
	thisMinMax.y = thisCenter.x + this->width / 2;
	if (!(thisMinMax.x < otherMinMax.y && otherMinMax.y < thisMinMax.y) &&
		!(otherMinMax.x < thisMinMax.y && thisMinMax.y < otherMinMax.y))
		return false;	// No hay solapamiento en el eje X

	// Comprueba si hay solapamiento en el eje Y
	otherMinMax.x = otherCenter.y - other->height / 2;
	otherMinMax.y = otherCenter.y + other->height / 2;
	thisMinMax.x = thisCenter.y - this->height / 2;
	thisMinMax.y = thisCenter.y + this->height / 2;
	if (!(thisMinMax.x < otherMinMax.y && otherMinMax.y < thisMinMax.y) &&
		!(otherMinMax.x < thisMinMax.y && thisMinMax.y < otherMinMax.y))
		return false;	// No hay solapamiento en el eje Y

	return true;	// Llegados a este punto, hay solapamiento en ambos ejes
}

void RectangleBasicCollider::DrawCollider()
{
	// Determina el color y opacidad del dibujo
	SDL_Color renderColor;
	renderColor.r = 0;
	renderColor.g = 0;
	renderColor.b = 179;
	renderColor.a = 128;
	RectangleCollider::DrawCollider(renderColor);
}

fPoint RectangleBasicCollider::GetCenter()
{
	fPoint offset = fPoint(offsetX, offsetY);
	offset.x *= transform->GetGlobalScale().x;
	offset.y *= transform->GetGlobalScale().y;
	return transform->GetGlobalPosition() + offset;
}

float RectangleBasicCollider::GetRotation()
{
	return 0.0f;	// La rotación de este rectángulo siempre es 0
}

fPoint * RectangleBasicCollider::GetPoints()
{
	fPoint center = GetCenter();
	fPoint scale = transform->GetGlobalScale();
	float pointOffsetX = width * scale.x / 2;
	float pointOffsetY = height * scale.y / 2;
	fPoint* points = new fPoint[4];
	points[0] = center + fPoint(-pointOffsetX, -pointOffsetY);
	points[1] = center + fPoint(+pointOffsetX, -pointOffsetY);
	points[2] = center + fPoint(+pointOffsetX, +pointOffsetY);
	points[3] = center + fPoint(-pointOffsetX, +pointOffsetY);
	return points;
}
