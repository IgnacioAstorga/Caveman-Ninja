#include "Application.h"
#include "ModuleScene.h"
#include "ModuleParticles.h"
#include "Scene.h"
#include "ParticleSystem.h"
#include "EmitContinuously.h"
#include "SpeedRandom.h"
#include "LifetimeRandom.h"
#include "MovementBasic.h"
#include "LifetimeDecay.h"
#include "SpriteRenderer.h"

class TestScene : public Scene
{
protected:
};

class TestApp : public Application
{
protected:

	Scene* OnCreateScene()
	{
		return new TestScene();
	}

	bool OnPopulateScene(Scene* scene) {
		ParticleSystem* ps = new ParticleSystem();
		ps->Add(new EmitContinuously(10));
		ps->Add(new SpeedRandom(100, 300, 100, 300));
		ps->Add(new LifetimeRandom(0.5, 2));
		ps->Add(new MovementBasic());
		ps->Add(new LifetimeDecay());
		ps->Add(new SpriteRenderer("try.png"));
		App->particles->RegisterParticleSystem(ps);

		return true;
	}
};