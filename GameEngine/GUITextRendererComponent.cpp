#include "GUITextRendererComponent.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"

GUITextRendererComponent::GUITextRendererComponent(string text, string fontName, unsigned int size, Color color, GUILocation align, float offsetX, float offsetY, GUILocation location, bool shadow, fPoint shadowOffset, bool start_enabled)
	:GUITextureRendererComponent(nullptr, offsetX, offsetY, location, shadow, shadowOffset, start_enabled)
{
	this->text = text;
	this->size = size;
	this->fontName = fontName;
	this->color = color;
	this->align = align;

	this->storedOffset = fPoint(offsetX, offsetY);
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

	// Establece el offset de acuerdo al alineamiento
	int textureWidth;
	int textureHeight;
	SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
	switch (align)
	{
	case TOP_LEFT:
		offsetX = 0.0f;
		offsetY = 0.0f;
		break;
	case TOP:
		offsetX = -(float)textureWidth / 2.0f;
		offsetY = 0.0f;
		break;
	case TOP_RIGHT:
		offsetX = -(float)textureWidth;
		offsetY = 0.0f;
		break;
	case LEFT:
		offsetX = 0.0f;
		offsetY = -(float)textureHeight / 2.0f;
		break;
	case CENTER:
		offsetX = -(float)textureWidth / 2.0f;
		offsetY = -(float)textureHeight / 2.0f;
	case RIGHT:
		offsetX = -(float)textureWidth;
		offsetY = -(float)textureHeight / 2.0f;
		break;
		break;
	case BOTTOM_LEFT:
		offsetX = 0.0f;
		offsetY = -(float)textureHeight;
		break;
	case BOTTOM:
		offsetX = -(float)textureWidth / 2.0f;
		offsetY = -(float)textureHeight;
		break;
	case BOTTOM_RIGHT:
		offsetX = -(float)textureWidth;
		offsetY = -(float)textureHeight;
		break;
	}
	// Añade el offset original
	offsetX += storedOffset.x;
	offsetY += storedOffset.y;

	return texture;
}