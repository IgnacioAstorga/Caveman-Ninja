#include "WeaponBoomerang.h"
#include "BoomerangProjectile.h"
#include "BoomerangBigProjectile.h"
#include "Application.h"
#include "ModuleAudio.h"

#define RANGED_OFFSET {10, -31}
#define CHARGE_TIME 1.35f
#define DELAY 0.25f
#define MAX_PROJECTILE_COUNT 2
#define INITIAL_SPEED {200, 0}
#define INITIAL_SPEED_CHARGED {400, 0}

WeaponBoomerang::WeaponBoomerang(CircleColliderComponent* meleeComponent, fPoint meleeOffset)
	: WeaponComponent(meleeComponent, meleeOffset, RANGED_OFFSET, CHARGE_TIME, DELAY, MAX_PROJECTILE_COUNT) {}

Entity* WeaponBoomerang::GetWeaponProjectile(fPoint position, int projectileNumber, bool up)
{
	return new BoomerangProjectile("boomerang_" + projectileNumber, position.x, position.y);
}

Entity * WeaponBoomerang::GetChargedWeaponProjectile(fPoint position, int projectileNumber)
{
	return new BoomerangBigProjectile("boomerang_big_" + projectileNumber, position.x, position.y);
}

fPoint WeaponBoomerang::GetInitialSpeed()
{
	return INITIAL_SPEED;
}

fPoint WeaponBoomerang::GetInitialChargedSpeed()
{
	return INITIAL_SPEED_CHARGED;
}

unsigned int WeaponBoomerang::GetFireSound()
{
	return App->audio->LoadFx("assets/sounds/player_attack.wav");
}
