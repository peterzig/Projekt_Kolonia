#include "SDL_Textur.h"
#include "SDL_G_Var.h"


SDL_Textur::SDL_Textur()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

SDL_Textur::~SDL_Textur()
{
	free();
}

bool SDL_Textur::loadFromFile(std::string path)
{
	// Usuniecie wczesniejszej tekstury
	free();

	// Finalna tekstura
	SDL_Texture* newTexture = NULL;

	// Zaladowanie obrazka z podanej sciezki
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Nie mozna zaladowac obrazka " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << endl;
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Tworzenie tekstury z powierzchni
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Nie mozna utworzyc tekstury z " << path.c_str() << "! SDL Error: " << SDL_GetError() << endl;
		}
		else
		{
			// Pobranie wymiarow obrazka
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Usuniecie starej powierzchni
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool SDL_Textur::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	// Usuniecie wczesniejszej tekstury
	free();

	// Renderowanie powierzchni tekstu
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		cout << "Nie mozna wyrenderowac powierzchni tekstu! SDL_ttf Error: " << TTF_GetError() << endl;
	}
	else
	{
		// Tworzenie tekstury z powierzchni
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			cout << "Nie mozna utworzyc tekstury z wyrenderowanego tekstu! SDL Error: " << SDL_GetError() << endl;
		}
		else
		{
			// Pobranie wymiarow obrazka
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// Usuniecie starej powierzchni
		SDL_FreeSurface(textSurface);
	}

	// Return success
	return mTexture != NULL;
}

void SDL_Textur::free()
{
	// Zwalnianie tekstury, jesli istnieje
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void SDL_Textur::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulacja RGB tekstury
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void SDL_Textur::setBlendMode(SDL_BlendMode blending)
{
	// Ustawienie funkcji mieszania
	SDL_SetTextureBlendMode(mTexture, blending);
}

void SDL_Textur::setAlpha(Uint8 alpha)
{
	// Modulacja przezroczystosci tekstury
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void SDL_Textur::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	// Ustawienie miejsca renderowania i renderowanie na ekran
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	// Ustawienie rozmiaru renderowania clip
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Renderowanie na ekran
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int SDL_Textur::getWidth()
{
	return mWidth;
}

int SDL_Textur::getHeight()
{
	return mHeight;
}