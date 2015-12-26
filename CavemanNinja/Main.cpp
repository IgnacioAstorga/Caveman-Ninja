#include "TestApp.cpp"

int main(int argc, char ** argv)
{
	TestApp* app = new TestApp();

	int return_value = app->Run();

	RELEASE(app);

	return return_value;
}