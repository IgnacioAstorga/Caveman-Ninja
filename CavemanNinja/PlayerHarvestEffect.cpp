#include "PlayerHarvestEffect.h"
#include "SpriteRendererComponent.h"
#include "BasicAnimation.h"

void PlayerHarvestEffect::OnCreate()
{
	BasicAnimation* animation = new BasicAnimation(256, 128, 4, 2, 0.0f, false);
	animation->frames.push_back({ 0, 0 });

	AddComponent(new SpriteRendererComponent("assets/images/effects.png", animation, -32, -32));
}
