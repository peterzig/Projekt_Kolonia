
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <conio.h>
//#include "core/Objects.h"
#include <ctime>

using namespace std;
// DO WYJEBANIA////////////////////////////////////////////////////////////////////////////////////////
int ruda = 0, tyton = 0, przyprawy = 0, narzedzia = 0, zloto = 0, bydlo = 0, tkaniny,
drewno = 0, wena = 0, zboze = 0, ubrania = 0, cegla = 0, trzcina = 0, monka = 0, cygara = 0, igly = 0,
jedzenie = 0, beczki = 0, sikor = 0, kakao = 0, s1 = 0, s2 = 0, s3 = 5, s4 = 0, s5 = 21, s6 = 7, s7 = 0,
s8 = 5, s9 = 0, s10 = 21, s11, s12 = 0, s13 = 0, s14 = 5, s15 = 0, s16 = 21, s17 = 7, s18 = 0, s19 = 5, s20 = 0;

//pozycja
int kolumna_stat_1 = 75-14;
int kolumna_stat_2 = 236 - 14;
int kolumna_stat_3 = kolumna_stat_2 +166;
int kolumna_stat_4 = kolumna_stat_3 + 166;
int kolumna_stat_5 = kolumna_stat_4 + 166;

int wiersz_stat_1 = 427;
int wiersz_stat_2 = 500;
int wiersz_stat_3 = 570;
int wiersz_stat_4 = 640;


// DO WYJEBANIA////////////////////////////////////////////////////////////////////////////////////////

// Rozmiar okna
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

// Rozmiary przyciskow (nowa gra,wczytaj gre, zapisz gre, wyjdz z gry, wroc, graj)
const int MAIN_BUTTON_WIDTH = 118;
const int MAIN_BUTTON_HEIGHT = 35;

// Rozmiary przyciskow splashy
const int BUILDINGS_BUTTON_WIDTH = 911;
const int BUILDINGS_BUTTON_HEIGHT = 256;

// Rozmiary przyciskow (zbuduj, zburz)
const int BUILD_BUTTON_WIDTH = 60;
const int BUILD_BUTTON_HEIGHT = 20;

// Rozmiary przyciskow (kup, sprzedaj)
const int BUY_BUTTON_WIDTH = 90;
const int BUY_BUTTON_HEIGHT = 70;

// Rozmiary przyciskow (zasoby)
const int RESOURCES_BUTTON_HEIGHT = 52;
const int RESOURCES_BUTTON_WIDTH = 56;

// Rozmiary przycisku Ulepsz
const int UPGRADE_BUTTON_HEIGHT = 63;
const int UPGRADE_BUTTON_WIDTH = 87;

// Rozmiary przyciskow zakaz budowy
const int ALLOW_BUILD_BUTTON_HEIGHT = 37;
const int ALLOW_BUILD_BUTTON_WIDTH = 105;

// Wspolrzedne przyciskow zakaz budowy
const int A_B_X = 584;
const int A_B_Y = 308;


// Wspolrzedne przyiskow build, destroy
const int C_1 = 17, C_2 = 204, C_3 = 402, C_4 = 596, C_5 = 770;
const int W_1 = 252, W_2 = 488, W_3 = 723;
const int R_R = 66;

// Wspolrzedne ulepszenia
const int U_X = 171, U_Y = 595;

// Rozmiary rectow magazynow
const int gWarehouse_rect_left_x = 9;
const int gWarehouse_rect_left_y = 558;
const int gWarehouse_rect_left_h = 162;
const int gWarehouse_rect_left_w = 197;

const int gWarehouse_rect_right_x = 223;
const int gWarehouse_rect_right_y = 558;
const int gWarehouse_rect_right_h = 162;
const int gWarehouse_rect_right_w = 197;

const int gWarehouse_rect_centre_x = 115;
const int gWarehouse_rect_centre_y = 558;
const int gWarehouse_rect_centre_h = 162;
const int gWarehouse_rect_centre_w = 197;

// Char buffor Ludzie i Pieniadze
char People_char_buffor[4];				int People_int = 1;
char Money_char_buffor[7];				int Money_int = 50000;

// Wspolrzedne Build, Destroy Magazynow
const int C_M_B = 242, C_M_D = 276,  W_M = 701;

// Zmienne do wyswietlania czasu
int h = 0, m = 0, s = 0;

// Kolor renderowanego tekstu
SDL_Color textColor = { 255, 255, 255, 255 };


// Sprity stanow przycisku
enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT,
	BUTTON_SPRITE_MOUSE_OVER_MOTION,
	BUTTON_SPRITE_MOUSE_DOWN,
	BUTTON_SPRITE_MOUSE_UP,
	BUTTON_SPRITE_TOTAL
};

// Stany wyswietlanego ekranu
enum Screen
{
	MAIN,
	LOAD,
	SAVE,
	GAME,
	PUB,
	IND,
	PROD,
	STATS,
	QUIT
} screen, subScreen;

// Akcje dla przyciskow
enum Actions
{
	NEW_GAME,
	CONTINUE_GAME,
	LOAD_GAME,
	SAVE_GAME,
	MAIN_MENU,
	EXIT_GAME,
	BUY,
	BUY_RESOURCE,
	SELL,
	SELL_RESOURCE,
	PUBLIC,
	INDUSTRIAL,
	PRODUCTION,
	VIEW_STATS,
	BUILD,
	DESTROY,
	UPGRADE,
	CANCEL,
	ALLOW_BUILD,
	DENY_BUILD,
	CHANGE_MUSIC,
	NONE
};

// Ladowanie obrazka jako tekstury
SDL_Texture* loadTexture(std::string path);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;
SDL_Renderer* gRenderer2 = NULL;


// Wyswietlane tekstury
SDL_Texture* gTexture = NULL;
SDL_Texture* gTexture2 = NULL;

// Tekstury magazyow
//SDL_Texture* gWarehouse_left = NULL;
//SDL_Texture* gWarehouse_right = NULL;
SDL_Texture* Warehouse_I_texture = NULL;
SDL_Texture* Warehouse_II_texture = NULL;
SDL_Texture* Warehouse_III_texture = NULL;
SDL_Texture* Warehouse_IV_texture = NULL;


// Czworokaty magazynow
SDL_Rect gWarehouse_rect_right;
SDL_Rect gWarehouse_rect_left;
SDL_Rect gWarehouse_rect_centre;

// Czcionka
TTF_Font *gFont = NULL;

// Dzwiek klikania
Mix_Chunk *gClickSound = NULL;
Mix_Music *gBackgroundMusic = NULL;

// Wlaczenie SDL i stworzenie okna
bool init();

// Ladowanie mediow
bool loadMedia();

// Zwalnianie mediow i zamykanie SDL
void close();

bool buy = false;
bool sell = false;

// Mozna budowac
bool allow_build = true;

class LTexture
{
public:
	LTexture();
	~LTexture();

	// Ladowanie obrazka z podanej sciezki
	bool loadFromFile(std::string path);

	// Tworzenie obrazka z tekstu
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

	// Zwalnianie tekstury
	void free();

	// Ustawianie koloru modulacji
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Ustawianie mieszania
	void setBlendMode(SDL_BlendMode blending);

	// Ustawianie modulacji przezroczystosci
	void setAlpha(Uint8 alpha);

	// Renderowanie tekstury w podanym punkcie
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Pobranie rozmiarow obrazka
	int getWidth();
	int getHeight();

private:
	// Aktualna tekstura
	SDL_Texture* mTexture;

	// Rozmiary obrazka
	int mWidth;
	int mHeight;
};

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(std::string path)
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

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
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

void LTexture::free()
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

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulacja RGB tekstury
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	// Ustawienie funkcji mieszania
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	// Modulacja przezroczystosci tekstury
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
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

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

LTexture gTextTexture;
LTexture gPromptTextTexture;
LTexture gTimeTextTexture;

//The application time based timer
class Timer
{
public:
	Timer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	void count();
	void render();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;

	std::stringstream timeText;
};

Timer::Timer()
{
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = true;
	mStarted = true;
}

void Timer::start()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Timer::stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void Timer::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void Timer::unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool Timer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool Timer::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}

