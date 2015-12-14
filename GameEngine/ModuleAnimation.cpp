#include "ModuleAnimation.h"
#include "Application.h"
#include "ModuleTime.h"
#include "Animation.h"

#include <algorithm>

ModuleAnimation::ModuleAnimation(bool start_enabled) : Module(start_enabled)
{
	// No hace nada
}

ModuleAnimation::~ModuleAnimation()
{
	// No hace nada
}

bool ModuleAnimation::Start()
{
	LOG("Starting Animation Module");

	bool ret = true;

	for (list<Animation*>::iterator it = animations.begin(); it != animations.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->Start();

	return ret;
}

update_status ModuleAnimation::PostUpdate()
{	
	// Incrementa la frame de cada animaci�n registrada en base al tiempo transcurrido
	float deltaTime = App->time->DeltaTime();
	for (list<Animation*>::iterator it = animations.begin(); it != animations.end(); ++it)
		if ((*it)->IsEnabled())
			(*it)->Increment(deltaTime);

	return UPDATE_CONTINUE;
}

bool ModuleAnimation::CleanUp()
{
	LOG("Cleaning up Animation Module");

	// Limpia la lista de animaciones
	bool ret = true;

	for (list<Animation*>::iterator it = animations.begin(); it != animations.end() && ret; ++it)
		if ((*it)->IsEnabled())
			ret = (*it)->CleanUp();
	animations.clear();

	return ret;
}

void ModuleAnimation::RegisterAnimation(Animation* animation)
{
	LOG("Animation registration");

	if (std::find(animations.begin(), animations.end(), animation) == animations.end())
	{
		animations.push_back(animation);
		animation->Start();
	}
}

void ModuleAnimation::UnregisterAnimation(Animation* animation)
{
	LOG("Animation unregistration");

	if (std::find(animations.begin(), animations.end(), animation) == animations.end())
	{
		animations.remove(animation);
		animation->CleanUp();
	}
}