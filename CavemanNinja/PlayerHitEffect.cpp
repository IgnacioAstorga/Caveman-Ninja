#include "PlayerHitEffect.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"
#include "EffectLifespanComponent.h"

void PlayerHitEffect::OnCreate()
{
	BasicAnimation* animation = new BasicAnimation(12.0f, SDL_FLIP_NONE, false);
	animation->frames.push_back({ 64, 64, 64, 64 });
	animation->frames.push_back({ 128, 64, 64, 64 });
	animation->frames.push_back({ 192, 64, 64, 64 });

	AddComponent(new SpriteRendererComponent("assets/images/effects.png", animation, -32, -32));
	AddComponent(new EffectLifespanComponent(0.25f));
}
