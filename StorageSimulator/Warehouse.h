#pragma once
#include <iostream>
#include "ContainerShelf.h"

// A class that represents as you guessed it.. a standard 3D Warehouse building
class Warehouse {
private:
    // Basic Wareshouse structural dimensions
    float Length;
    float Height;
    float Width;

    // Warehouse's Container Shelves
    int ContainerShelfArrSize;
    ContainerShelf* ContainerShelfArr;

public:

    // Calculates space of a Warehouse in m^3
    float calculateSpace() {
        return Length * Width * Height;
    }

    // Asks for adding more Container Shelves in case of space depleating - Returns 1 if a Container Shelf is meant to be added and 0 if not
    bool askForMoreContainerShelfSpace() {
        const std::string choiceUnresolved = "Choice unresolved! Next time give an Y/N answer";
        char choice;
        std::cout << "Container Shelf Space depleated! Add another one? (Y/N): ";
        std::cin >> choice;

        if (std::cin.fail()) {

            std::cin.clear();
            std::cin.ignore();
            std::cout << choiceUnresolved << std::endl;

        }
        else if (choice == 'Y') {

            int containerShelfSpacesToAdd;
            std::cout << "How many Container Shelve slots?: ";
            std::cin >> containerShelfSpacesToAdd;

            addMoreContainerShelfSpace(containerShelfSpacesToAdd);

            return 1;

        }
        else if (choice == 'N') {

            std::cout << "Container Shelf not added" << std::endl;

        }
        else {

            std::cout << choiceUnresolved << std::endl;

        }
        return 0;
    }

    // Returns dynamical value of ContainerShelf Array
    void displayAvaiableContainerShelfSpace() {
        std::cout << "Avaiable ContainerShelf Space: " << ContainerShelfArrSize - ContainerShelfCounter << std::endl;
    }

    // Dynamically extends ContainerShelf Table
    void addMoreContainerShelfSpace(int ContainerShelfSpaceToAdd) {

        int newSize = ContainerShelfArrSize + ContainerShelfSpaceToAdd;

        if (ContainerShelfArr != nullptr) {

            ContainerShelf* tempContainerShelf = new ContainerShelf[newSize];

            for (int i = 0; i < ContainerShelfArrSize; i++) {
                tempContainerShelf[i] = ContainerShelfArr[i];
            }

            delete[] ContainerShelfArr;

            ContainerShelfArr = new ContainerShelf[newSize];

            for (int i = 0; i < ContainerShelfArrSize; i++) {
                ContainerShelfArr[i] = tempContainerShelf[i];
            }

            delete[] tempContainerShelf;

        }
        else {
            ContainerShelfArr = new ContainerShelf[newSize];
        }

        ContainerShelfArrSize = newSize;
    }

    // Adds a new Container Shelf to the warehouse
    void addContainerShelf(ContainerShelf containerShelfToBeAdded) {
        if (ContainerShelfCounter < ContainerShelfArrSize) {
            ContainerShelfArr[ContainerShelfCounter] = containerShelfToBeAdded;
            ContainerShelfCounter++;
        }
        else {
            if (askForMoreContainerShelfSpace()) {
                ContainerShelfArr[ContainerShelfCounter] = containerShelfToBeAdded;
                ContainerShelfCounter++;
            }
        }
    }

    // Removes selected Container Shelf
    void removeContainerShelf(ContainerShelf containerShelfToBeDeleted) {
        for (int i = 0; i < ContainerShelfArrSize; i++) {
            if (containerShelfToBeDeleted == ContainerShelfArr[i]) {
                ContainerShelfArr[i] = ContainerShelf();
                updateContainerShelves(); // Updates Container Shelves so the empty ones go to the end of the array
                break;
            }
        }
    }

    // Removes last Container Shelf
    void removeLastContainerShelf() {
        if (ContainerShelfCounter > 0) {
            ContainerShelfArr[ContainerShelfCounter - 1] = ContainerShelf();
            ContainerShelfCounter--;
        }
        else {
            std::cout << "Container Shelf is already empty! Cannot delete non-existent object!\n";
        }
    }

    // Updates Container Shelves Integrity - Empty Container Shelves should be at the end of the array
    void updateContainerShelves() {
        for (int i = 0; i < ContainerShelfCounter; i++) {
            if (ContainerShelfArr[i] == "") {
                ContainerShelfArr[i] = ContainerShelfArr[ContainerShelfCounter - 1];
                ContainerShelfArr[ContainerShelfCounter - 1] = ContainerShelf();
                ContainerShelfCounter--;
            }
        }
    }

    // Displays all Container Shelves in Warehouse
    void displayContainerShelves() {
        std::cout << "Container Shelves: ";
        for (int i = 0; i < ContainerShelfCounter; i++) {
            if (i != ContainerShelfCounter - 1) {
                std::cout << ContainerShelfArr[i] << ", ";
            }
            else {
                std::cout << ContainerShelfArr[i] << std::endl;
            }
        }
    }

    // Creates a 3D square'ish storage compartment with Container Shelves allready
    Warehouse(float length, float width, float height, int containerShelfArrSize) : Length(length), Width(width), Height(height), ContainerShelfArrSize(containerShelfArrSize)
    {
        ContainerShelfArr = new ContainerShelf[ContainerShelfArrSize];
    };

    // Creates a 3D square'ish storage compartment without Container Shelves
    Warehouse(float length, float width, float height) : Length(length), Width(width), Height(height)
    {
        ContainerShelfArr = nullptr;
        ContainerShelfArrSize = 0;
    };

    // Destructor that also deletes dynamicly allocated memory *CRUCIAL DO NOT DELETE* - helps avoid memory leak 
    ~Warehouse() {
        delete[] ContainerShelfArr;
    }

protected:
    int ContainerShelfCounter = 0;
};