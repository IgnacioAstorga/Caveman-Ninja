#include "Component.h"
#include "Entity.h"

#include <typeinfo>

Component::Component(bool start_enabled) : enabled(start_enabled)
{
	started = false;

	// Llamada al delegado
	OnCreate();
}

Component::~Component()
{
	// Llamada al delegado
	OnDestroy();
}

bool Component::IsEnabled() const
{
	return enabled;
}

bool Component::Enable()
{
	if (enabled == false)
		return enabled = Start();

	return true;
}

bool Component::Disable()
{
	if (enabled == true)
		return enabled = !CleanUp();

	return true;
}

bool Component::Start()
{
	// Solo por si acaso, comprueba que no haya sido inicializado
	if (started == true)
		return true;
	started = true;

	if (!OnStart())
		LOG("Error al hacer Start en el componente: ", typeid(this).name());

	return true;
}

update_status Component::PreUpdate()
{
	if (!OnPreUpdate())
		LOG("Error al hacer Update en el componente: ", typeid(this).name());

	return UPDATE_CONTINUE;
}

update_status Component::Update()
{
	if (!OnUpdate())
		LOG("Error al hacer Update en el componente: ", typeid(this).name());

	return UPDATE_CONTINUE;
}

update_status Component::PostUpdate()
{
	if (!OnPostUpdate())
		LOG("Error al hacer PostUpdate en el componente: ", typeid(this).name());

	return UPDATE_CONTINUE;
}

bool Component::CleanUp()
{
	// Solo por si acaso, comprueba que ya haya sido inicializado
	if (started != true)
		return true;
	started = false;

	if (!OnCleanUp())
		LOG("Error al hacer CleanUp en el componente: ", typeid(this).name());

	return true;
}
