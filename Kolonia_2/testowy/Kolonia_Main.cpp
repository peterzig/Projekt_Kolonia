#include "SDL_Headers.h"


#include "SDL_Functions.h"
#include "SDL_Button.h"
#include "SDL_Enums.h"
#include "SDL_G_Const.h"
#include "SDL_G_Var.h"
#include "SDL_Textur.h"
#include "SDL_Timer.h"
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
			SDL_Button new_game_button(NEW_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 624, 400, "new.png");
			SDL_Button continue_button(CONTINUE_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 624, 350, "continue.png");
			SDL_Button load_game_button(LOAD_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 624, 480, "load.png");
			SDL_Button exit_game_button(EXIT_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 624, 660, "exit.png");
			SDL_Button main_menu_button(MAIN_MENU, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 624, 660, "menu.png");
			SDL_Button save_game_button(SAVE_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 150, 732, "save.png");
			SDL_Button back_button(CONTINUE_GAME, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 300, 732, "back.png");
			SDL_Button stats_button(VIEW_STATS, MAIN_BUTTON_WIDTH, MAIN_BUTTON_HEIGHT, 5, 732, "stats.png");

			// Przyciski splashy
			SDL_Button ind_button(INDUSTRIAL, BUILDINGS_BUTTON_WIDTH, BUILDINGS_BUTTON_HEIGHT, 0, 0, "/buildings/ind.png");
			SDL_Button prod_button(PRODUCTION, BUILDINGS_BUTTON_WIDTH, BUILDINGS_BUTTON_HEIGHT, 0, 256, "/buildings/prod.png");
			SDL_Button pub_button(PUBLIC, BUILDINGS_BUTTON_WIDTH, BUILDINGS_BUTTON_HEIGHT, 0, 512, "/buildings/pub.png");


			// Przyciski: kup, sprzedaj
			SDL_Button buy_button(BUY, BUY_BUTTON_WIDTH, BUY_BUTTON_HEIGHT, 335, 250, "buy.png");
			SDL_Button sell_button(SELL, BUY_BUTTON_WIDTH, BUY_BUTTON_HEIGHT, 335, 345, "sell.png");
			SDL_Button cancel_NAV_button(NONE, BUY_BUTTON_WIDTH, BUY_BUTTON_HEIGHT, 335, 440, "cancel_nav.png");
			SDL_Button cancel_AV_button(CANCEL, BUY_BUTTON_WIDTH, BUY_BUTTON_HEIGHT, 335, 440, "cancel_av.png");

			// Przyciski kupowania zasobow
			// przycisk(id, akcja, szerokosc, wysokosc, poz_x, poz_y, nazwa_pliku)
			SDL_Button buy_iron_ore_button(1, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 244, "/resources/iron_ore.png");
			SDL_Button buy_gold_button(2, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 244, "/resources/gold.png");
			SDL_Button buy_cottom_button(3, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 244, "/resources/cottom.png");
			SDL_Button buy_sugarcane_button(4, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 244, "/resources/sugarcane.png");
			SDL_Button buy_food_button(10, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 244, "/resources/food.png");

			SDL_Button buy_tobacco_button(5, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 318, "/resources/tobacco.png");
			SDL_Button buy_cattle_button(6, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 318, "/resources/cattle.png");
			SDL_Button buy_grain_button(7, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 318, "/resources/grain.png");
			SDL_Button buy_flour_button(8, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 318, "/resources/flour.png");
			SDL_Button buy_alcohol_button(14, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 318, "/resources/alcohol.png");

			SDL_Button buy_spices_button(12, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 387, "/resources/spices.png");
			SDL_Button buy_textiles_button(15, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 387, "/resources/textiles.png");
			SDL_Button buy_clothes_button(16, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 387, "/resources/clothes.png");
			SDL_Button buy_cigarettes_button(11, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 387, "/resources/cigarettes.png");
			SDL_Button buy_jewelry_button(17, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 387, "/resources/jewelry.png");

			SDL_Button buy_tools_button(18, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 456, "/resources/tools.png");
			SDL_Button buy_wood_button(19, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 456, "/resources/wood.png");
			SDL_Button buy_bricks_button(20, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 456, "/resources/bricks.png");
			SDL_Button buy_iron_button(9, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 456, "/resources/iron.png");
			SDL_Button buy_cocoa_button(13, BUY_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 456, "/resources/cocoa.png");

			// Przyciski sprzedazy zasobow
			// przycisk(id, akcja, szerokosc, wysokosc, poz_x, poz_y, nazwa_pliku)
			SDL_Button sell_iron_ore_button(1, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 244, "/resources/iron_ore.png");
			SDL_Button sell_gold_button(2, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 244, "/resources/gold.png");
			SDL_Button sell_cottom_button(3, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 244, "/resources/cottom.png");
			SDL_Button sell_sugarcane_button(4, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 244, "/resources/sugarcane.png");
			SDL_Button sell_food_button(10, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 244, "/resources/food.png");

			SDL_Button sell_tobacco_button(5, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 318, "/resources/tobacco.png");
			SDL_Button sell_cattle_button(6, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 318, "/resources/cattle.png");
			SDL_Button sell_grain_button(7, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 318, "/resources/grain.png");
			SDL_Button sell_flour_button(8, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 318, "/resources/flour.png");
			SDL_Button sell_alcohol_button(14, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 318, "/resources/alcohol.png");

			SDL_Button sell_spices_button(12, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 387, "/resources/spices.png");
			SDL_Button sell_textiles_button(15, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 387, "/resources/textiles.png");
			SDL_Button sell_clothes_button(16, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 387, "/resources/clothes.png");
			SDL_Button sell_cigarettes_button(11, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 387, "/resources/cigarettes.png");
			SDL_Button sell_jewelry_button(17, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 387, "/resources/jewelry.png");

			SDL_Button sell_tools_button(18, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 5, 456, "/resources/tools.png");
			SDL_Button sell_wood_button(19, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 70, 456, "/resources/wood.png");
			SDL_Button sell_bricks_button(20, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 135, 456, "/resources/bricks.png");
			SDL_Button sell_iron_button(9, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 199, 456, "/resources/iron.png");
			SDL_Button sell_cocoa_button(13, SELL_RESOURCE, RESOURCES_BUTTON_WIDTH, RESOURCES_BUTTON_HEIGHT, 263, 456, "/resources/cocoa.png");

			// Przyciski Buduj i Zburz
			// przycisk(id, akcja, szerokosc, wysokosc, poz_x, poz_y, nazwa_pliku)

			// Production
			// CottonPlantation
			SDL_Button build_NAV_CottonPlantation(19, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_3, "build_nav.png");
			SDL_Button destroy_NAV_CottonPlantation(19, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_3, "destroy_nav.png");
			SDL_Button build_AV_CottonPlantation(19, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_3, "build_av.png");
			SDL_Button destroy_AV_CottonPlantation(19, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_3, "destroy_av.png");
			// ForestersLodge
			SDL_Button build_AV_ForestersLodge(20, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_av.png");
			SDL_Button destroy_AV_ForestersLodge(20, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_av.png");
			// GrainFarm
			SDL_Button build_NAV_GrainFarm(21, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_nav.png");
			SDL_Button destroy_NAV_GrainFarm(21, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_GrainFarm(21, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_av.png");
			SDL_Button destroy_AV_GrainFarm(21, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_av.png");
			// SpiceFarm
			SDL_Button build_NAV_SpiceFarm(22, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_nav.png");
			SDL_Button destroy_NAV_SpiceFarm(22, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_SpiceFarm(22, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_av.png");
			SDL_Button destroy_AV_SpiceFarm(22, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_av.png");
			// HuntersHut
			SDL_Button build_NAV_HuntersHut(23, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_nav.png");
			SDL_Button destroy_NAV_HuntersHut(23, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_HuntersHut(23, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_av.png");
			SDL_Button destroy_AV_HuntersHut(23, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_av.png");
			// CocoaPlantation
			SDL_Button build_NAV_CocoaPlantation(24, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_3, "build_nav.png");
			SDL_Button destroy_NAV_CocoaPlantation(24, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_3, "destroy_nav.png");
			SDL_Button build_AV_CocoaPlantation(24, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_3, "build_av.png");
			SDL_Button destroy_AV_CocoaPlantation(24, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_3, "destroy_av.png");
			// CattleFarm
			SDL_Button build_NAV_CattleFarm(25, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_nav.png");
			SDL_Button destroy_NAV_CattleFarm(25, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_CattleFarm(25, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_av.png");
			SDL_Button destroy_AV_CattleFarm(25, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_av.png");
			// SheepFarm
			SDL_Button build_NAV_SheepFarm(26, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_nav.png");
			SDL_Button destroy_NAV_SheepFarm(26, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_SheepFarm(26, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_av.png");
			SDL_Button destroy_AV_SheepFarm(26, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_av.png");
			// Winery
			SDL_Button build_NAV_Winery(27, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_nav.png");
			SDL_Button destroy_NAV_Winery(27, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_Winery(27, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_av.png");
			SDL_Button destroy_AV_Winery(27, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_av.png");
			// TobaccoPlantation
			SDL_Button build_NAV_TobaccoPlantation(28, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_nav.png");
			SDL_Button destroy_NAV_TobaccoPlantation(28, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_TobaccoPlantation(28, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_av.png");
			SDL_Button destroy_AV_TobaccoPlantation(28, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_av.png");
			// SugarcanePlantation
			SDL_Button build_NAV_SugarcanePlantation(29, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_nav.png");
			SDL_Button destroy_NAV_SugarcanePlantation(29, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_SugarcanePlantation(29, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_av.png");
			SDL_Button destroy_AV_SugarcanePlantation(29, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_av.png");
			// IronMine
			SDL_Button build_NAV_IronMine(30, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_3, "build_nav.png");
			SDL_Button destroy_NAV_IronMine(30, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_3, "destroy_nav.png");
			SDL_Button build_AV_IronMine(30, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_3, "build_av.png");
			SDL_Button destroy_AV_IronMine(30, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_3, "destroy_av.png");
			// DeepIronMine
			SDL_Button build_NAV_DeepIronMine(31, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_3, "build_nav.png");
			SDL_Button destroy_NAV_DeepIronMine(31, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_3, "destroy_nav.png");
			SDL_Button build_AV_DeepIronMine(31, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_3, "build_av.png");
			SDL_Button destroy_AV_DeepIronMine(31, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_3, "destroy_av.png");
			// GoldMine
			SDL_Button build_NAV_GoldMine(32, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_3, "build_nav.png");
			SDL_Button destroy_NAV_GoldMine(32, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_3, "destroy_nav.png");
			SDL_Button build_AV_GoldMine(32, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_3, "build_av.png");
			SDL_Button destroy_AV_GoldMine(32, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_3, "destroy_av.png");
			// FishersHut
			SDL_Button build_NAV_FishersHut(33, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_nav.png");
			SDL_Button destroy_NAV_FishersHut(33, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_FishersHut(33, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_av.png");
			SDL_Button destroy_AV_FishersHut(33, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_av.png");

			// Processing
			// Bakery
			SDL_Button build_NAV_Bakery(34, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_nav.png");
			SDL_Button destroy_NAV_Bakery(34, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_Bakery(34, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_av.png");
			SDL_Button destroy_AV_Bakery(34, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_av.png");
			// OreRafinery
			SDL_Button build_NAV_OreRafinery(35, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_nav.png");
			SDL_Button destroy_NAV_OreRafinery(35, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_OreRafinery(35, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_av.png");
			SDL_Button destroy_AV_OreRafinery(35, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_av.png");
			// GoldSmith
			SDL_Button build_NAV_GoldSmith(36, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_3, "build_nav.png");
			SDL_Button destroy_NAV_GoldSmith(36, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_3, "destroy_nav.png");
			SDL_Button build_AV_GoldSmith(36, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_3, "build_av.png");
			SDL_Button destroy_AV_GoldSmith(36, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_3, "destroy_av.png");
			// ButchersShop
			SDL_Button build_NAV_ButchersShop(37, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_nav.png");
			SDL_Button destroy_NAV_ButchersShop(37, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_ButchersShop(37, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_av.png");
			SDL_Button destroy_AV_ButchersShop(37, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_av.png");
			// RumDistillery
			SDL_Button build_NAV_RumDistillery(38, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_nav.png");
			SDL_Button destroy_NAV_RumDistillery(38, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_RumDistillery(38, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_av.png");
			SDL_Button destroy_AV_RumDistillery(38, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_av.png");
			// Clothiers
			SDL_Button build_NAV_Clothiers(39, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_3, "build_nav.png");
			SDL_Button destroy_NAV_Clothiers(39, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_3, "destroy_nav.png");
			SDL_Button build_AV_Clothiers(39, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_3, "build_av.png");
			SDL_Button destroy_AV_Clothiers(39, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_3, "destroy_av.png");
			// StoneMason
			SDL_Button build_NAV_StoneMason(40, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_nav.png");
			SDL_Button destroy_NAV_StoneMason(40, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_StoneMason(40, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_av.png");
			SDL_Button destroy_AV_StoneMason(40, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_av.png");
			// TobaccoProduction
			SDL_Button build_NAV_TobaccoProduction(41, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_nav.png");
			SDL_Button destroy_NAV_TobaccoProduction(41, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_TobaccoProduction(41, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_av.png");
			SDL_Button destroy_AV_TobaccoProduction(41, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_av.png");
			// WeavingMill
			SDL_Button build_NAV_WeavingMill(42, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_nav.png");
			SDL_Button destroy_NAV_WeavingMill(42, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_WeavingMill(42, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_av.png");
			SDL_Button destroy_AV_WeavingMill(42, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_av.png");
			// WeavingHut
			SDL_Button build_NAV_WeavingHut(43, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_nav.png");
			SDL_Button destroy_NAV_WeavingHut(43, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_WeavingHut(43, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_av.png");
			SDL_Button destroy_AV_WeavingHut(43, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_av.png");
			// ToolSmith
			SDL_Button build_NAV_ToolSmith(44, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_nav.png");
			SDL_Button destroy_NAV_ToolSmith(44, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_ToolSmith(44, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_av.png");
			SDL_Button destroy_AV_ToolSmith(44, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_av.png");
			// WindMill
			SDL_Button build_NAV_WindMill(45, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_nav.png");
			SDL_Button destroy_NAV_WindMill(45, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_WindMill(45, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_av.png");
			SDL_Button destroy_AV_WindMill(45, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_av.png");

			// Industrial
			// Doctor
			SDL_Button build_NAV_Doctor(2, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_nav.png");
			SDL_Button destroy_NAV_Doctor(2, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_Doctor(2, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_2, "build_av.png");
			SDL_Button destroy_AV_Doctor(2, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_2, "destroy_av.png");
			// PublicBath
			SDL_Button build_NAV_PublicBath(3, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_nav.png");
			SDL_Button destroy_NAV_PublicBath(3, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_PublicBath(3, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_2, "build_av.png");
			SDL_Button destroy_AV_PublicBath(3, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_2, "destroy_av.png");
			// FireDepartment
			SDL_Button build_NAV_FireDepartment(4, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_nav.png");
			SDL_Button destroy_NAV_FireDepartment(4, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_FireDepartment(4, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_1, "build_av.png");
			SDL_Button destroy_AV_FireDepartment(4, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_av.png");
			// Gallows pojbalo?
			// University
			SDL_Button build_NAV_University(6, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_nav.png");
			SDL_Button destroy_NAV_University(6, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_University(6, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4, W_2, "build_av.png");
			SDL_Button destroy_AV_University(6, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_2, "destroy_av.png");
			// Chapel
			SDL_Button build_NAV_Chapel(7, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_nav.png");
			SDL_Button destroy_NAV_Chapel(7, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_Chapel(7, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_av.png");
			SDL_Button destroy_AV_Chapel(7, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_av.png");
			// Church
			SDL_Button build_NAV_Church(8, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_nav.png");
			SDL_Button destroy_NAV_Church(8, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_Church(8, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_av.png");
			SDL_Button destroy_AV_Church(8, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_av.png");
			// MarketPlace
			SDL_Button build_NAV_MarketPlace(10, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_nav.png");
			SDL_Button destroy_NAV_MarketPlace(10, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_MarketPlace(10, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_av.png");
			SDL_Button destroy_AV_MarketPlace(10, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_av.png");
			// Palace
			SDL_Button build_NAV_Palace(11, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_nav.png");
			SDL_Button destroy_NAV_Palace(11, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_Palace(11, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_2, "build_av.png");
			SDL_Button destroy_AV_Palace(11, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_2, "destroy_av.png");
			// School
			SDL_Button build_NAV_School(12, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_nav.png");
			SDL_Button destroy_NAV_School(12, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_School(12, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5, W_1, "build_av.png");
			SDL_Button destroy_AV_School(12, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_av.png");
			// Theatre
			SDL_Button build_NAV_Theatre(13, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_nav.png");
			SDL_Button destroy_NAV_Theatre(13, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_nav.png");
			SDL_Button build_AV_Theatre(13, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_2, "build_av.png");
			SDL_Button destroy_AV_Theatre(13, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_2, "destroy_av.png");
			// Tavern
			SDL_Button build_NAV_Tavern(14, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_nav.png");
			SDL_Button destroy_NAV_Tavern(14, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_Tavern(14, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_av.png");
			SDL_Button destroy_AV_Tavern(14, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_av.png");

			// DOMY
			// Pionerzy
			SDL_Button build_NAV_House_L1(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_nav.png");
			SDL_Button destroy_NAV_House_L1(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_House_L1(666, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1, W_1, "build_av.png");
			SDL_Button destroy_AV_House_L1(666, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_1 + R_R, W_1, "destroy_av.png");
			// Osadnicy
			SDL_Button build_NAV_House_L2(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_nav.png");
			SDL_Button destroy_NAV_House_L2(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_House_L2(666, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2, W_1, "build_av.png");
			SDL_Button destroy_AV_House_L2(666, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_2 + R_R, W_1, "destroy_av.png");
			// Mieszczanie
			SDL_Button build_NAV_House_L3(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_nav.png");
			SDL_Button destroy_NAV_House_L3(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_nav.png");
			SDL_Button build_AV_House_L3(666, BUILD, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3, W_1, "build_av.png");
			SDL_Button destroy_AV_House_L3(666, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_3 + R_R, W_1, "destroy_av.png");
			// Kupcy
			SDL_Button destroy_NAV_House_L4(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_nav.png");
			SDL_Button destroy_AV_House_L4(666, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_4 + R_R, W_1, "destroy_av.png");
			// Arystokraci
			SDL_Button destroy_NAV_House_L5(666, NONE, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_nav.png");
			SDL_Button destroy_AV_House_L5(666, DESTROY, BUILD_BUTTON_WIDTH, BUILD_BUTTON_HEIGHT, C_5 + R_R, W_1, "destroy_av.png");

			// Pozwol budowac
			SDL_Button Allow_Build(666, ALLOW_BUILD, ALLOW_BUILD_BUTTON_WIDTH, ALLOW_BUILD_BUTTON_HEIGHT, A_B_X, A_B_Y, "allow_build.png");
			SDL_Button Deny_Build(666, DENY_BUILD, ALLOW_BUILD_BUTTON_WIDTH, ALLOW_BUILD_BUTTON_HEIGHT, A_B_X, A_B_Y, "deny_build.png");
			// Zabron budowac

			//  MAGAZYNY
			// WarehouseIIUpgrade
			SDL_Button upgrade_NAV_Warehouse(15, NONE, UPGRADE_BUTTON_WIDTH, UPGRADE_BUTTON_HEIGHT, U_X, U_Y, "upgrade_nav.png");
			SDL_Button upgrade_AV_Warehouse(15, UPGRADE, UPGRADE_BUTTON_WIDTH, UPGRADE_BUTTON_HEIGHT, U_X, U_Y, "upgrade_av.png");

			// Muzyka i info
			SDL_Button Music_On(CHANGE_MUSIC, 45, 37, 1315, 725, "music_on.png");
			SDL_Button Music_Off(CHANGE_MUSIC, 45, 37, 1315, 725, "music_off.png");



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

				///////////////////////////////////////////////////////////////////////////////////////// Do zmiany !!!!!!
				SDL_Rect fillRect = { 6, 295, 56, 5 };
				SDL_Rect fillRect2 = { 71, 295, 13, 5 };
					
				SDL_Rect fillRect4 = { 201, 295, 42, 5 };
				SDL_Rect fillRect5 = { 266, 295, 9, 5 };

				SDL_Rect fillRect6 = { 6, 369, 31, 5 };
				SDL_Rect fillRect7 = { 71, 369, 5, 5 };
				SDL_Rect fillRect8 = { 136, 369, 32, 5 };
				SDL_Rect fillRect9 = { 201, 369, 14, 5 };
				SDL_Rect fillRect10 = { 266, 369, 5, 5 };

				SDL_Rect fillRect11 = { 6, 437, 7, 5 };
				SDL_Rect fillRect12 = { 71, 437, 7, 5 };
				SDL_Rect fillRect13 = { 136, 437, 7, 5 };
				SDL_Rect fillRect14 = { 201, 437, 7, 5 };
				SDL_Rect fillRect15 = { 266, 437, 7, 5 };

				SDL_Rect fillRect16 = { 6, 507, 7, 5 };
				SDL_Rect fillRect17 = { 71, 507, 7, 5 };
				SDL_Rect fillRect18 = { 136, 507, 7, 5 };
				SDL_Rect fillRect19 = { 201, 507, 7, 5 };
				SDL_Rect fillRect20 = { 266, 507, 7, 5 };
				///////////////////////////////////////////////////////////////////////////////////////// Do zmiany !!!!!!

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
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC	!!!!!!!!!!!!!!!

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
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC	!!!!!!!!!!!!!!!

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
					// LVL1////////////////////////////////////////////////////////////////////////////////////////////////////// WWYWALIC (co� z tym zrobic) !!!!!!!!!!!
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

					////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC Zastapic  funkcja !!!!!!!!!!!
					/*
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
					*/
					////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC Zastapic  funkcja !!!!!!!!!!!


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

					////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC Beda funckje  !!!!!!!!!!!
					/*
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
					*/
					////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC Beda funckje  !!!!!!!!!!!

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
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC	!!!!!!!!!!!!!!!
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
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC	!!!!!!!!!!!!!!!

						SDL_RenderSetViewport(gRenderer, &RightViewport);
						SDL_RenderCopy(gRenderer, gTexture2, NULL, NULL);
						timer.render();

						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC  !!!!!!!!!!!!!!!
						/*
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
						*/
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC   !!!!!!!!!!!!!!!


						//gTextTexture.loadFromRenderedText("Zapisz", textC);
						//	gTextTexture.render(624, 200);

						// Pozwolenie i zakaz budowy
						if (allow_build == true)
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

						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC !!!!!!!!!!!!!!!
						/*
						gTextTexture.loadFromRenderedText(_itoa(chatka_drwala, People_char_buffor, 10), textC);
						gTextTexture.render(53, 228);
						*/
						//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// WYWALIC !!!!!!!!!!!!!!!!

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
