#include "CameraComponent.h"
#include "Camera.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Entity.h"

CameraComponent::CameraComponent(int width, int height, bool start_active, bool start_enabled) : Component(start_enabled)
{
	this->initialWidth = width;
	this->initialHeight = height;
	this->startActive = start_active;
}

CameraComponent::~CameraComponent()
{
	RELEASE(camera);
}

bool CameraComponent::OnStart()
{
	if (entity == nullptr)
		return false;

	if (camera == nullptr)
		camera = new Camera(entity->transform, initialWidth, initialHeight);

	if (startActive == true)
		App->renderer->SetActiveCamera(camera);

	return true;
}

bool CameraComponent::OnCleanUp()
{
	if (camera == nullptr || entity == nullptr)
		return false;

	if (camera->active == true)
		App->renderer->SetActiveCamera(nullptr);

	return true;
}

Camera* CameraComponent::GetCamera() const
{
	return camera;
}