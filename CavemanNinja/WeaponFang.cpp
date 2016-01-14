#include "WeaponFang.h"
#include "FangProjectile.h"
#include "FangBigProjectile.h"
#include "Application.h"
#include "ModuleAudio.h"

#define RANGED_OFFSET {10, -31}
#define CHARGE_TIME 1.0f
#define DELAY 0.15f
#define MAX_PROJECTILE_COUNT 3
#define INITIAL_SPEED {200, 0}
#define INITIAL_SPEED_CHARGED {300, 0}

WeaponFang::WeaponFang(CircleColliderComponent* meleeComponent, fPoint meleeOffset)
	: WeaponComponent(meleeComponent, meleeOffset, RANGED_OFFSET, CHARGE_TIME, DELAY, MAX_PROJECTILE_COUNT) {}

Entity* WeaponFang::GetWeaponProjectile(fPoint position, int projectileNumber, bool up)
{
	return new FangProjectile(up, "fang_" + projectileNumber, position.x, position.y);
}

Entity * WeaponFang::GetChargedWeaponProjectile(fPoint position, int projectileNumber)
{
	return new FangBigProjectile("fang_big_" + projectileNumber, position.x, position.y);
}

fPoint WeaponFang::GetInitialSpeed()
{
	return INITIAL_SPEED;
}

fPoint WeaponFang::GetInitialChargedSpeed()
{
	return INITIAL_SPEED_CHARGED;
}

unsigned int WeaponFang::GetFireSound()
{
	return App->audio->LoadFx("assets/sounds/player_attack.wav");
}
