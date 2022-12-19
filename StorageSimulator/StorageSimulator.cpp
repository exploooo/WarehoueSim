#include <iostream>
#include <typeinfo>
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

// A parent abstract Cargo object
// TBDIF
// Future inheritance to distinct Cargo Types
class Cargo {
public:

    virtual void showContent() = 0;

};

class EmptyCargoSpace : public Cargo {
private:
    string ContentDescription = "Empty Space";

public:

    virtual void showContent() {
        cout << ContentDescription << endl;
    }

};

class FoodCargo : public Cargo {
private:
    string ContentDescription = "Food";

public:

    virtual void showContent() {
        cout << ContentDescription << endl;
    }
};

// TBDIF
// A storage Unit inside of a Rack
class Unit {
private:
    // Array
    int CargoArraySize;
    Cargo** CargoArray;

public:

    // Displays All cargo in this Unit
    void displayCargo() {
        for (int i = 0; i < CargoArraySize; i++) {
            cout << "Place no." << i << ":";
            CargoArray[i]->showContent();
        }
    }

    // Places Cargo box in specified place in this Unit
    void placeCargo(int index, Cargo* cargoToBePlaced) {
        delete CargoArray[index];
        CargoArray[index] = cargoToBePlaced;
    }

    // Displays Cargo Array Size
    void displayArrSize() {
        cout << CargoArraySize;
    }

    // Constructor with empty array
    Unit(int cargoArraySize) : CargoArraySize(cargoArraySize)
    {
        CargoArray = new Cargo*[CargoArraySize];
        for (int i = 0; i < CargoArraySize; i++) {
            CargoArray[i] = new EmptyCargoSpace;
        }
    };

    //Constructor without an array - Default Constructor
    Unit()
    {
        CargoArray = nullptr;
        CargoArraySize = 0;
    };

    ~Unit(){
        // Need to check if Array content is dynamically allocated in this case i use only Empty Spaces as dynamically assigned valu
        Cargo* tempEmptySpace = new EmptyCargoSpace;
        const type_info& EMPTY_SPACE_TYPE = typeid(*tempEmptySpace);

        delete tempEmptySpace;

        for (int i = 0; i < CargoArraySize; i++) {
            if (typeid(*CargoArray[i]) == EMPTY_SPACE_TYPE) {
                delete CargoArray[i];
            }
        }
        delete[] CargoArray;
    }

private:
    int UnitCount = 0;
};

// TBDIF
// A class that represents a basic Rack
class Rack {
private:
    string RackID;
    int MaxUnits; 

public:

    friend ostream& operator<<(ostream& os, Rack item);
    friend bool operator==(Rack a, Rack b);
    friend bool operator==(Rack a, string str);

    //Default Constructor
    Rack()
    {};

    Rack(string rackID, int maxUnits) : RackID(rackID), MaxUnits(maxUnits)
    {};

protected:
    int UnitsCount = 0;
};


// A class that represents as you guessed it.. a standard 3D Warehouse building
class Warehouse {
private:
    // Basic Wareshouse structural dimensions
    float Length;
    float Height;
    float Width;

    // Warehouse's Racks
    int RackArrSize;
    Rack* Racks;

public:

    // Calculates space of a Warehouse in m^3
    float calculateSpace() {
        return Length * Width * Height;
    }

    // Asks for adding more rack space in case of depleating - Returns 1 if a Rack space is meant to be added and 0 if not
    bool askForMoreRackSpace() {
        const string choiceUnresolved = "Choice unresolved! Next time give an Y/N answer";
        char choice;
        cout << "Rack Spaces depleated! Add another one? (Y/N): ";
        cin >> choice;
        
        if (cin.fail()) {

            cin.clear();
            cin.ignore();
            cout << choiceUnresolved << endl;

        } else if (choice == 'Y') {

            int rackSpacesToAdd;
            cout << "How many Rack's slots?: ";
            cin >> rackSpacesToAdd;

            addMoreRackSpace(rackSpacesToAdd);

            return 1;

        } else if (choice == 'N') {

            cout << "Rack not added" << endl;

        } else {

            cout << choiceUnresolved << endl;

        }
        return 0;
    }
    
