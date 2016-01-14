#include "Camera.h"
#include "SDL_rect.h"
#include "Transform.h"

Camera::Camera(Transform* transform, int width, int height, bool start_active) : active(start_active)
{
	this->transform = transform;
	this->width = width;
	this->height = height;
}

Camera::~Camera()
{
	// En principio no hace nada
}

SDL_Rect Camera::GetViewArea()
{
	fPoint cameraPosition = transform->GetGlobalPosition();
	fPoint cameraScale = transform->GetGlobalScale();

	SDL_Rect viewArea;
	viewArea.x = (int)cameraPosition.x;
	viewArea.y = (int)cameraPosition.y;
	viewArea.w = (int)(width * cameraScale.x);
	viewArea.h = (int)(height * cameraScale.y);

	return viewArea;
}

bool Camera::Contains(fPoint point)
{
	fPoint cameraPosition = transform->GetGlobalPosition();
	fPoint cameraScale = transform->GetGlobalScale();
	if (point.x < cameraPosition.x || point.x > cameraPosition.x + (width * cameraScale.x / SCREEN_SIZE))
		return false;
	else if (point.y < cameraPosition.y || point.y > cameraPosition.y + (height * cameraScale.y / SCREEN_SIZE))
		return false;
	else
		return true;
}
