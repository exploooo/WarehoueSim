#include <iostream>
#include <typeinfo>
#include "CargoTypes.h"
#include "Units.h"
#include "ContainerShelf.h"
#include "Warehouse.h"

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Author: Mikołaj Sarnecki
// Date of creation: 3.12.2022
// Purpouse: creation of a virtual storage compartment and managing it (WAREHOUSE)
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Legend of comment keywords:
// ***
// TBDIF: To be done in future
// *** If you need to address some of the keyworded objects just search them with ctrl + f and correct
// Every object is to be correctly described using comments

// TO DO LIST:
// 1. Implement some basic objects recreating a simple warehouse
// 2. Read some kind of documentation how are actual warehouses created
// 3. Implement more complex Warehouse system
// 4. Divide code into separate header and cpp files
// 5. Call it v1.0
// Optional maybe learn pointers and do some magic
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int main()
{
    // Main is used mainly for tests at the moment

    const int size = 10;

    Unit unit_a = Unit("A1", size);

    FoodCargo carrots = FoodCargo();

    for (int i = 0; i < size/2; i++) {
        unit_a.placeCargo(&carrots, i);
    }

    unit_a.removeCargo(4);
    unit_a.displayAll();



    return 0;
}