void Timer::count()
{
	if (getTicks() % 130 == 0)
	{
		if (s1 < 56)
		{
			s1++;
			s1++;
			s15++;
		}
		if (s5 < 56)
			s5++;
		if (s18 < 56)
			s18++;
	}
	if (getTicks() % 150 == 0)
	{
		if (s2 < 56)
			s2++;
		if (s6 < 56)
			s6++;
		if (s10 < 56)
			s10++;
		if (s11 < 56)
			s11++;
		if (s16 < 56)
			s16++;
	}
	if (getTicks() % 200 == 0)
	{
		if (s3 < 56)
			s3++;
		if (s13 < 56)
			s13++;
		if (s19 < 56)
			s19++;
		if (s12 < 56)
			s12++;
	}
	if (getTicks() % 300 == 0)
	{
		if (s4 < 56)
			s4++;
		if (s7 < 56)
		{
			s7++;
			s7++;
		}
		if (s15 < 56)
			s15++;
		if (s20 < 56)
		{
			s20++;
			s20++;
			s20++;

		}
	}
	if (getTicks() % 200 == 0)
	{
		if (s8 < 56)
			s8++;
		if (s11 < 56)
			s11++;
		if (s14 < 56)
		{

			s14++;
			s14++;
			s14++;
		}
		if (s17 < 56)
			s17++;
	}
	if (getTicks() % 300 == 0)
	{
		s9++;
		if (s1 < 0)
			s1--;
		if (s2 < 0)
			s2--;
		if (s3 < 0)
			s3--;
		if (s4 < 0)
			s4--;
		if (s5 < 0)
			s5--;
		if (s6 < 0)
			s6--;
		if (s7 < 0)
			s7--;
		if (s8 < 0)
			s8--;
		if (s9 < 0)
			s9--;
		if (s10 < 0)
			s10--;
		if (s11 < 0)
			s11--;
		if (s12 < 0)
			s12--;
		if (s13 < 0)
			s13--;
		if (s14 < 0)
			s14--;
		if (s15 < 0)
			s15--;
		if (s16 < 0)
			s16--;
		if (s17 < 0)
			s17--;
		if (s18 < 0)
			s18--;
		if (s19 < 0)
			s19--;
		if (s20 < 0)
			s20--;
	}
	if (s == 60)
	{
		m++;
		s = 0;
	}
	s = (getTicks() / 1000) - (m * 60);
}

void Timer::render()
{

	timeText.str("");
	timeText << m << " m " << s << " sekund";
	// Renderowanie tekstu
	if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
	{
		cout << "Nie mozna wyrenderowac czasu!" << endl;
	}
	else
	{
		gTimeTextTexture.render((350 - gTimeTextTexture.getWidth()), 310);
	}
}

// Czas
Timer timer;


class LButton
{
public:
	LButton(Actions, int, int, int, int, char*);
	LButton(int, Actions, int, int, int, int, char*);
	~LButton();

	// Ustawia pozycje przycisku
	void setPosition(int, int);

	// Kieruje akcja przycisku
	void handleEvent(SDL_Event* e);

	// Wyswietla przycisk
	void render();

	// Ustawia teksture przycisku
	void setTexture();

	// Dzialanie po nacisnieciu na przycisk
	void operation(Actions);

private:
	// Tekstura przycisku
	LTexture gButtonSpriteSheetTexture;

	// id budynku, szerokosc, wysokosc
	int id, w, h, w_b, h_b;

	// Sciezka (nazwa) pliku
	char *img;

	// Pozycja przycisku
	SDL_Point mPosition;

	// Warunek akcji przycisku
	Actions action;

	// Aktualnie wyswietlany sprite
	LButtonSprite mCurrentSprite;
	SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
};

LButton::LButton(Actions action, int width, int height, int pos_x, int pos_y, char *image)
	: action(action), w(width), h(height), mCurrentSprite(BUTTON_SPRITE_MOUSE_OUT)
{
	img = new char[strlen(image) + strlen("imgs/buttons/") + 2];
	strcpy(img, "imgs/buttons/");
	strcat(img, image);

	setPosition(pos_x, pos_y);
	setTexture();
}


LButton::LButton(int ident, Actions action, int width, int height, int pos_x, int pos_y, char *image)
	: id(ident), action(action), w(width), h(height), mCurrentSprite(BUTTON_SPRITE_MOUSE_OUT)
{
	img = new char[strlen(image) + strlen("imgs/buttons/") + 2];
	strcpy(img, "imgs/buttons/");
	strcat(img, image);

	setPosition(pos_x, pos_y);
	setTexture();
}

LButton::~LButton()
{
	this->w = NULL;
	this->h = NULL;
	delete[] img;
	gButtonSpriteSheetTexture.free();
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e)
{
	// Jesli zdarzenie myszy zaszlo
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{


		// Pobierz pozycje myszy
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Sprawdz czy mysz jest na przycisku
		bool inside = true;

		// Czy na prawym panelu
		bool RightPanelButton = false;
		if ((w == BUILDINGS_BUTTON_WIDTH && h == BUILDINGS_BUTTON_HEIGHT) || (w == BUILD_BUTTON_WIDTH && h == BUILD_BUTTON_HEIGHT) || (w == ALLOW_BUILD_BUTTON_WIDTH && h == ALLOW_BUILD_BUTTON_HEIGHT))
			RightPanelButton = true;

		// Czy na prawym panelu
		if (RightPanelButton)
		{
			inside = true;
			// Mysz jest z lewej strony splasha
			if (x < mPosition.x + SCREEN_WIDTH / 3)
			{
				inside = false;
			}
			// Mysz jest z prawej strony splasha
			else if (x > mPosition.x + w + SCREEN_WIDTH / 3)
			{
				inside = false;
			}
			// Mysz jest ponad przyciskiem
			else if (y < mPosition.y)
			{
				inside = false;
			}
			// Mysz jest ponizej przycisku
			else if (y > mPosition.y + h)
			{
				inside = false;
			}

		}
		else
			// Mysz jest z lewej strony przycisku
			if (x < mPosition.x)
			{
				inside = false;
			}
		// Mysz jest z prawej strony przycisku
			else if (x > mPosition.x + w)
			{
				inside = false;
			}
		// Mysz jest ponad przyciskiem
			else if (y < mPosition.y)
			{
				inside = false;
			}
		// Mysz jest ponizej przycisku
			else if (y > mPosition.y + h)
			{
				inside = false;
			}

		// Mysz jest poza przyciskiem
		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}

		// Mysz jest w przycisku
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				if (action!=NONE)
				Mix_PlayChannel(-1, gClickSound, 0);
				SDL_Delay(200);
				operation(action);
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			}
		}
	}
}

void LButton::setTexture()
{
	if (!gButtonSpriteSheetTexture.loadFromFile(img))
	{
		cout << "Nie mozna zaladowac tekstury przycisku!" << endl;
	}
	else
	{
		//Set sprites
		for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
		{
			gSpriteClips[i].x = 0;
			gSpriteClips[i].y = i * h;
			gSpriteClips[i].w = w;
			gSpriteClips[i].h = h;
		}
	}
}

