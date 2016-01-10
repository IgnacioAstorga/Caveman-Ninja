#include "GUISpriteRendererComponent.h"
#include "GUISpriteRendererComponent.h"
#include "Application.h"
#include "ModuleTextures.h"

GUISpriteRendererComponent::GUISpriteRendererComponent(string fileName, Animation * animation, float offsetX, float offsetY, GUILocation location, bool shadow, fPoint shadowOffset, bool start_enabled)
	: GUITextureRendererComponent(animation, offsetX, offsetY, location, shadow, shadowOffset, start_enabled)
{
	this->fileName = fileName;
}

GUISpriteRendererComponent::~GUISpriteRendererComponent()
{
	// En principio no hace nada
}

SDL_Texture * GUISpriteRendererComponent::OnLoadTexture()
{
	// Carga la textura adecuada
	return App->textures->Load(fileName.c_str());
}

Animation * GUISpriteRendererComponent::GetAnimation()
{
	return animation;
}
