#include "Application.h"
#include "ModuleScene.h"
#include "ModuleParticles.h"
#include "Scene.h"
#include "ParticleSystem.h"
#include "EmitContinuously.h"
#include "SpeedRandom.h"
#include "LifetimeRandom.h"
#include "ColorRandom.h"
#include "MovementBasic.h"
#include "RotationMatchingSpeed.h"
#include "LifetimeDecay.h"
#include "AlphaFadeInOut.h"
#include "SpriteRenderer.h"
#include "Color.h"

#include <sstream>

class TestScene : public Scene {};

class TestApp : public Application
{
protected:

	Scene* OnCreateScene()
	{
		return new TestScene();
	}

	bool OnPopulateScene(Scene* scene)
	{
		Animation* a = new Animation();
		a->speed = 24.0f;
		a->frames.push_back({ 0, 0, 60, 60 });
		a->frames.push_back({ 60, 0, 60, 60 });
		a->frames.push_back({ 120, 0, 60, 60 });
		a->frames.push_back({ 0, 60, 60, 60 });
		a->frames.push_back({ 60, 60, 60, 60 });
		a->frames.push_back({ 120, 60, 60, 60 });

		Entity* en1 = new Entity();
		en1->Instantiate("try", 100, 100, scene);
		Entity* en2 = new Entity();
		en2->Instantiate("try", 0, 0, scene);
		en1->AddChild(en2);

		ParticleSystem* ps = new ParticleSystem(en2->transform);
		ps->Add(new EmitContinuously(20));
		ps->Add(new SpeedRandom(300, 500, -100, 100));
		ps->Add(new LifetimeRandom(0.5, 2));
		ps->Add(new ColorRandom(Color(0.5f, 0.65f, 1.0f), Color(0.65f, 0.85f, 1.0f)));
		ps->Add(new MovementBasic());
		ps->Add(new RotationMatchingSpeed());
		ps->Add(new LifetimeDecay());
		ps->Add(new AlphaFadeInOut(0.1f, 0.75f));
		ps->Add(new SpriteRenderer("try_animated_white.png", a));
		App->particles->RegisterParticleSystem(ps);

		return true;
	}
};