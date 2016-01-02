#include "GUITextRendererComponent.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"

GUITextRendererComponent::GUITextRendererComponent(string text, string fontName, unsigned int size, Color color, float offsetX, float offsetY, GUILocation location, bool start_enabled)
	:GUITextureRendererComponent(nullptr, offsetX, offsetY, location, start_enabled)
{
	this->text = text;
	this->size = size;
	this->fontName = fontName;
	this->color = color;
}

GUITextRendererComponent::~GUITextRendererComponent()
{
	// En principio no hace nada
}

SDL_Texture * GUITextRendererComponent::OnLoadTexture()
{
	// Crea la fuente
	SetFont(fontName);

	// Crea y devuelve la textura
	return CreateTexture();
}

void GUITextRendererComponent::SetText(string text)
{
	this->text = text;
	texture = CreateTexture();	// Recrea la textura
}

string GUITextRendererComponent::GetText()
{
	return text;
}

void GUITextRendererComponent::SetFont(string fontName)
{
	SetFont(fontName, this->size);
}

void GUITextRendererComponent::SetFont(string fontName, unsigned int size)
{
	if (font != nullptr)
		App->fonts->Unload(font);	// Descarga la textura anterior

	font = App->fonts->Load(fontName.c_str(), size);
	texture = CreateTexture();	// Recrea la textura
}

string GUITextRendererComponent::GetFontName()
{
	return fontName;
}

void GUITextRendererComponent::SetSize(unsigned int size)
{
	this->size = size;
	SetFont(fontName);	// La textura será creada por el método SetFont
}

unsigned int GUITextRendererComponent::GetSize()
{
	return size;
}

void GUITextRendererComponent::SetColor(Color color)
{
	this->color = color;
	texture = CreateTexture();	// Recrea la textura
}

Color GUITextRendererComponent::GetColor()
{
	return color;
}

SDL_Texture* GUITextRendererComponent::CreateTexture()
{
	// Crea una textura a partir del texto y su fuente
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color.ToSDLColor());
	texture = SDL_CreateTextureFromSurface(App->renderer->renderer, surface);
	return texture;
}