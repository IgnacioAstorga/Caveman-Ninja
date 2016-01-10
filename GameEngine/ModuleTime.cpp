#include "ModuleTime.h"
#include "Timer.h"

#include "SDL.h"

#include <stdlib.h>
#include <time.h>

ModuleTime::ModuleTime(bool start_enabled) : Module(start_enabled)
{
	// Por ahora no hace nada
}

ModuleTime::~ModuleTime()
{
	// Por ahora no hace nada
}

bool ModuleTime::Start()
{
	// Establece el tiempo de la frame inicial (en milisegundos)
	lastFrameTime = SDL_GetTicks();

	// Establece una semilla para los números aleatorios
	srand((unsigned int) time(NULL));

	return true;
}

update_status ModuleTime::PreUpdate()
{
	// Calcula el tiempo transcurrido entre esta frame y la anterior (en segundos)
	unsigned long newFrameTime = SDL_GetTicks();
	deltaTime = (newFrameTime - lastFrameTime) / 1000.0f;
	lastFrameTime = newFrameTime;

	// Incrementa todos los timers
	for (list<Timer*>::iterator it = timers.begin(); it != timers.end(); ++it)
		if (!(*it)->IsPaused())
			(*it)->Increment(deltaTime);

	return UPDATE_CONTINUE;
}

bool ModuleTime::CleanUp()
{
	// Limpia la lista de timers
	timers.clear();

	return true;
}

float ModuleTime::DeltaTime()
{
	return deltaTime;
}

void ModuleTime::RegisterTimer(Timer * timer)
{
	LOG("Timer registration");

	if (find(timers.begin(), timers.end(), timer) == timers.end())
		timers.push_back(timer);
}

void ModuleTime::UnregisterTimer(Timer * timer)
{
	LOG("Timer unregistration");

	timers.remove(timer);
}
