#include "PlayerHarvestEffect.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "EffectLifespanComponent.h"

void PlayerHarvestEffect::OnCreate()
{
	BasicAnimation* animation = new BasicAnimation(0.0f, SDL_FLIP_NONE, false);
	animation->frames.push_back({ 0, 0, 64, 64 });

	AddComponent(new SpriteRendererComponent("assets/images/effects.png", animation, -32, -32));
}
