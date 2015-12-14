#ifndef __CAMERACOMPONENT_H__
#define __CAMERACOMPONENT_H__

#include "Component.h"
#include "Camera.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Entity.h"

class CameraComponent : public Component
{
public:
	CameraComponent(int width, int height, bool start_active = true, bool start_enabled = true) : Component(start_enabled)
	{
		this->initialWidth = width;
		this->initialHeight = height;
		this->startActive = start_active;
	}

	~CameraComponent()
	{
		RELEASE(camera);
	}

	bool OnStart()
	{
		if (entity == nullptr)
			return false;

		if (camera == nullptr)
			camera = new Camera(entity->transform, initialWidth, initialHeight);

		if (startActive == true)
			App->renderer->SetActiveCamera(camera);

		return true;
	}

	bool OnCleanUp()
	{
		if (camera == nullptr || entity == nullptr)
			return false;

		if (camera->active == true)
			App->renderer->SetActiveCamera(nullptr);
		
		return true;
	}

	Camera* GetCamera() {
		return camera;
	}

private:
	int initialWidth, initialHeight;
	bool startActive;
	Camera* camera;
};

#endif // __CAMERACOMPONENT_H__