void LButton::render()
{
	gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC !!!!!!!
bool upgrade = true; //zastapion funkcja
int licze_magazyny = 0; // ktory magazyn zbudowalismy
bool MUSIC_ON = true; 
int chatka_drwala = 0; // do wy�wietlania ile jest budynkow, zastopione prez funkcjie
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC !!!!!!!

void LButton::operation(Actions action)
{
	switch (action)
	{
	case NEW_GAME:
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
		gTexture = loadTexture("imgs/left.png");
		screen = GAME;
		subScreen = GAME;
		timer.stop();
		timer.start();
		// Wyzerowanie wszustkiego !!!!!!!!!!
		break;

	case LOAD_GAME:
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
		gTexture = loadTexture("imgs/load_save.png");
		screen = MAIN;
		subScreen = LOAD;
		break;

	case SAVE_GAME:
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
		gTexture = loadTexture("imgs/load_save.png");
		screen = MAIN;
		subScreen = SAVE;
		break;

	case MAIN_MENU:
		if (gTexture != NULL)
		{
			SDL_DestroyTexture(gTexture);
			gTexture = NULL;
		}
		if (gTexture2 != NULL)
		{
			SDL_DestroyTexture(gTexture2);
			gTexture2 = NULL;
		}

		gTexture = loadTexture("imgs/main.png");

		screen = MAIN;
		subScreen = MAIN;
		break;

	case CONTINUE_GAME:
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
		gTexture = loadTexture("imgs/left.png");

		screen = GAME;
		subScreen = GAME;

		break;

	case PUBLIC:
		SDL_DestroyTexture(gTexture2);
		gTexture2 = NULL;
		gTexture2 = loadTexture("imgs/public.png");
		screen = GAME;
		subScreen = PUB;
		break;

	case BUY:
		sell = false;
		buy = true;
		break;

	case BUY_RESOURCE:
		s1++;
		s1++;
		s1++;
		break;

	case SELL:
		buy = false;
		sell = true;
		break;

	case SELL_RESOURCE:
		s1--;
		s1--;
		break;

	case INDUSTRIAL:
		SDL_DestroyTexture(gTexture2);
		gTexture2 = NULL;
		gTexture2 = loadTexture("imgs/production.png");
		screen = GAME;
		subScreen = IND;
		break;

	case PRODUCTION:
		SDL_DestroyTexture(gTexture2);
		gTexture2 = NULL;
		gTexture2 = loadTexture("imgs/farms.png");
		screen = GAME;
		subScreen = PROD;
		break;

	case VIEW_STATS:
		SDL_DestroyTexture(gTexture2);
		gTexture2 = NULL;
		gTexture2 = loadTexture("imgs/statistics.png");
		screen = GAME;
		subScreen = STATS;
		break;

	case EXIT_GAME:
		screen = QUIT;
		break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC
	case BUILD:
		chatka_drwala++;
		break;

	case DESTROY:
		if(chatka_drwala>0)
		chatka_drwala--;
		break;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC

	case CANCEL:
		sell = false;
		buy = false;
		break;

	case ALLOW_BUILD:
		allow_build = true;
		break;

	case DENY_BUILD:
		allow_build = false;
		break;

	case UPGRADE://///////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC
		SDL_DestroyTexture(Warehouse_I_texture);
		Warehouse_I_texture = NULL;
		SDL_DestroyTexture(Warehouse_II_texture);
		Warehouse_II_texture = NULL;
		if (licze_magazyny == 0)
		{

			Warehouse_I_texture = loadTexture("imgs/magazyn2.png");
			Warehouse_II_texture = loadTexture("imgs/magazyn3.png");
		}
		if (licze_magazyny == 1)
		{

			Warehouse_I_texture = loadTexture("imgs/magazyn3.png");
			Warehouse_II_texture = loadTexture("imgs/magazyn4.png");
		}
		if (licze_magazyny == 2)
		{

			Warehouse_I_texture = loadTexture("imgs/magazyn4.png");
			Warehouse_II_texture = loadTexture("imgs/magazyn5.png");
		}
		licze_magazyny++;
		upgrade = false;
		break;
				 /////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC
	case CHANGE_MUSIC:
		if (MUSIC_ON == true)
			MUSIC_ON = false;
		else
			MUSIC_ON = true;
		break;


	}
}


bool init()
{
	// Flaga inicjalizacji
	bool success = true;

	// Inicjalizacja SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL nie zostal zainicjalizowany! SDL Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		// Ustawienie filtrowania tekstury na liniowe
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Ostrzezenie: Liniowe filtrowanie tekstury jest wylaczone!");
		}

		// Tworzenie okna
		gWindow = SDL_CreateWindow("Kolonia", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			cout << "Okno nie zostalo utworzone! SDL Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			SDL_Surface* icon = IMG_Load("imgs/icon.png");
			SDL_SetWindowIcon(gWindow, icon);
			// Tworzenie renderera dla okna
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				cout << "Renderer nie zostal utworzony! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				// Inicjalizacja kolorow renderera
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Inicjalizacja ladowania PNG
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image nie zostal zainicjalizowany! SDL_image Error: " << IMG_GetError() << endl;
					success = false;
				}

				// Inicjalizacja SDL_ttf
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf nie zostal zainicjalizowany! SDL_ttf Error: " << TTF_GetError() << endl;
					success = false;
				}

				// Inicjalizacja SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					cout << "SDL_mixer nie zostal zainicjalizowany! SDL_mixer Error: " << Mix_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	// Flaga powodzenia ladowania
	bool success = true;

	// Ladowanie tekstury
	gTexture = loadTexture("imgs/main.png");
	if (gTexture == NULL)
	{
		cout << "Nie mozna zaladowac obrazka!" << endl;
		success = false;
	}

	// Textury magazynow
	Warehouse_I_texture = loadTexture("imgs/magazyn1.png");
	if (Warehouse_I_texture == NULL)
	{
		cout << "Nie mozna zaladowac obrazka!" << endl;
		success = false;
	}
	Warehouse_II_texture = loadTexture("imgs/magazyn2.png");
	if (Warehouse_II_texture == NULL)
	{
		cout << "Nie mozna zaladowac obrazka!" << endl;
		success = false;
	}
	Warehouse_III_texture = loadTexture("imgs/magazyn3.png");
	if (Warehouse_III_texture == NULL)
	{
		cout << "Nie mozna zaladowac obrazka!" << endl;
		success = false;
	}
	Warehouse_IV_texture = loadTexture("imgs/magazyn4.png");
	if (Warehouse_IV_texture == NULL)
	{
		cout << "Nie mozna zaladowac obrazka!" << endl;
		success = false;
	}


	// Ladowanie czcionki
	gFont = TTF_OpenFont("fonts/Caladea-Regular.ttf", 19);
	if (gFont == NULL)
	{
		cout << "Nie mozna zaladowac czcionki! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}
	else
	{
		// Renderowanie tekstu
		SDL_Color textColor = { 200, 200, 200 };
		if (!gTextTexture.loadFromRenderedText("12", textColor))
		{
			cout << "Nie mozna wyrenderowac tekstu!" << endl;
			success = false;
		}
	}

	// Ladowanie dzwieku klikniecia
	gClickSound = Mix_LoadWAV("sounds/click.wav");
	if (gClickSound == NULL)
	{
		cout << "Nie zaladowano dzwieku  SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}

	// Ladowanie tla muzycznego
	gBackgroundMusic = Mix_LoadMUS("sounds/background.ogg");
	if (gBackgroundMusic == NULL)
	{
		cout << "Nie zaladowano dzwieku tla SDL_mixer Error: " << Mix_GetError() << endl;
		success = false;
	}

	// Ladowanie tekstury
	if (!gPromptTextTexture.loadFromRenderedText("Nacisnij ENTER, aby zresetowac czas.", textColor))
	{
		cout << "Nie mozna wyrenderowac tekstury!" << endl;
		success = false;
	}

	return success;
}

void close()
{
	// Zwalnia zaladowany obrazek
	if (gTexture != NULL)
	{
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
	}
	if (gTexture2 != NULL)
	{
		SDL_DestroyTexture(gTexture2);
		gTexture2 = NULL;
	}



	if (Warehouse_I_texture != NULL)
	{
		SDL_DestroyTexture(Warehouse_I_texture);
		Warehouse_I_texture = NULL;
	}
	if (Warehouse_II_texture != NULL)
	{
		SDL_DestroyTexture(Warehouse_II_texture);
		Warehouse_II_texture = NULL;
	}
	if (Warehouse_III_texture != NULL)
	{
		SDL_DestroyTexture(Warehouse_III_texture);
		Warehouse_III_texture = NULL;
	}
	if (Warehouse_IV_texture != NULL)
	{
		SDL_DestroyTexture(Warehouse_IV_texture);
		Warehouse_IV_texture = NULL;
	}

	// Zwalnia teksture tekstu
	gTextTexture.free();

	// Zwalnia czcionke
	TTF_CloseFont(gFont);
	gFont = NULL;

	// Zwalnia dzwiek
	Mix_FreeChunk(gClickSound);
	gClickSound = NULL;

	// Zwalnia muzyke
	Mix_FreeMusic(gBackgroundMusic);
	gBackgroundMusic = NULL;

	// Zamyka okno
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Zamkniecie systemow SDL'a
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(std::string path)
{
	// Finalna tekstura
	SDL_Texture* newTexture = NULL;

	// Wczytuje obrazek ze sciezki
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Nie mozna wczytac obrazka: " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << endl;
	}
	else
	{
		// Wczytuje teksture z powierzchni pikseli
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Nie mozna utworzyc tekstury z " << path.c_str() << "! SDL Error: " << path.c_str() << SDL_GetError() << endl;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

int main(int argc, char* args[])
{
	// Wlaczenie SDL i stworzenie okna
	if (!init())
		cout << "Blad inicjalizacji!" << endl;
	else
	{
		// Ladowanie mediow
		if (!loadMedia())
			cout << "Nie mozna zaladowac mediow!" << endl;
		else
		{
			// Flaga glownej petli
			bool quit = false;
			// Kolor tekstu
			SDL_Color textC = { 255, 255, 255 };

			// Ekran poczatkowy
			screen = MAIN;

			SDL_Event e;

			SDL_Rect LargeViewport;
			LargeViewport.x = 0;
			LargeViewport.y = 0;
			LargeViewport.w = SCREEN_WIDTH;
			LargeViewport.h = SCREEN_HEIGHT;

			SDL_Rect LeftViewport;
			LeftViewport.x = 0;
			LeftViewport.y = 0;
			LeftViewport.w = SCREEN_WIDTH / 3;
			LeftViewport.h = SCREEN_HEIGHT;

			SDL_Rect RightViewport;
			RightViewport.x = SCREEN_WIDTH / 3;
			RightViewport.y = 0;
			RightViewport.w = 2 * SCREEN_WIDTH / 3;
			RightViewport.h = SCREEN_HEIGHT;

			gFont = TTF_OpenFont("fonts/Caladea-Regular.ttf", 19);

			// Przyciski menu
			// przycisk(akcja, szerokosc, wysokosc, poz_x, poz_y, nazwa_pliku)	
			LButton new_game_button(NEW_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 624, 400, "new.png");
			LButton continue_button(CONTINUE_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 624, 350, "continue.png");
			LButton load_game_button(LOAD_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 624, 480, "load.png");
			LButton exit_game_button(EXIT_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 624, 660, "exit.png");
			LButton main_menu_button(MAIN_MENU, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 624, 660, "menu.png");
			LButton save_game_button(SAVE_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 150, 732, "save.png");
			LButton back_button(CONTINUE_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 300, 732, "back.png");
			LButton stats_button(VIEW_STATS, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 5, 732, "stats.png");

			// Przyciski splashy
			LButton ind_button(INDUSTRIAL, BUILDINGS_BUTTON_WIDTH, BUILDINGS_BUTTON_HEIGHT, 0, 0, "/buildings/ind.png");
			LButton prod_button(PRODUCTION, BUILDINGS_BUTTON_WIDTH, BUILDINGS_BUTTON_HEIGHT, 0, 256, "/buildings/prod.png");
			LButton pub_button(PUBLIC, BUILDINGS_BUTTON_WIDTH, BUILDINGS_BUTTON_HEIGHT, 0, 512, "/buildings/pub.png");
			

			// Przyciski: kup, sprzedaj
			LButton buy_button(BUY, BUY_BUTTON_WIDTH, BUY_BUTTON_HEIGHT, 335, 250, "buy.png");
			LButton sell_button(SELL, BUY_BUTTON_WIDTH, BUY_BUTTON_HEIGHT, 335, 345, "sell.png");
			LButton cancel_NAV_button(NONE, BUY_BUTTON_WIDTH, BUY_BUTTON_HEIGHT, 335, 440, "cancel_nav.png");
			LButton cancel_AV_button(CANCEL, BUY_BUTTON_WIDTH, BUY_BUTTON_HEIGHT, 335, 440, "cancel_av.png");

			// Przyciski kupowania zasobow
			// przycisk(id, akcja, szerokosc, wysokosc, poz_x, poz_y, nazwa_pliku)
			LButton buy_iron_ore_button(1, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 244, "/resources/iron_ore.png");
			LButton buy_gold_button(2, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 244, "/resources/gold.png");
			LButton buy_cottom_button(3, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 244, "/resources/cottom.png");
			LButton buy_sugarcane_button(4, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 244, "/resources/sugarcane.png");
			LButton buy_food_button(10, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 244, "/resources/food.png");

			LButton buy_tobacco_button(5, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 318, "/resources/tobacco.png");
			LButton buy_cattle_button(6, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 318, "/resources/cattle.png");
			LButton buy_grain_button(7, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 318, "/resources/grain.png");
			LButton buy_flour_button(8, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 318, "/resources/flour.png");
			LButton buy_alcohol_button(14, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 318, "/resources/alcohol.png");

			LButton buy_spices_button(12, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 387, "/resources/spices.png");
			LButton buy_textiles_button(15, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 387, "/resources/textiles.png");
			LButton buy_clothes_button(16, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 387, "/resources/clothes.png");
			LButton buy_cigarettes_button(11, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 387, "/resources/cigarettes.png");
			LButton buy_jewelry_button(17, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 387, "/resources/jewelry.png");

			LButton buy_tools_button(18, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 456, "/resources/tools.png");
			LButton buy_wood_button(19, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 456, "/resources/wood.png");
			LButton buy_bricks_button(20, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 456, "/resources/bricks.png");
			LButton buy_iron_button(9, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 456, "/resources/iron.png");
			LButton buy_cocoa_button(13, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 456, "/resources/cocoa.png");

			// Przyciski sprzedazy zasobow
			// przycisk(id, akcja, szerokosc, wysokosc, poz_x, poz_y, nazwa_pliku)
			LButton sell_iron_ore_button(1, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 244, "/resources/iron_ore.png");
			LButton sell_gold_button(2, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 244, "/resources/gold.png");
			LButton sell_cottom_button(3, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 244, "/resources/cottom.png");
			LButton sell_sugarcane_button(4, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 244, "/resources/sugarcane.png");
			LButton sell_food_button(10, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 244, "/resources/food.png");

			LButton sell_tobacco_button(5, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 318, "/resources/tobacco.png");
			LButton sell_cattle_button(6, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 318, "/resources/cattle.png");
			LButton sell_grain_button(7, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 318, "/resources/grain.png");
			LButton sell_flour_button(8, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 318, "/resources/flour.png");
			LButton sell_alcohol_button(14, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 318, "/resources/alcohol.png");

			LButton sell_spices_button(12, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 387, "/resources/spices.png");
			LButton sell_textiles_button(15, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 387, "/resources/textiles.png");
			LButton sell_clothes_button(16, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 387, "/resources/clothes.png");
			LButton sell_cigarettes_button(11, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 387, "/resources/cigarettes.png");
			LButton sell_jewelry_button(17, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 387, "/resources/jewelry.png");

			LButton sell_tools_button(18, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 456, "/resources/tools.png");
			LButton sell_wood_button(19, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 456, "/resources/wood.png");
			LButton sell_bricks_button(20, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 456, "/resources/bricks.png");
			LButton sell_iron_button(9, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 456, "/resources/iron.png");
			LButton sell_cocoa_button(13, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 456, "/resources/cocoa.png");

			// Przyciski Buduj i Zburz
			// przycisk(id, akcja, szerokosc, wysokosc, poz_x, poz_y, nazwa_pliku)

			// Production
			// CottonPlantation
			LButton build_NAV_CottonPlantation(19, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_3, "build_nav.png");
			LButton destroy_NAV_CottonPlantation(19, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_3, "destroy_nav.png");
			LButton build_AV_CottonPlantation(19, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_3, "build_av.png");
			LButton destroy_AV_CottonPlantation(19, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_3, "destroy_av.png");
			// ForestersLodge
			LButton build_AV_ForestersLodge(20, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_av.png");
			LButton destroy_AV_ForestersLodge(20, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_av.png");
			// GrainFarm
			LButton build_NAV_GrainFarm(21, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_nav.png");
			LButton destroy_NAV_GrainFarm(21, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_GrainFarm(21, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_av.png");
			LButton destroy_AV_GrainFarm(21, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_av.png");
			// SpiceFarm
			LButton build_NAV_SpiceFarm(22, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_nav.png");
			LButton destroy_NAV_SpiceFarm(22, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_SpiceFarm(22, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_av.png");
			LButton destroy_AV_SpiceFarm(22, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_av.png");
			// HuntersHut
			LButton build_NAV_HuntersHut(23, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_nav.png");
			LButton destroy_NAV_HuntersHut(23, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_HuntersHut(23, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_av.png");
			LButton destroy_AV_HuntersHut(23, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_av.png");
			// CocoaPlantation
			LButton build_NAV_CocoaPlantation(24, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_3, "build_nav.png");
			LButton destroy_NAV_CocoaPlantation(24, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_3, "destroy_nav.png");
			LButton build_AV_CocoaPlantation(24, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_3, "build_av.png");
			LButton destroy_AV_CocoaPlantation(24, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_3, "destroy_av.png");
			// CattleFarm
			LButton build_NAV_CattleFarm(25, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_nav.png");
			LButton destroy_NAV_CattleFarm(25, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_CattleFarm(25, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_av.png");
			LButton destroy_AV_CattleFarm(25, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_av.png");
			// SheepFarm
			LButton build_NAV_SheepFarm(26, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_nav.png");
			LButton destroy_NAV_SheepFarm(26, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_SheepFarm(26, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_av.png");
			LButton destroy_AV_SheepFarm(26, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_av.png");
			// Winery
			LButton build_NAV_Winery(27, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_nav.png");
			LButton destroy_NAV_Winery(27, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_Winery(27, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_av.png");
			LButton destroy_AV_Winery(27, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_av.png");
			// TobaccoPlantation
			LButton build_NAV_TobaccoPlantation(28, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_nav.png");
			LButton destroy_NAV_TobaccoPlantation(28, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_TobaccoPlantation(28, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_av.png");
			LButton destroy_AV_TobaccoPlantation(28, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_av.png");
			// SugarcanePlantation
			LButton build_NAV_SugarcanePlantation(29, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_nav.png");
			LButton destroy_NAV_SugarcanePlantation(29, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_SugarcanePlantation(29, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_av.png");
			LButton destroy_AV_SugarcanePlantation(29, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_av.png");
			// IronMine
			LButton build_NAV_IronMine(30, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_3, "build_nav.png");
			LButton destroy_NAV_IronMine(30, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_3, "destroy_nav.png");
			LButton build_AV_IronMine(30, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_3, "build_av.png");
			LButton destroy_AV_IronMine(30, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_3, "destroy_av.png");
			// DeepIronMine
			LButton build_NAV_DeepIronMine(31, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_3, "build_nav.png");
			LButton destroy_NAV_DeepIronMine(31, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_3, "destroy_nav.png");
			LButton build_AV_DeepIronMine(31, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_3, "build_av.png");
			LButton destroy_AV_DeepIronMine(31, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_3, "destroy_av.png");
			// GoldMine
			LButton build_NAV_GoldMine(32, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_3, "build_nav.png");
			LButton destroy_NAV_GoldMine(32, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_3, "destroy_nav.png");
			LButton build_AV_GoldMine(32, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_3, "build_av.png");
			LButton destroy_AV_GoldMine(32, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_3, "destroy_av.png");
			// FishersHut
			LButton build_NAV_FishersHut(33, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_nav.png");
			LButton destroy_NAV_FishersHut(33, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_FishersHut(33, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_av.png");
			LButton destroy_AV_FishersHut(33, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_av.png");

			// Processing
			// Bakery
			LButton build_NAV_Bakery(34, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_nav.png");
			LButton destroy_NAV_Bakery(34, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_Bakery(34, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_av.png");
			LButton destroy_AV_Bakery(34, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_av.png");
			// OreRafinery
			LButton build_NAV_OreRafinery(35, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_nav.png");
			LButton destroy_NAV_OreRafinery(35, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_OreRafinery(35, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_av.png");
			LButton destroy_AV_OreRafinery(35, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_av.png");
			// GoldSmith
			LButton build_NAV_GoldSmith(36, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_3, "build_nav.png");
			LButton destroy_NAV_GoldSmith(36, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_3, "destroy_nav.png");
			LButton build_AV_GoldSmith(36, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_3, "build_av.png");
			LButton destroy_AV_GoldSmith(36, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_3, "destroy_av.png");
			// ButchersShop
			LButton build_NAV_ButchersShop(37, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_nav.png");
			LButton destroy_NAV_ButchersShop(37, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_ButchersShop(37, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_av.png");
			LButton destroy_AV_ButchersShop(37, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_av.png");
			// RumDistillery
			LButton build_NAV_RumDistillery(38, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_nav.png");
			LButton destroy_NAV_RumDistillery(38, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_RumDistillery(38, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_av.png");
			LButton destroy_AV_RumDistillery(38, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_av.png");
			// Clothiers
			LButton build_NAV_Clothiers(39, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_3, "build_nav.png");
			LButton destroy_NAV_Clothiers(39, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_3, "destroy_nav.png");
			LButton build_AV_Clothiers(39, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_3, "build_av.png");
			LButton destroy_AV_Clothiers(39, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_3, "destroy_av.png");
			// StoneMason
			LButton build_NAV_StoneMason(40, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_nav.png");
			LButton destroy_NAV_StoneMason(40, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_StoneMason(40, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_av.png");
			LButton destroy_AV_StoneMason(40, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_av.png");
			// TobaccoProduction
			LButton build_NAV_TobaccoProduction(41, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_nav.png");
			LButton destroy_NAV_TobaccoProduction(41, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_TobaccoProduction(41, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_av.png");
			LButton destroy_AV_TobaccoProduction(41, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_av.png");
			// WeavingMill
			LButton build_NAV_WeavingMill(42, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_nav.png");
			LButton destroy_NAV_WeavingMill(42, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_WeavingMill(42, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_av.png");
			LButton destroy_AV_WeavingMill(42, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_av.png");
			// WeavingHut
			LButton build_NAV_WeavingHut(43, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_nav.png");
			LButton destroy_NAV_WeavingHut(43, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_WeavingHut(43, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_av.png");
			LButton destroy_AV_WeavingHut(43, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_av.png");
			// ToolSmith
			LButton build_NAV_ToolSmith(44, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_nav.png");
			LButton destroy_NAV_ToolSmith(44, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_ToolSmith(44, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_av.png");
			LButton destroy_AV_ToolSmith(44, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_av.png");
			// WindMill
			LButton build_NAV_WindMill(45, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_nav.png");
			LButton destroy_NAV_WindMill(45, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_WindMill(45, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_av.png");
			LButton destroy_AV_WindMill(45, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_av.png");

			// Industrial
			// Doctor
			LButton build_NAV_Doctor(2, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_nav.png");
			LButton destroy_NAV_Doctor(2, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_Doctor(2, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_av.png");
			LButton destroy_AV_Doctor(2, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_av.png");
			// PublicBath
			LButton build_NAV_PublicBath(3, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_nav.png");
			LButton destroy_NAV_PublicBath(3, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_PublicBath(3, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_av.png");
			LButton destroy_AV_PublicBath(3, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_av.png");
			// FireDepartment
			LButton build_NAV_FireDepartment(4, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_nav.png");
			LButton destroy_NAV_FireDepartment(4, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_FireDepartment(4, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_av.png");
			LButton destroy_AV_FireDepartment(4, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_av.png");
			// Gallows pojbalo?
			// University
			LButton build_NAV_University(6, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_nav.png");
			LButton destroy_NAV_University(6, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_University(6, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_av.png");
			LButton destroy_AV_University(6, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_av.png");
			// Chapel
			LButton build_NAV_Chapel(7, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_nav.png");
			LButton destroy_NAV_Chapel(7, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_Chapel(7, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_av.png");
			LButton destroy_AV_Chapel(7, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_av.png");
			// Church
			LButton build_NAV_Church(8, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_nav.png");
			LButton destroy_NAV_Church(8, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_Church(8, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_av.png");
			LButton destroy_AV_Church(8, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_av.png");
			// MarketPlace
			LButton build_NAV_MarketPlace(10, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_nav.png");
			LButton destroy_NAV_MarketPlace(10, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_MarketPlace(10, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_av.png");
			LButton destroy_AV_MarketPlace(10, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_av.png");
			// Palace
			LButton build_NAV_Palace(11, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_nav.png");
			LButton destroy_NAV_Palace(11, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_Palace(11, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_av.png");
			LButton destroy_AV_Palace(11, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_av.png");
			// School
			LButton build_NAV_School(12, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_nav.png");
			LButton destroy_NAV_School(12, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_School(12, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_av.png");
			LButton destroy_AV_School(12, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_av.png");
			// Theatre
			LButton build_NAV_Theatre(13, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_nav.png");
			LButton destroy_NAV_Theatre(13, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_nav.png");
			LButton build_AV_Theatre(13, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_av.png");
			LButton destroy_AV_Theatre(13, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_av.png");
			// Tavern
			LButton build_NAV_Tavern(14, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_nav.png");
			LButton destroy_NAV_Tavern(14, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_Tavern(14, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_av.png");
			LButton destroy_AV_Tavern(14, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_av.png");

			// DOMY
			// Pionerzy
			LButton build_NAV_House_L1(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_nav.png");
			LButton destroy_NAV_House_L1(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_House_L1(666, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_av.png");
			LButton destroy_AV_House_L1(666, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_av.png");
			// Osadnicy
			LButton build_NAV_House_L2(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_nav.png");
			LButton destroy_NAV_House_L2(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_House_L2(666, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_av.png");
			LButton destroy_AV_House_L2(666, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_av.png");
			// Mieszczanie
			LButton build_NAV_House_L3(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_nav.png");
			LButton destroy_NAV_House_L3(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_nav.png");
			LButton build_AV_House_L3(666, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_av.png");
			LButton destroy_AV_House_L3(666, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_av.png");
			// Kupcy
			LButton destroy_NAV_House_L4(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_nav.png");
			LButton destroy_AV_House_L4(666, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_av.png");
			// Arystokraci
			LButton destroy_NAV_House_L5(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_nav.png");
			LButton destroy_AV_House_L5(666, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_av.png");

			// Pozwol budowac
			LButton Allow_Build(666, ALLOW_BUILD, ALLOW_BUILD_BUTTON_WIDTH, ALLOW_BUILD_BUTTON_HEIGHT, A_B_X, A_B_Y, "allow_build.png");
			LButton Deny_Build(666, DENY_BUILD, ALLOW_BUILD_BUTTON_WIDTH, ALLOW_BUILD_BUTTON_HEIGHT, A_B_X, A_B_Y, "deny_build.png");
			// Zabron budowac

			//  MAGAZYNY
			// WarehouseIIUpgrade
			LButton upgrade_NAV_Warehouse(15, NONE, UPGRADE_BUTTON_WIDTH, UPGRADE_BUTTON_HEIGHT, U_X, U_Y, "upgrade_nav.png");
			LButton upgrade_AV_Warehouse(15, UPGRADE, UPGRADE_BUTTON_WIDTH, UPGRADE_BUTTON_HEIGHT, U_X, U_Y, "upgrade_av.png");

			// Muzyka i info
			LButton Music_On(CHANGE_MUSIC, 45, 37, 1315, 725, "music_on.png");
			LButton Music_Off(CHANGE_MUSIC, 45, 37, 1315, 725, "music_off.png");

			

			// Wspolrzedne czworokatow magazynu 
			// LEWY
			gWarehouse_rect_left.x = gWarehouse_rect_left_x;
			gWarehouse_rect_left.y = gWarehouse_rect_left_y;
			gWarehouse_rect_left.h = gWarehouse_rect_left_h;
			gWarehouse_rect_left.w = gWarehouse_rect_left_w;
			// PRAWY
			gWarehouse_rect_right.x = gWarehouse_rect_right_x;
			gWarehouse_rect_right.y = gWarehouse_rect_right_y;
			gWarehouse_rect_right.h = gWarehouse_rect_right_h;
			gWarehouse_rect_right.w = gWarehouse_rect_right_w;

			gWarehouse_rect_centre.x = gWarehouse_rect_centre_h;
			gWarehouse_rect_centre.y = gWarehouse_rect_centre_y;
			gWarehouse_rect_centre.h = gWarehouse_rect_centre_h;
			gWarehouse_rect_centre.w = gWarehouse_rect_centre_w;
			// Glowna petla gry
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					// User requests quit
					if (e.type == SDL_QUIT)
						quit = true;

				}
				//If there is no music playing 
				if (Mix_PlayingMusic() == 0)
				{ //Play the music 
					Mix_PlayMusic(gBackgroundMusic, -1);
				}

				// Klawisz ESCAPE - wychodzenie do menu glownego
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if (currentKeyStates[SDL_SCANCODE_ESCAPE])
				{
					if (!(screen == MAIN && subScreen == MAIN))
					{
						if (gTexture2 != NULL)
						{
							SDL_DestroyTexture(gTexture2);
							gTexture2 = NULL;
						}
						SDL_DestroyTexture(gTexture);
						gTexture = NULL;
						gTexture = loadTexture("imgs/main.png");
						screen = MAIN;
						subScreen = MAIN;
					}
				}
				// Ustawianie tekst do renderowania
			
				// Czyszczenie ekranu
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				SDL_Rect fillRect = { 6, 295, s1, 5 };
				SDL_Rect fillRect2 = { 71, 295, s2, 5 };
				SDL_Rect fillRect3 = { 136, 295, s3, 5 };
				SDL_Rect fillRect4 = { 201, 295, s4, 5 };
				SDL_Rect fillRect5 = { 266, 295, s5, 5 };

				SDL_Rect fillRect6 = { 6, 369, s6, 5 };
				SDL_Rect fillRect7 = { 71, 369, s7, 5 };
				SDL_Rect fillRect8 = { 136, 369, s8, 5 };
				SDL_Rect fillRect9 = { 201, 369, s9, 5 };
				SDL_Rect fillRect10 = { 266, 369, s10, 5 };

				SDL_Rect fillRect11 = { 6, 437, s11, 5 };
				SDL_Rect fillRect12 = { 71, 437, s12, 5 };
				SDL_Rect fillRect13 = { 136, 437, s13, 5 };
				SDL_Rect fillRect14 = { 201, 437, s14, 5 };
				SDL_Rect fillRect15 = { 266, 437, s15, 5 };

				SDL_Rect fillRect16 = { 6, 507, s16, 5 };
				SDL_Rect fillRect17 = { 71, 507, s17, 5 };
				SDL_Rect fillRect18 = { 136, 507, s18, 5 };
				SDL_Rect fillRect19 = { 201, 507, s19, 5 };
				SDL_Rect fillRect20 = { 266, 507, s20, 5 };

				switch (screen)
				{
					// Ekran menu glownego
				case MAIN:
					timer.pause();
					SDL_RenderSetViewport(gRenderer, &LargeViewport);
					SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
					switch (subScreen)
					{
					case MAIN:
						if (timer.getTicks() > 0)
						{
							continue_button.render();
							continue_button.handleEvent(&e);
						}
						new_game_button.render();
						load_game_button.render();
						exit_game_button.render();
						new_game_button.handleEvent(&e);
						load_game_button.handleEvent(&e);
						exit_game_button.handleEvent(&e);
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC

						if(MUSIC_ON==true)
						{
							Music_On.render();
							Music_On.handleEvent(&e);
							Mix_ResumeMusic();
						}
						else
						{
							Music_Off.render();
							Music_Off.handleEvent(&e);
							Mix_PauseMusic();
						}
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC

						break;
						// Ekran wczytywania stanu gry
					case LOAD:
						gTextTexture.loadFromRenderedText("Wczytaj", textC);
						gTextTexture.render(600, 200);

						main_menu_button.setPosition(624, 660);
						main_menu_button.render();
						main_menu_button.handleEvent(&e);
						break;
						// Ekran zapisu stanu gry
					case SAVE:
						gTextTexture.loadFromRenderedText("Zapisz", textC);
						gTextTexture.render(624, 200);

						back_button.setPosition(624, 660);
						back_button.render();
						back_button.handleEvent(&e);
						break;
					}
					break;
					// Ekran rozgrywki
				case GAME:
					timer.unpause();
					timer.count();
					SDL_RenderSetViewport(gRenderer, &LeftViewport);
					SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
					// Liczby
					// test

					// Pieniadze
	//TAK		//	gTextTexture.loadFromRenderedText(_itoa(Money_int, Money_char_buffor, 10), textC);
	//BYLO		//	gTextTexture.render(90, 40);
					// Podatki
					gTextTexture.loadFromRenderedText("50000", textC);
					Money_int++;
					gTextTexture.render(90, 40);

					// Koszty
					gTextTexture.loadFromRenderedText("0", textC);
					gTextTexture.render(90, 63);

					// Sprzedaz
					gTextTexture.loadFromRenderedText("0", textC);
					gTextTexture.render(90, 90);

					// Kupno
					gTextTexture.loadFromRenderedText("0", textC);
					gTextTexture.render(90, 113);

					// Bilans
					gTextTexture.loadFromRenderedText("0", textC);
					gTextTexture.render(90, 140);

					// Srodki
					gTextTexture.loadFromRenderedText("0", textC);
					gTextTexture.render(90, 170);


					// Ludnosc
	//TAK		//	gTextTexture.loadFromRenderedText(_itoa(People_int, People_char_buffor, 10), textC);
	//BYLO		//	gTextTexture.render(340, 175);
					// Pionierzy
					gTextTexture.loadFromRenderedText("0", textC);
					gTextTexture.render(340, 38);

					// Osadnicy
					gTextTexture.loadFromRenderedText("0", textC);
					gTextTexture.render(340, 62);

					// Mieszczanie
					gTextTexture.loadFromRenderedText("0", textC);
					gTextTexture.render(340, 90);

					// Kupcy
					gTextTexture.loadFromRenderedText("0", textC);
					gTextTexture.render(340, 117);

					// Arystokraci
					gTextTexture.loadFromRenderedText("0", textC);
					gTextTexture.render(340, 145);

					// Mieszkancy
					gTextTexture.loadFromRenderedText("0", textC);
					gTextTexture.render(340, 175);
					People_int++;

					// Magazyny
					// LVL1////////////////////////////////////////////////////////////////////////////////////////////////////// WWYWALIC (co� z tym zrobic)
					{
						SDL_RenderCopy(gRenderer, Warehouse_I_texture, NULL, &gWarehouse_rect_left);
						SDL_RenderCopy(gRenderer, Warehouse_II_texture, NULL, &gWarehouse_rect_right);
					}
					// LVL2
					/*
					{
						if (Warehouse_I_texture != NULL)
						{
							SDL_DestroyTexture(Warehouse_I_texture);
							Warehouse_I_texture = NULL;
						{
						SDL_RenderCopy(gRenderer, Warehouse_I_texture, NULL, &gWarehouse_rect_left);
						SDL_RenderCopy(gRenderer, Warehouse_III_texture, NULL, &gWarehouse_rect_right);
					}
					// LVL3
					{
						if (Warehouse_I_texture != NULL)
						{
							SDL_DestroyTexture(Warehouse_II_texture);
							Warehouse_I_texture = NULL;
						{
						SDL_RenderCopy(gRenderer, Warehouse_III_texture, NULL, &gWarehouse_rect_left);
						SDL_RenderCopy(gRenderer, Warehouse_IV_texture, NULL, &gWarehouse_rect_right);
					}
					// LVL4
					{
						if (Warehouse_I_texture != NULL)
						{
							SDL_DestroyTexture(Warehouse_III_texture);
							Warehouse_I_texture = NULL;
						{
						SDL_RenderCopy(gRenderer, Warehouse_IV_texture, NULL, &gWarehouse_rect_centre);
					}
					*/
					
					// UPGRADE
					if (upgrade == false)
					{
						upgrade_NAV_Warehouse.render();
						upgrade_NAV_Warehouse.handleEvent(&e);
					}
					else
					{
						upgrade_AV_Warehouse.render();
						upgrade_AV_Warehouse.handleEvent(&e);
					}

					if (buy == true)
					{
						gTextTexture.loadFromRenderedText("Kup", textC);
						gTextTexture.render(250, 210);
						buy_iron_ore_button.render();
						buy_iron_ore_button.handleEvent(&e);
						buy_gold_button.render();
						buy_gold_button.handleEvent(&e);
						buy_cottom_button.render();
						buy_cottom_button.handleEvent(&e);
						buy_sugarcane_button.render();
						buy_sugarcane_button.handleEvent(&e);
						buy_food_button.render();
						buy_food_button.handleEvent(&e);

						buy_tobacco_button.render();
						buy_tobacco_button.handleEvent(&e);
						buy_cattle_button.render();
						buy_cattle_button.handleEvent(&e);
						buy_grain_button.render();
						buy_grain_button.handleEvent(&e);
						buy_flour_button.render();
						buy_flour_button.handleEvent(&e);
						buy_alcohol_button.render();
						buy_alcohol_button.handleEvent(&e);

						buy_spices_button.render();
						buy_spices_button.handleEvent(&e);
						buy_textiles_button.render();
						buy_textiles_button.handleEvent(&e);
						buy_clothes_button.render();
						buy_clothes_button.handleEvent(&e);
						buy_cigarettes_button.render();
						buy_cigarettes_button.handleEvent(&e);
						buy_jewelry_button.render();
						buy_jewelry_button.handleEvent(&e);

						buy_tools_button.render();
						buy_tools_button.handleEvent(&e);
						buy_wood_button.render();
						buy_wood_button.handleEvent(&e);
						buy_bricks_button.render();
						buy_bricks_button.handleEvent(&e);
						buy_iron_button.render();
						buy_iron_button.handleEvent(&e);
						buy_cocoa_button.render();
						buy_cocoa_button.handleEvent(&e);

						cancel_AV_button.render();
						cancel_AV_button.handleEvent(&e);
					}
					else
					if (sell == true)
					{
						gTextTexture.loadFromRenderedText("Sprzedaj", textC);
						gTextTexture.render(250, 210);
						sell_iron_ore_button.render();
						sell_iron_ore_button.handleEvent(&e);
						sell_gold_button.render();
						sell_gold_button.handleEvent(&e);
						sell_cottom_button.render();
						sell_cottom_button.handleEvent(&e);
						sell_sugarcane_button.render();
						sell_sugarcane_button.handleEvent(&e);
						sell_food_button.render();
						sell_food_button.handleEvent(&e);

						sell_tobacco_button.render();
						sell_tobacco_button.handleEvent(&e);
						sell_cattle_button.render();
						sell_cattle_button.handleEvent(&e);
						sell_grain_button.render();
						sell_grain_button.handleEvent(&e);
						sell_flour_button.render();
						sell_flour_button.handleEvent(&e);
						sell_alcohol_button.render();
						sell_alcohol_button.handleEvent(&e);

						sell_spices_button.render();
						sell_spices_button.handleEvent(&e);
						sell_textiles_button.render();
						sell_textiles_button.handleEvent(&e);
						sell_clothes_button.render();
						sell_clothes_button.handleEvent(&e);
						sell_cigarettes_button.render();
						sell_cigarettes_button.handleEvent(&e);
						sell_jewelry_button.render();
						sell_jewelry_button.handleEvent(&e);

						sell_tools_button.render();
						sell_tools_button.handleEvent(&e);
						sell_wood_button.render();
						sell_wood_button.handleEvent(&e);
						sell_bricks_button.render();
						sell_bricks_button.handleEvent(&e);
						sell_iron_button.render();
						sell_iron_button.handleEvent(&e);
						sell_cocoa_button.render();
						sell_cocoa_button.handleEvent(&e);

						cancel_AV_button.render();
						cancel_AV_button.handleEvent(&e);
					}
					else
					{
						cancel_NAV_button.render();
						cancel_NAV_button.handleEvent(&e);
					}
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
					SDL_RenderFillRect(gRenderer, &fillRect);
					SDL_RenderFillRect(gRenderer, &fillRect2);
					SDL_RenderFillRect(gRenderer, &fillRect3);
					SDL_RenderFillRect(gRenderer, &fillRect4);
					SDL_RenderFillRect(gRenderer, &fillRect5);

					SDL_RenderFillRect(gRenderer, &fillRect6);
					SDL_RenderFillRect(gRenderer, &fillRect7);
					SDL_RenderFillRect(gRenderer, &fillRect8);
					SDL_RenderFillRect(gRenderer, &fillRect9);
					SDL_RenderFillRect(gRenderer, &fillRect10);

					SDL_RenderFillRect(gRenderer, &fillRect11);
					SDL_RenderFillRect(gRenderer, &fillRect12);
					SDL_RenderFillRect(gRenderer, &fillRect13);
					SDL_RenderFillRect(gRenderer, &fillRect14);
					SDL_RenderFillRect(gRenderer, &fillRect15);

					SDL_RenderFillRect(gRenderer, &fillRect16);
					SDL_RenderFillRect(gRenderer, &fillRect17);
					SDL_RenderFillRect(gRenderer, &fillRect18);
					SDL_RenderFillRect(gRenderer, &fillRect19);
					SDL_RenderFillRect(gRenderer, &fillRect20);

					buy_button.render();
					buy_button.handleEvent(&e);
					sell_button.render();
					sell_button.handleEvent(&e);
					stats_button.render();
					stats_button.handleEvent(&e);
					save_game_button.render();
					save_game_button.handleEvent(&e);
					switch (subScreen)
					{
						// Ekran rozgrywki - wybor budynkow
					case GAME:
						main_menu_button.setPosition(300, 732);
						main_menu_button.render();
						main_menu_button.handleEvent(&e);

						SDL_RenderSetViewport(gRenderer, &RightViewport);
						ind_button.render();
						prod_button.render();
						pub_button.render();
						ind_button.handleEvent(&e);
						prod_button.handleEvent(&e);
						pub_button.handleEvent(&e);

						break;

						// Ekran rozgrywki - statystyki
					case STATS:
						back_button.setPosition(300, 732);
						back_button.render();
						back_button.handleEvent(&e);
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC
						/*
						if (MUSIC_ON == true)
						{
							Music_On.render();
							Music_On.handleEvent(&e);
							Mix_ResumeMusic();
						}
						else
						{
							Music_Off.render();
							Music_Off.handleEvent(&e);
							Mix_PauseMusic();
						}
						*/
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC

						SDL_RenderSetViewport(gRenderer, &RightViewport);
						SDL_RenderCopy(gRenderer, gTexture2, NULL, NULL);
						timer.render();

						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC
						gTextTexture.loadFromRenderedText(_itoa(s1, Money_char_buffor, 10), textC);			gTextTexture.loadFromRenderedText(_itoa(s11, Money_char_buffor, 10), textC);
						gTextTexture.render(kolumna_stat_1, wiersz_stat_1);									gTextTexture.render(kolumna_stat_3, wiersz_stat_3);
						gTextTexture.loadFromRenderedText(_itoa(s2, Money_char_buffor, 10), textC);			gTextTexture.loadFromRenderedText(_itoa(s12, Money_char_buffor, 10), textC);
						gTextTexture.render(kolumna_stat_1, wiersz_stat_2);									gTextTexture.render(kolumna_stat_3, wiersz_stat_4);
						gTextTexture.loadFromRenderedText(_itoa(s3, Money_char_buffor, 10), textC);			gTextTexture.loadFromRenderedText(_itoa(s13, Money_char_buffor, 10), textC);
						gTextTexture.render(kolumna_stat_1, wiersz_stat_3);									gTextTexture.render(kolumna_stat_4, wiersz_stat_1);
						gTextTexture.loadFromRenderedText(_itoa(s4, Money_char_buffor, 10), textC);			gTextTexture.loadFromRenderedText(_itoa(s14, Money_char_buffor, 10), textC);
						gTextTexture.render(kolumna_stat_1, wiersz_stat_4);									gTextTexture.render(kolumna_stat_4, wiersz_stat_2);
						gTextTexture.loadFromRenderedText(_itoa(s5, Money_char_buffor, 10), textC);			gTextTexture.loadFromRenderedText(_itoa(s15, Money_char_buffor, 10), textC);
						gTextTexture.render(kolumna_stat_2, wiersz_stat_1);									gTextTexture.render(kolumna_stat_4, wiersz_stat_3);
						gTextTexture.loadFromRenderedText(_itoa(s6, Money_char_buffor, 10), textC);			gTextTexture.loadFromRenderedText(_itoa(s16, Money_char_buffor, 10), textC);
						gTextTexture.render(kolumna_stat_2, wiersz_stat_2);									gTextTexture.render(kolumna_stat_4, wiersz_stat_4);
						gTextTexture.loadFromRenderedText(_itoa(s7, Money_char_buffor, 10), textC);			gTextTexture.loadFromRenderedText(_itoa(s17, Money_char_buffor, 10), textC);
						gTextTexture.render(kolumna_stat_2, wiersz_stat_3);									gTextTexture.render(kolumna_stat_5, wiersz_stat_1);
						gTextTexture.loadFromRenderedText(_itoa(s8, Money_char_buffor, 10), textC);			gTextTexture.loadFromRenderedText(_itoa(s18, Money_char_buffor, 10), textC);
						gTextTexture.render(kolumna_stat_2, wiersz_stat_4);									gTextTexture.render(kolumna_stat_5, wiersz_stat_2);
						gTextTexture.loadFromRenderedText(_itoa(s9, Money_char_buffor, 10), textC);			gTextTexture.loadFromRenderedText(_itoa(s19, Money_char_buffor, 10), textC);
						gTextTexture.render(kolumna_stat_3, wiersz_stat_1);									gTextTexture.render(kolumna_stat_5, wiersz_stat_3);
						gTextTexture.loadFromRenderedText(_itoa(s10, Money_char_buffor, 10), textC);		gTextTexture.loadFromRenderedText(_itoa(s20, Money_char_buffor, 10), textC);
						gTextTexture.render(kolumna_stat_3, wiersz_stat_2);									gTextTexture.render(kolumna_stat_5, wiersz_stat_4);
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC


						//gTextTexture.loadFromRenderedText("Zapisz", textC);
					//	gTextTexture.render(624, 200);

						// Pozwolenie i zakaz budowy
						if (allow_build==true)
						{
							Deny_Build.render();
							Deny_Build.handleEvent(&e);
						}
						else
						{
							Allow_Build.render();
							Allow_Build.handleEvent(&e);
						}
						// Buduj zburz domy
						// BUILD								DESTROY
						build_AV_House_L1.render();				destroy_AV_House_L1.render();
						build_AV_House_L1.handleEvent(&e);		destroy_AV_House_L1.handleEvent(&e);

						build_NAV_House_L2.render();			destroy_NAV_House_L2.render();
						build_NAV_House_L2.handleEvent(&e);		destroy_NAV_House_L2.handleEvent(&e);

						build_NAV_House_L3.render();			destroy_NAV_House_L3.render();
						build_NAV_House_L3.handleEvent(&e);		destroy_NAV_House_L3.handleEvent(&e);

						/* Kupcy */								destroy_NAV_House_L4.render();
						/*Tych nie budujemy*/					destroy_NAV_House_L4.handleEvent(&e);

						/* Arystokraci */						destroy_NAV_House_L5.render();
						/*Tych nie budujemy*/					destroy_NAV_House_L5.handleEvent(&e);

						break;
						// Ekran rozgrywki - budynki publiczne
					case PUB:
						back_button.setPosition(300, 732);
						back_button.render();
						back_button.handleEvent(&e);
						SDL_RenderSetViewport(gRenderer, &RightViewport);
						SDL_RenderCopy(gRenderer, gTexture2, NULL, NULL);

						// Obiekty przyciskow
						// RENDER							//HANDLE_EVENT
						build_NAV_Doctor.render();			build_NAV_Doctor.handleEvent(&e);
						destroy_NAV_Doctor.render();		destroy_NAV_Doctor.handleEvent(&e);

						build_NAV_PublicBath.render();		build_NAV_PublicBath.handleEvent(&e);
						destroy_NAV_PublicBath.render();	destroy_NAV_PublicBath.handleEvent(&e);

						build_NAV_FireDepartment.render();	build_NAV_FireDepartment.handleEvent(&e);
						destroy_NAV_FireDepartment.render(); destroy_NAV_FireDepartment.handleEvent(&e);

						build_NAV_University.render();		build_NAV_University.handleEvent(&e);
						destroy_NAV_University.render();	destroy_NAV_University.handleEvent(&e);

						build_AV_Chapel.render();			build_AV_Chapel.handleEvent(&e);
						destroy_AV_Chapel.render();			destroy_AV_Chapel.handleEvent(&e);

						build_NAV_Church.render();			build_NAV_Church.handleEvent(&e);
						destroy_NAV_Church.render();		destroy_NAV_Church.handleEvent(&e);

						build_AV_MarketPlace.render();		build_AV_MarketPlace.handleEvent(&e);
						destroy_AV_MarketPlace.render();	destroy_AV_MarketPlace.handleEvent(&e);

						build_NAV_School.render();			build_NAV_School.handleEvent(&e);
						destroy_NAV_School.render();		destroy_NAV_School.handleEvent(&e);

						build_NAV_Theatre.render();			build_NAV_Theatre.handleEvent(&e);
						destroy_NAV_Theatre.render();		destroy_NAV_Theatre.handleEvent(&e);

						build_NAV_Tavern.render();			build_NAV_Tavern.handleEvent(&e);
						destroy_NAV_Tavern.render();		destroy_NAV_Tavern.handleEvent(&e);
						break;
						// Ekran rozgrywki - przetworstwo
					case IND:
						back_button.setPosition(300, 732);
						back_button.render();
						back_button.handleEvent(&e);
						SDL_RenderSetViewport(gRenderer, &RightViewport);
						SDL_RenderCopy(gRenderer, gTexture2, NULL, NULL);

						// Obiekty przyciskow
						// RENDER								// HANDLE_EVENT
						build_NAV_Bakery.render();				build_NAV_Bakery.handleEvent(&e);
						destroy_NAV_Bakery.render();			destroy_NAV_Bakery.handleEvent(&e);

						build_NAV_OreRafinery.render();			build_NAV_OreRafinery.handleEvent(&e);
						destroy_NAV_OreRafinery.render();		destroy_NAV_OreRafinery.handleEvent(&e);

						build_NAV_GoldSmith.render();			build_NAV_GoldSmith.handleEvent(&e);
						destroy_NAV_GoldSmith.render();			destroy_NAV_GoldSmith.handleEvent(&e);

						build_NAV_ButchersShop.render();		build_NAV_ButchersShop.handleEvent(&e);
						destroy_NAV_ButchersShop.render();		destroy_NAV_ButchersShop.handleEvent(&e);

						build_NAV_RumDistillery.render();		build_NAV_RumDistillery.handleEvent(&e);
						destroy_NAV_RumDistillery.render();		destroy_NAV_RumDistillery.handleEvent(&e);

						build_NAV_Clothiers.render();			build_NAV_Clothiers.handleEvent(&e);
						destroy_NAV_Clothiers.render();			destroy_NAV_Clothiers.handleEvent(&e);

						build_NAV_StoneMason.render();			build_NAV_StoneMason.handleEvent(&e);
						destroy_NAV_StoneMason.render();		destroy_NAV_StoneMason.handleEvent(&e);

						build_NAV_TobaccoProduction.render();	build_NAV_TobaccoProduction.handleEvent(&e);
						destroy_NAV_TobaccoProduction.render(); destroy_NAV_TobaccoProduction.handleEvent(&e);

						build_NAV_WeavingMill.render();			build_NAV_WeavingMill.handleEvent(&e);
						destroy_NAV_WeavingMill.render();		destroy_NAV_WeavingMill.handleEvent(&e);

						build_AV_WeavingHut.render();			build_AV_WeavingHut.handleEvent(&e);
						destroy_AV_WeavingHut.render();			destroy_AV_WeavingHut.handleEvent(&e);

						build_NAV_ToolSmith.render();			build_NAV_ToolSmith.handleEvent(&e);
						destroy_NAV_ToolSmith.render();			destroy_NAV_ToolSmith.handleEvent(&e);

						build_NAV_WindMill.render();			build_NAV_WindMill.handleEvent(&e);
						destroy_NAV_WindMill.render();			destroy_NAV_WindMill.handleEvent(&e);

						break;
						// Ekran rozgrywki - produkcja
					case PROD:
						back_button.setPosition(300, 732);
						back_button.render();
						back_button.handleEvent(&e);
						SDL_RenderSetViewport(gRenderer, &RightViewport);
						SDL_RenderCopy(gRenderer, gTexture2, NULL, NULL);
				
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC
						gTextTexture.loadFromRenderedText(_itoa(chatka_drwala, People_char_buffor, 10), textC);
						gTextTexture.render(53, 228);
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC

						// Obiekty przyciskow
						// RENDER								// HANDLE_EVENT
						build_AV_ForestersLodge.render();		build_AV_ForestersLodge.handleEvent(&e);
						destroy_AV_ForestersLodge.render();		destroy_AV_ForestersLodge.handleEvent(&e);

						build_NAV_CottonPlantation.render();	build_NAV_CottonPlantation.handleEvent(&e);
						destroy_NAV_CottonPlantation.render();	destroy_NAV_CottonPlantation.handleEvent(&e);

						build_NAV_GrainFarm.render();			build_NAV_GrainFarm.handleEvent(&e);
						destroy_NAV_GrainFarm.render();			destroy_NAV_GrainFarm.handleEvent(&e);

						build_NAV_SpiceFarm.render();			build_NAV_SpiceFarm.handleEvent(&e);
						destroy_NAV_SpiceFarm.render();			destroy_NAV_SpiceFarm.handleEvent(&e);

						build_AV_HuntersHut.render();			build_AV_HuntersHut.handleEvent(&e);
						destroy_AV_HuntersHut.render();			destroy_AV_HuntersHut.handleEvent(&e);

						build_NAV_CocoaPlantation.render();		build_NAV_CocoaPlantation.handleEvent(&e);
						destroy_NAV_CocoaPlantation.render();	destroy_NAV_CocoaPlantation.handleEvent(&e);

						build_NAV_CattleFarm.render();			build_NAV_CattleFarm.handleEvent(&e);
						destroy_NAV_CattleFarm.render();		destroy_NAV_CattleFarm.handleEvent(&e);

						build_AV_SheepFarm.render();			build_AV_SheepFarm.handleEvent(&e);
						destroy_AV_SheepFarm.render();			destroy_AV_SheepFarm.handleEvent(&e);

						build_NAV_Winery.render();				build_NAV_Winery.handleEvent(&e);
						destroy_NAV_Winery.render();			destroy_NAV_Winery.handleEvent(&e);
						// RENDER								// HANDLE_EVENT
						build_NAV_TobaccoPlantation.render();	build_NAV_TobaccoPlantation.handleEvent(&e);
						destroy_NAV_TobaccoPlantation.render();	destroy_NAV_TobaccoPlantation.handleEvent(&e);

						build_NAV_SugarcanePlantation.render();	build_NAV_SugarcanePlantation.handleEvent(&e);
						destroy_NAV_SugarcanePlantation.render(); destroy_NAV_SugarcanePlantation.handleEvent(&e);

						build_NAV_IronMine.render();			build_NAV_IronMine.handleEvent(&e);
						destroy_NAV_IronMine.render();			destroy_NAV_IronMine.handleEvent(&e);

						build_NAV_DeepIronMine.render();		build_NAV_DeepIronMine.handleEvent(&e);
						destroy_NAV_DeepIronMine.render();		destroy_NAV_DeepIronMine.handleEvent(&e);

						build_NAV_GoldMine.render();			build_NAV_GoldMine.handleEvent(&e);
						destroy_NAV_GoldMine.render();			destroy_NAV_GoldMine.handleEvent(&e);

						build_AV_FishersHut.render();			build_AV_FishersHut.handleEvent(&e);
						destroy_AV_FishersHut.render();			destroy_AV_FishersHut.handleEvent(&e);


						break;
					}
					break;
				case QUIT:
					quit = true;
					break;
				}
				// Odswiezenie ekranu
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	// getch do testowania
	//_getch();
	// Zwalnianie zasob�w i zamykanie SDL
	close();
	return 0;
}
