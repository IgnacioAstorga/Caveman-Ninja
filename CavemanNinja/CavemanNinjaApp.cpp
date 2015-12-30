#include "Application.h"
#include "Scene_Level1.h"

class CavemanNinjaApp : public Application
{
protected:

	Scene* OnCreateScene()
	{
		return new Scene_Level1();
	}
};