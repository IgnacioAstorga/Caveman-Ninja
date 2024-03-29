#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

class Module
{
public:
	Module(bool active = true);
	virtual ~Module();

	bool IsEnabled() const;
	bool Enable();
	bool Disable();

	virtual bool Init();
	virtual bool Start();
	virtual update_status PreUpdate();
	virtual update_status Update();
	virtual update_status PostUpdate();
	virtual bool CleanUp();

private:
	bool active = true;
};

#endif // __MODULE_H__