#include "sdl_functions.h"

STexture gTextTexture;
STexture gPromptTextTexture;

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
			printf("Ostrzezenie: Liniowe filtrowanie tekstury jest wylaczone!");

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
	// Tekstury magazynow
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
		if (!gTextTexture.loadFromRenderedText("12", textColor, gFont))
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

	// Zamyka systemy SDL'a
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
		std::cout << "Nie mozna wczytac obrazka: " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
	else
	{
		// Wczytuje teksture z powierzchni pikseli
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
			std::cout << "Nie mozna utworzyc tekstury z " << path.c_str() << "! SDL Error: " << path.c_str() << SDL_GetError() << std::endl;

		// Zwalnia stare powierzchnie
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}


bool Build_Pub(Public & Name,Resource *TResource[21])
{
	if (Name.getStatus() == false)
		return false;

	else if (usedFields + Name.getSize() > islandSize)
		return false;

	else if (Name.Build(TResource) == false)
		return false;
	else
	{
		usedFields += Name.getSize();
		return true;
	}
}

bool Destroy_Pub(Public & Name)
{
	if (Name.Destroy() == true)
	{
		usedFields -= Name.getSize();
		return true;
	}

	else
		return false;
}

bool Build_Proc(Processing & Name,Resource *TResource[21])
{
	if (Name.getStatus() == false)
		return false;

	else if (usedFields + Name.getSize() > islandSize)
		return false;

	else if (Name.Build(TResource) == false)
		return false;
	else
	{
		usedFields += Name.getSize();
		return true;
	}
}

bool Destroy_Proc(Processing & Name)
{
	if (Name.Destroy() == true)
	{
		usedFields -= Name.getSize();
		return true;
	}

	else
		return false;
}

bool Build_Prod(Production & Name,Resource *TResource[21])
{
	if (Name.getStatus() == false)
		return false;

	else if (usedFields + Name.getSize() > islandSize)
		return false;

	else if (Name.Build(TResource) == false)
		return false;
	else
	{
		usedFields += Name.getSize();
		return true;
	}
}

bool Destroy_Prod(Production & Name)
{
	if (Name.Destroy() == true)
	{
		usedFields -= Name.getSize();
		return true;
	}

	else
		return false;
}

bool Build_House(House & Name, Resource *TResource[21])
{
	if (Name.getStatus() == false)
		return false;

	else if (usedFields + Name.getSize() > islandSize)
		return false;

	else if (Name.Build(tResource) == false)
		return false;
	else
	{
		usedFields += Name.getSize();
		return true;
	}
}

bool Destroy_House(House & Name)
{
	if (Name.Destroy() == true)
	{
		usedFields -= Name.getSize();
		return true;
	}

	else
		return false;
}


