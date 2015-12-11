#include "Application.h"
#include "ParticleSystem.h"

class TestApp : public Application
{
protected:
	bool OnApplicationStart()
	{
		ParticleSystem ps;
	}
};