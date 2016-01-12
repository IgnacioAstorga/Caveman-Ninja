#ifndef __CAMERACOMPONENT_H__
#define __CAMERACOMPONENT_H__

#include "Component.h"

class Camera;

class CameraComponent : public Component
{
public:
	CameraComponent(int width, int height, bool start_active = true, bool start_enabled = true);
	virtual ~CameraComponent();

	bool OnStart();
	bool OnCleanUp();

public:

	Camera* GetCamera() const;

private:
	int initialWidth, initialHeight;
	bool startActive;
	Camera* camera;
};

#endif // __CAMERACOMPONENT_H__