void Fill_Arrays()
{
	// House(bricksToBuild, toolsToBuild, woodToBuild, inhabitants, startPeople, buildingID0, buildingID1, buildingID2)
	{ int tab0[1] = { -1 };
	tHouse[0] = new House(0, 0, 3, 3, 1, tab0, sizeof(tab0)); } 	/* Pioneers House */ { int tab1[2] = { 4, 7 };
	tHouse[1] = new House(0, 1, 3, 7, 2, tab1, sizeof(tab1)); }		/* Settlers House */ { int tab2[3] = { 2, 9, 11 };
	tHouse[2] = new House(6, 2, 2, 15, 3, tab2, sizeof(tab2)); } 	/* Citizens House */ { int tab3[3] = { 0, 1, 6 };
	tHouse[3] = new House(9, 3, 3, 25, 4, tab3, sizeof(tab3)); }	/* Merchansts House */ { int tab4[3] = { 3, 5, 10 };
	tHouse[4] = new House(12, 3, 3, 40, 5, tab4, sizeof(tab4)); }	/* Aristorcats House */

	// Public(goldToBuild, bricksToBuild, toolsToBuild, woodToBuild, maintenanceActiveCost, size, peopleToBuild, peopleClass)

	tPublic[0] = new Public(450, 9, 4, 4, 30, 4, 50, 2);			// Doctor
	tPublic[1] = new Public(1200, 19, 6, 5, 60, 12, 210, 2);		// Public Bath	
	tPublic[2] = new Public(150, 0, 3, 5, 15, 4, 15, 1);			// Fire Department
	tPublic[3] = new Public(750, 19, 6, 5, 60, 9, 250, 3);			// University
	tPublic[4] = new Public(100, 0, 2, 5, 5, 2, 40, 0);				// Chapel
	tPublic[5] = new Public(5000, 50, 15, 20, 40, 24, 1500, 3);		// Cathedral
	tPublic[6] = new Public(1600, 25, 7, 7, 50, 12, 150, 2);		// Church
	tPublic[7] = new Public(200, 0, 4, 10, 10, 12, 75, 0);			// Marketplace
	tPublic[8] = new Public(7500, 70, 25, 25, 90, 35, 2500, 4);		// Palace 
	tPublic[9] = new Public(450, 9, 4, 4, 30, 4, 100, 1);			// School
	tPublic[10] = new Public(1200, 19, 2, 5, 80, 9, 300, 3);		// Theatre
	tPublic[11] = new Public(250, 6, 3, 4, 15, 6, 50, 1);			// Tavern

																	// Production(moneyToBuild, bricksToBuild, toolsToBuild, woodToBuild, maintenanceActiveCost, maintenancePassiveCost, size, magazineCapacity, peopleToBuild, peopleClass, productID)

	tProduction[0] = new Production(200, 6, 2, 3, 25, 10, 16, 9, 200, 2, 3);		// Cotton Plantation		
	tProduction[1] = new Production(50, 0, 2, 0, 5, 0, 4, 10, 0, -1, 19);			// Foresters Lodge
	tProduction[2] = new Production(100, 0, 2, 5, 5, 0, 16, 6, 75, 1, 7);			// Grain Farm
	tProduction[3] = new Production(300, 8, 2, 3, 35, 15, 16, 4, 75, 1, 12);		// Spice Farm
	tProduction[4] = new Production(50, 0, 2, 2, 5, 0, 4, 3, 0, -1, 10);			// Hunters Hut
	tProduction[5] = new Production(300, 8, 2, 3, 35, 15, 16, 6, 200, 2, 13);		// Cocoa Plantation	
	tProduction[6] = new Production(100, 0, 1, 4, 5, 0, 16, 4, 30, 0, 6);			// Cattle Farm
	tProduction[7] = new Production(200, 0, 2, 4, 5, 0, 16, 8, 0, -1, 3);			// Sheep Farm
	tProduction[8] = new Production(300, 8, 2, 3, 35, 15, 16, 6, 40, 1, 14);		// Winery
	tProduction[9] = new Production(300, 8, 2, 3, 35, 15, 16, 6, 40, 1, 5);			// Tobacco Plantation
	tProduction[10] = new Production(300, 8, 2, 3, 25, 10, 16, 6, 40, 1, 4);		// Sugarcane Plantation
	tProduction[11] = new Production(1000, 5, 10, 20, 60, 20, 3, 4, 120, 1, 1);		// Iron Mine
	tProduction[12] = new Production(1800, 7, 15, 30, 60, 20, 3, 4, 450, 2, 1);		// Deep Iron Mine
	tProduction[13] = new Production(1000, 5, 10, 20, 60, 20, 3, 4, 150, 2, 2);		// Gold Mine
	tProduction[14] = new Production(100, 0, 3, 5, 5, 0, 1, 4, 0, -1, 10);			// Fisters Hut
	tProduction[15] = new Production(100, 0, 5, 5, 5, 0, 4, 8, 15, 1, 20);			// Stone Mason

																					// Processing(moneyToBuild, bricksToBuild, toolsToBuild, woodToBuild, maintenanceActiveCost, maintenancePassiveCost, magazineCapacity, peopleToBuild, peopleClass, productID, materialID, productNumber, materialNumber)

	tProcessing[0] = new Processing(150, 0, 2, 6, 5, 0, 4, 75, 1, 10, 8, 1, 2);			// Bakery
	tProcessing[1] = new Processing(200, 4, 3, 1, 25, 10, 5, 120, 1, 9, 1, 1, 1);		// Ore Refenery
	tProcessing[2] = new Processing(1500, 10, 7, 2, 45, 20, 4, 250, 3, 17, 2, 2, 1);	// Gold Smith
	tProcessing[3] = new Processing(150, 10, 3, 4, 5, 0, 4, 30, 0, 10, 6, 1, 2);		// Butcher Shop
	tProcessing[4] = new Processing(200, 5, 3, 2, 25, 7, 4, 40, 1, 14, 4, 1, 2);		// Rum Distillery
	tProcessing[5] = new Processing(150, 2, 3, 6, 10, 5, 4, 200, 2, 16, 15, 1, 1);		// Clothiers
	tProcessing[6] = new Processing(200, 5, 3, 2, 20, 10, 4, 40, 1, 11, 5, 1, 2);		// TobaccoProduction
	tProcessing[7] = new Processing(200, 7, 4, 3, 20, 10, 4, 75, 1, 15, 3, 1, 1);		// WeavingMill
	tProcessing[8] = new Processing(200, 0, 3, 6, 10, 5, 4, 0, -1, 15, 3, 1, 2);		// WeavingHut
	tProcessing[9] = new Processing(150, 5, 3, 2, 25, 10, 4, 100, 1, 18, 9, 2, 1);		// ToolSmithy
	tProcessing[10] = new Processing(100, 0, 3, 6, 5, 0, 6, 75, 1, 10, 7, 1, 2);		// WindMill

																						// People(tax)
	tPeople[0] = new People(1);		// Pioneers
	tPeople[1] = new People(1);		// Settlers
	tPeople[2] = new People(1);		// Citizens
	tPeople[3] = new People(2);		// Merchants
	tPeople[4] = new People(2);		// Aristocrats

									// Resource(price)
	tResource[0] = new Resource(1);			// Money
	tResource[1] = new Resource(60);		// Iron Ore
	tResource[2] = new Resource(465);		// Gold
	tResource[3] = new Resource(16);		// Wool
	tResource[4] = new Resource(19);		// Sugar
	tResource[5] = new Resource(23);		// Tobacco
	tResource[6] = new Resource(6);			// Cattle
	tResource[7] = new Resource(3);			// Grain
	tResource[8] = new Resource(3);			// Flour
	tResource[9] = new Resource(84);		// Iron
	tResource[10] = new Resource(17);		// Food
	tResource[11] = new Resource(65);		// Tobacco Products
	tResource[12] = new Resource(40);		// Spices
	tResource[13] = new Resource(33);		// Cocoa
	tResource[14] = new Resource(52);		// Liquor
	tResource[15] = new Resource(32);		// Cloth
	tResource[16] = new Resource(130);		// Clothes
	tResource[17] = new Resource(590);		// Jewerly
	tResource[18] = new Resource(80);		// Tools
	tResource[19] = new Resource(20);		// Wood
	tResource[20] = new Resource(30);		// Bricks

}


