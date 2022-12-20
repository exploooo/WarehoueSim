#pragma once
#include <iostream>
#include "CargoTypes.h"

// TBDIF
// A storage Unit inside of a Rack

class Unit {
private:
    // Basic
    std::string UnitID;

    // Array
    int CargoArraySize;
    Cargo** CargoArray;

    // Prop Empty item - to contain first empty space place and type_info
    const Cargo* EMPTY_SPACE_OBJECT_PROP = new EmptyCargoSpace;
    const type_info& EMPTY_SPACE = typeid(*EMPTY_SPACE_OBJECT_PROP);
    int EMPTY_SPACE_INDEX;

public:

    // Return Index of Next empty item in Unit or -1 if Unit is full of Cargo
    int findEmptyItem() {
        for (int i = 0; i < CargoArraySize; i++) {
            if (typeid(*CargoArray[i]) == EMPTY_SPACE) {
                return i;
            }
        }
        return -1;
    }

    // Return Index of Last empty item in Unit or -1 if Unit is full of Cargo
    int findLastEmptyItem() {
        for (int i = CargoArraySize - 1; i > EMPTY_SPACE_INDEX; i--) {
            if (typeid(*CargoArray[i]) == EMPTY_SPACE) {
                return i;
            }
        }
        return -1;
    }

    int calculateFreeSpace() {
        int sum = 0;
        for (int i = 0; i < CargoArraySize; i++) {
            if (typeid(*CargoArray[i]) == EMPTY_SPACE) {
                sum++;
            }
        }
        return sum;
    }

    // Places Cargo box in specified place in this Unit
    void placeCargo(Cargo* cargoToBePlaced, int index) {
        // Protects from putting beyond Array range
        if (index >= CargoArraySize) {
            std::cout << "Error! Index value to high" << std::endl;
            return;
        }
        // Protects input from EmptySpace which is only dynamically declared object
        if (typeid(*cargoToBePlaced) == EMPTY_SPACE) {
            std::cout << "Error! Cannot Allocate static Empty Space item! Try with other type of cargo." << std::endl;
            return;
        }
        if (EMPTY_SPACE_INDEX == -1 || findEmptyItem() == -1) {
            std::cout << "Error! Unit space depleated!" << std::endl;
            return;
        }
        if (index == EMPTY_SPACE_INDEX) {
            EMPTY_SPACE_INDEX = findEmptyItem();
        }
        // Deletes previously dynamically allocated memory
        delete CargoArray[index];
        CargoArray[index] = cargoToBePlaced;
    }

    // Removes Cargo under specified index
    void removeCargo(int index) {
        if (typeid(*CargoArray[index]) == EMPTY_SPACE) {
            std::cout << "Error! Cannot Remove cargo from empty space" << std::endl;
            return;
        }
        CargoArray[index] = new EmptyCargoSpace;
        if (index < EMPTY_SPACE_INDEX) {
            EMPTY_SPACE_INDEX = index;
        }
    }

    //Empties Unit completely
    void removeAllCargo() {
        if (EMPTY_SPACE_INDEX == 0) {
            std::cout << "Cargo Array is already empty!" << std::endl;
            return;
        }
        for (int i = 0; i < CargoArraySize; i++) {
            if (typeid(*CargoArray[i]) != EMPTY_SPACE) {
                CargoArray[i] = new EmptyCargoSpace;
            }
        }
    }

    // Displays Cargo Array Size
    void displayArrSize() {
        std::cout << CargoArraySize;
    }

    // Displays ID And Array Size
    void displayInfo() {
        std::cout << "ID: " << UnitID << ", Capacity: " << CargoArraySize << std::endl;
    }

    // Displays how many free space is there left
    void displayFreeSpace() {
        std::cout << "Free Space: " << calculateFreeSpace() << "/" << CargoArraySize << std::endl;
    }

    // Displays All cargo in this Unit
    void displayCargo() {
        for (int i = 0; i < CargoArraySize; i++) {
            std::cout << "Place no." << i << ":";
            CargoArray[i]->showContent();
        }
    }

    // Displays ID, Array size and it's content
    void displayAll() {
        displayInfo();
        displayFreeSpace();
        std::cout << "-------------\n" << "Content: \n";
        displayCargo();
        std::cout << "-------------\n";
    }

    // Constructor with empty array
    Unit(std::string unitID, int cargoArraySize) : UnitID(unitID), CargoArraySize(cargoArraySize)
    {
        CargoArray = new Cargo * [CargoArraySize];
        for (int i = 0; i < CargoArraySize; i++) {
            CargoArray[i] = new EmptyCargoSpace;
        }
        EMPTY_SPACE_INDEX = 0;
    };

    //Constructor without an array - Default Constructor
    Unit()
    {
        CargoArray = nullptr;
        CargoArraySize = 0;
        EMPTY_SPACE_INDEX = 0;
    };

    ~Unit() {
        // Need to check if Array content is dynamically allocated in this case can be used only Empty Spaces as dynamically assigned value
        for (int i = 0; i < CargoArraySize; i++) {
            if (typeid(*CargoArray[i]) == EMPTY_SPACE) {
                delete CargoArray[i];
            }
        }
        delete[] CargoArray;
        delete EMPTY_SPACE_OBJECT_PROP;
    }

};