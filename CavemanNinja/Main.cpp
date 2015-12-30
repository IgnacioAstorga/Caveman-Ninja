#include "CavemanNinjaApp.cpp"
#include "SDL.h"

int main(int argc, char ** argv)
{
	CavemanNinjaApp* app = new CavemanNinjaApp();

	int return_value = app->Run();

	RELEASE(app);

	return return_value;
}