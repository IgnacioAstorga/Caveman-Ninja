#include "WeaponTomahawk.h"
#include "TomahawkProjectile.h"
#include "TomahawkBigProjectile.h"
#include "Application.h"
#include "ModuleAudio.h"

#define RANGED_OFFSET {10, -31}
#define CHARGE_TIME 1.25f
#define DELAY 0.2f
#define MAX_PROJECTILE_COUNT 2
#define INITIAL_SPEED {150, -100}
#define INITIAL_SPEED_CHARGED {250, -100}

WeaponTomahawk::WeaponTomahawk(CircleColliderComponent* meleeComponent, fPoint meleeOffset)
	: WeaponComponent(meleeComponent, meleeOffset, RANGED_OFFSET, CHARGE_TIME, DELAY, MAX_PROJECTILE_COUNT) {}

Entity* WeaponTomahawk::GetWeaponProjectile(fPoint position, int projectileNumber, bool up)
{
	return new TomahawkProjectile("tomahawk_" + projectileNumber, position.x, position.y);
}

Entity * WeaponTomahawk::GetChargedWeaponProjectile(fPoint position, int projectileNumber)
{
	return new TomahawkBigProjectile("tomahawk_big_" + projectileNumber, position.x, position.y);
}

fPoint WeaponTomahawk::GetInitialSpeed()
{
	return INITIAL_SPEED;
}

fPoint WeaponTomahawk::GetInitialChargedSpeed()
{
	return INITIAL_SPEED_CHARGED;
}

unsigned int WeaponTomahawk::GetFireSound()
{
	return App->audio->LoadFx("assets/sounds/player_attack.wav");
}