Uint32 Update_Prod(Uint32 interval, void* param)
{
	
	int i = reinterpret_cast<int>(param);
		totalResources += tResource[i]->getNumber();				// sumowanie liczby surowcow ktore posiada gracz
		if (tProduction[i]->getNumber() > maxBuildingNumber)		// wyszukiwanie zmiennej maxBuldingNumber
			maxBuildingNumber = tProduction[i]->getNumber();
		totalMagazinesCapacity += tProduction[i]->getMagazineCapacity() * tProduction[i]->getNumber();		// sumowanie calkowitej pojemnosci magazynow budynkow
		usedMagazine = totalResources - totalMagazinesCapacity;				// wykorzystanie magazynu glownego to dodatni wynik roznicy wszystkich surowcow od calkowitej pojemnosci wszystkich budynkow
		if (usedMagazine < 0) usedMagazine = 0;								// wynik ujemny tej roznicy oznacza, ze magazyn w ogole nie jest wykorzystywany

		for (int j = 1; j <= maxBuildingNumber; ++j)																								// dodawaj po jednej jednostce surowca tyle razy ile wynosi najwieksza liczba posiadanego budynku
				if (tProduction[i]->getMagazineCapacity() * tProduction[i]->getNumber() <= tResource[tProduction[i]->getProductID()]->getNumber())	// jezeli pojemnosc magazynu * liczba budynkow <= liczby posiadanych surowcow 
					if (tProduction[i]->getNumber() != 0)																							// oraz liczba budynkow jest != 0
						if (usedMagazine < WareHouse.getmagazineCapacity())																			// oraz dostepne jest jeszcze miejsce w magazynie glownym
							if (tProduction[i]->getNumber() >= j)																					// oraz mamy liczbe j budynkow aby moc dodaj j-ty surowiec
							{
								tResource[tProduction[i]->getProductID()]->increase(1);																// dodaj jedna jednostke surowca
								++usedMagazine;																										// zwieksz zajetosc magazynu
							}

		// ZAPELNIANIE MAGAZYNOW WEWNETRZNYCH BUDYNKOW DANEGO TYPU (w pierwszej kolejnosci)

			if (tProduction[i]->getMagazineCapacity() * tProduction[i]->getNumber() > tResource[tProduction[i]->getProductID()]->getNumber())		// jezeli pojemnosc magazynu * liczba budynkow > liczby posiadanych surowcow to
			{
				tResource[tProduction[i]->getProductID()]->increase(tProduction[i]->getNumber());													// zwieksz liczbe surowca o liczbe posiadanych budynkow (kazdy budynek Production zwieksza o 1 jednostke surowca)

				if (tProduction[i]->getMagazineCapacity() * tProduction[i]->getNumber() < tResource[tProduction[i]->getProductID()]->getNumber())	// jezeli po zwiekszeniu pojemnosc magazynu * liczba budynkow < liczby posiadanych surowcow to
				{
					int excess = tResource[tProduction[i]->getProductID()]->getNumber() - tProduction[i]->getMagazineCapacity() * tProduction[i]->getNumber();		// dodany nadmiar surowcow, ktory nie miesci sie w calkowitej pojemnosci magazynow danego typu budynku
					tResource[tProduction[i]->getProductID()]->decrease(excess);		// TU JESZCZE DOKONCZ	! CO TU MIALO BYC :D !								// poziom surowcow zmniejsz do max dostepnej pojemnosci
				}
			}

			// ZAPELNIANIE MAGAZYNU OGOLNEGO (w drugiej kolejnosci)

			usedMagazine = totalResources - totalMagazinesCapacity;				// wykorzystanie magazynu glownego to dodatni wynik roznicy wszystkich surowcow od calkowitej pojemnosci wszystkich budynkow
			if (usedMagazine < 0) usedMagazine = 0;								// wynik ujemny tej roznicy oznacza, ze magazyn w ogole nie jest wykorzystywany

			for (int j = 1; j <= maxBuildingNumber; ++j)																								// dodawaj po jednej jednostce surowca tyle razy ile wynosi najwieksza liczba posiadanego budynku
					if (tProduction[i]->getMagazineCapacity() * tProduction[i]->getNumber() <= tResource[tProduction[i]->getProductID()]->getNumber())	// jezeli pojemnosc magazynu * liczba budynkow <= liczby posiadanych surowcow 
						if (tProduction[i]->getNumber() != 0)																							// oraz liczba budynkow jest != 0
							if (usedMagazine < WareHouse.getmagazineCapacity())																			// oraz dostepne jest jeszcze miejsce w magazynie glownym
								if (tProduction[i]->getNumber() >= j)																					// oraz mamy liczbe j budynkow aby moc dodaj j-ty surowiec
								{
									tResource[tProduction[i]->getProductID()]->increase(1);																// dodaj jedna jednostke surowca
									++usedMagazine;																										// zwieksz zajetosc magazynu
								}
		if (tProduction[i]->getActiveNumber() < 5)
			return 5000;
		else 
			return 3000;
}

