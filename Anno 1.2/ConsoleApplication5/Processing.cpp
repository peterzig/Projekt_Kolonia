#include "stdafx.h"
#include "Processing.h"

Processing::Processing()
{
}

Processing::Processing(int _moneyToBuild, int _bricksToBuild, int _toolsToBuild, int _woodToBuild, int _maintenanceActiveCost, 
	int _maintenancePassiveCost, int _magazineCapacity, int _peopleToBuild, int _peopleClass)
{
	moneyToBuild = _moneyToBuild;
	bricksToBuild = _bricksToBuild;
	toolsToBuild = _toolsToBuild;
	woodToBuild = _woodToBuild;
	maintenanceActiveCost = _maintenanceActiveCost;
	maintenancePassiveCost = _maintenancePassiveCost;
	magazineCapacity = _magazineCapacity;
	peopleToBuild = _peopleToBuild;
	peopleClass = _peopleClass;
}

Processing::~Processing()
{
}