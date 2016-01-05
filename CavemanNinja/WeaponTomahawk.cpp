#include "WeaponTomahawk.h"
#include "TomahawkProjectile.h"
#include "Application.h"
#include "ModuleAudio.h"

WeaponTomahawk::WeaponTomahawk()
	: WeaponComponent(fPoint(10,-31), fPoint(150, -100), 0.2f, 2) {}

Entity* WeaponTomahawk::GetWeaponProjectile(fPoint position, int projectileNumber)
{
	return new TomahawkProjectile(this, "tomahawk_" + projectileNumber, position.x, position.y);
}

unsigned int WeaponTomahawk::GetFireSound()
{
	return App->audio->LoadFx("assets/sounds/player_attack.wav");
}