Uint32 Update_Proc(Uint32 interval, void* param)
{
	int i = reinterpret_cast<int>(param);
	if (tProcessing[i]->getMagazineCapacity() * tProcessing[i]->getNumber() > tResource[tProcessing[i]->getMaterialID()]->getNumber())	// jezeli pojemnosc magazynu * liczba budynkow > liczby posiadanych surowcow 
				if (tResource[tProcessing[i]->getMaterialID()]->getNumber() >= tProcessing[i]->getMaterialNumber())								// oraz posiadamy przynamniej tyle surowca ile potrzeba do przetwarzania na inny to
				{
					tResource[tProcessing[i]->getProductID()]->increase(tProcessing[i]->getProductNumber());									// dodaj liczbe surowca, ktory zostal wyprodukowany
					tResource[tProcessing[i]->getMaterialID()]->decrease(tProcessing[i]->getMaterialNumber());									// zmniejsz liczbe liczbe surowca, ktory zostal przetworzony
				}
	maxBuildingNumber = tProcessing[i]->getNumber();
	totalMagazinesCapacity += tProcessing[i]->getMagazineCapacity() * tProcessing[i]->getNumber();		// sumowanie calkowitej pojemnosci magazynow budynkow
	usedMagazine = totalResources - totalMagazinesCapacity;				// wykorzystanie magazynu glownego to dodatni wynik roznicy wszystkich surowcow od calkowitej pojemnosci wszystkich budynkow
	if (usedMagazine < 0) usedMagazine = 0;								// wynik ujemny tej roznicy oznacza, ze magazyn w ogole nie jest wykorzystywany

	for (int j = 1; j <= maxBuildingNumber; ++j)																								// dodawaj po jednej jednostce surowca tyle razy ile wynosi najwieksza liczba posiadanego budynku
			if (tProcessing[i]->getMagazineCapacity() * tProcessing[i]->getNumber() <= tResource[tProcessing[i]->getProductID()]->getNumber())	// jezeli pojemnosc magazynu * liczba budynkow <= liczby posiadanych surowcow 
				if (tProcessing[i]->getNumber() != 0)																							// oraz liczba budynkow jest != 0
					if (usedMagazine < WareHouse.getmagazineCapacity())																			// oraz dostepne jest jeszcze miejsce w magazynie glownym
						if (tProcessing[i]->getNumber() >= j)																					// oraz mamy liczbe j budynkow aby moc dodaj j-ty surowiec
						{
							tResource[tProcessing[i]->getProductID()]->increase(1);																// dodaj jedna jednostke surowca
							++usedMagazine;																										// zwieksz zajetosc magazynu
						}

	// ZAPELNIANIE MAGAZYNOW WEWNETRZNYCH BUDYNKOW DANEGO TYPU (w pierwszej kolejnosci)

	for (int i = 0; i < 15; ++i)
		if (tProcessing[i]->getMagazineCapacity() * tProcessing[i]->getNumber() > tResource[tProcessing[i]->getProductID()]->getNumber())		// jezeli pojemnosc magazynu * liczba budynkow > liczby posiadanych surowcow to
		{
			tResource[tProcessing[i]->getProductID()]->increase(tProcessing[i]->getNumber());													// zwieksz liczbe surowca o liczbe posiadanych budynkow (kazdy budynek Production zwieksza o 1 jednostke surowca)

			if (tProcessing[i]->getMagazineCapacity() * tProcessing[i]->getNumber() < tResource[tProcessing[i]->getProductID()]->getNumber())	// jezeli po zwiekszeniu pojemnosc magazynu * liczba budynkow < liczby posiadanych surowcow to
			{
				int excess = tResource[tProcessing[i]->getProductID()]->getNumber() - tProcessing[i]->getMagazineCapacity() * tProcessing[i]->getNumber();		// dodany nadmiar surowcow, ktory nie miesci sie w calkowitej pojemnosci magazynow danego typu budynku
				tResource[tProcessing[i]->getProductID()]->decrease(excess);		// TU JESZCZE DOKONCZ	! CO TU MIALO BYC :D !								// poziom surowcow zmniejsz do max dostepnej pojemnosci
			}
		}

	if (tProcessing[i]->getActiveNumber() < 5)
		return 7000;
	else
		return 3000;
}