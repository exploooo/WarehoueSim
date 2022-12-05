#include <iostream>
using namespace std;

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

class Unit {
private:

public:
};

class Rack {
private:
    string RackID;

public:

    //Default Constructor
    Rack()
    {};

    Rack(string rackID, int unitsCount): RackID(rackID), UnitsCount(unitsCount)
    {};

protected:
    int UnitsCount = 0;
};

class Warehouse {
private:
    // Basic Wareshouse structural dimensions
    float Length;
    float Height;
    float Width;

    // Warehouse's Racks
    static const int MAX_NUMBER_OF_RACKS = 10;
    Rack Racks[MAX_NUMBER_OF_RACKS];

public:

    // Calculates space of a Warehouse in m^3
    float calculateSpace() {
        return Length * Width * Height;
    }
    
    // TBDIF - 10 for now
    // Calculates Available rack spots basing on space
    int calculateAvailableRackSpots(float space=0) {
        return MAX_NUMBER_OF_RACKS - RackCounter;
    }

    // Adds a new rack shelf to the warehouse
    void addRack(Rack rackToBeAdded) {
        Racks[RackCounter] = rackToBeAdded;
        RackCounter++;
    }

    // Removes selected Rack Shelf
    void removeRack(Rack rackToBeRemoved) {
        Racks[RackCounter] = Rack();
        RackCounter--;
    }

    // Creates a 3D square'ish storage compartment
    Warehouse(float length, float width, float height) : Length(length), Width(width), Height(height) 
    {};

protected:
    int RackCounter = 0;
};

int main()
{
    Rack rack_a = Rack("#A1", 10);
    Warehouse storage_a = Warehouse(110, 300, 12);

    cout << storage_a.calculateSpace() << endl;
    cout << storage_a.calculateAvailableRackSpots() << endl;
    
    storage_a.addRack(rack_a);

    cout << storage_a.calculateAvailableRackSpots() << endl;
}

