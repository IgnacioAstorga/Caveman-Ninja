#include "WeaponTomahawk.h"
#include "TomahawkProjectile.h"
#include "TomahawkBigProjectile.h"
#include "Application.h"
#include "ModuleAudio.h"

WeaponTomahawk::WeaponTomahawk(CircleColliderComponent* meleeComponent, fPoint meleeOffset)
	: WeaponComponent(meleeComponent, meleeOffset, fPoint(10,-31), 1.25f, 0.2f, 2) {}

Entity* WeaponTomahawk::GetWeaponProjectile(fPoint position, int projectileNumber)
{
	return new TomahawkProjectile(this, "tomahawk_" + projectileNumber, position.x, position.y);
}

Entity * WeaponTomahawk::GetChargedWeaponProjectile(fPoint position, int projectileNumber)
{
	return new TomahawkBigProjectile(this, "tomahawk_big_" + projectileNumber, position.x, position.y);
}

fPoint WeaponTomahawk::GetInitialSpeed()
{
	return fPoint(150, -100);
}

fPoint WeaponTomahawk::GetInitialChargedSpeed()
{
	return fPoint(250, -100);
}

unsigned int WeaponTomahawk::GetFireSound()
{
	return App->audio->LoadFx("assets/sounds/player_attack.wav");
}
