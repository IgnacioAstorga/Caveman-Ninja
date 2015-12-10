#include "Application.h"

#include "SDL.h"
#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )

int main(int argc, char ** argv)
{
	Application* app = new Application();

	int return_value = app->Run();

	RELEASE(app);

	return return_value;
}