    // Returns dynamical value of Racks Array
    void displayAvaiableRackSpace() {
        cout << "Avaiable Rack Space: " << RackArrSize-RackCounter << endl;
    }

    // Dynamically extends Rack Table
    void addMoreRackSpace(int rackSpaceToAdd) {

        int newSize = RackArrSize + rackSpaceToAdd;

        if (Racks != nullptr) {

            Rack* tempRacks = new Rack[newSize];

            for (int i = 0; i < RackArrSize; i++) {
                tempRacks[i] = Racks[i]; 
            }

            delete[] Racks;

            Racks = new Rack[newSize];

            for (int i = 0; i < RackArrSize; i++) {
                Racks[i] = tempRacks[i];
            }

            delete[] tempRacks;

        } else {
            Racks = new Rack[newSize];
        }

        RackArrSize = newSize;
    }

    // Adds a new rack shelf to the warehouse
    void addRack(Rack rackToBeAdded) {
        if (RackCounter < RackArrSize) {
            Racks[RackCounter] = rackToBeAdded;
            RackCounter++;
        } else {
            if (askForMoreRackSpace()) {
                Racks[RackCounter] = rackToBeAdded;
                RackCounter++;
            }
        }
    }

    // Removes selected Rack shelf
    void removeRack(Rack rackToBeDeleted) {
        for (int i = 0; i < RackArrSize; i++) {
            if (rackToBeDeleted == Racks[i]) {
                Racks[i] = Rack();
                updateRacks(); // Updates Racks so the empty ones go to the end of the array
                break;
            }
        }
    }

    // Removes last Rack shelf
    void removeLastRack() {
        if (RackCounter > 0) {
            Racks[RackCounter - 1] = Rack();
            RackCounter--;
        }
        else {
            cout << "Rack Array is already empty! Cannot delete non-existent object!" << endl;
        }
    }

    // Updates Rack Integrity - Empty Racks should be at the end of the array
    void updateRacks() {
        for (int i = 0; i < RackCounter; i++) {
            if (Racks[i] == "") {
                Racks[i] = Racks[RackCounter-1];
                Racks[RackCounter-1] = Rack();
                RackCounter--;
            }
        }
    }

    // Displays all Racks in Warehouse
    void displayRacks() {
        cout << "Racks: ";
        for (int i = 0; i < RackCounter; i++) {
            if (i != RackCounter - 1) {
                cout << Racks[i] << ", ";
            } else {
                cout << Racks[i] << endl;
            }
        }
    }

    // Creates a 3D square'ish storage compartment with Racks allready
    Warehouse(float length, float width, float height, int rackArrSize) : Length(length), Width(width), Height(height), RackArrSize(rackArrSize)
    {
        Racks = new Rack[rackArrSize];
    };

    // Creates a 3D square'ish storage compartment without Racks
    Warehouse(float length, float width, float height) : Length(length), Width(width), Height(height)
    {
        Racks = nullptr;
        RackArrSize = 0;
    };

    // Destructor that also deletes dynamicly allocated memory *CRUCIAL DO NOT DELETE* - helps avoid memory leak 
    ~Warehouse() {
        delete [] Racks;
    }

protected:
    int RackCounter=0;
};

ostream& operator<<(ostream& os, Rack item) {
    os << item.RackID;
    return os;
}

bool operator==(Rack a, Rack b) {
    if (a.RackID == b.RackID) {
        return true;
    } else {
        return false;
    }
}
bool operator==(Rack a, string str) {
    if (a.RackID == str) {
        return true;
    } else {
        return false;
    }
}

int main()
{
    // Main is used mainly for tests at the moment

    const int size = 10;

    Unit unit_a = Unit(size);

    FoodCargo carrots = FoodCargo();

    for (int i = 0; i < size/2; i++) {
        unit_a.placeCargo(i, &carrots);
    }

    unit_a.displayCargo();

    return 0;
}

