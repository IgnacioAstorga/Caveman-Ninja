#ifndef __CAMERA_H__
#define __CAMERA_H__

struct SDL_Rect;
class Transform;

class Camera
{
public:
	Camera(Transform* transform, int width, int height, bool start_active = false);
	~Camera();

public:
	SDL_Rect GetViewArea();

	bool active;

private:
	Transform* transform;
	int width, height;
};

#endif // __CAMERA_H__