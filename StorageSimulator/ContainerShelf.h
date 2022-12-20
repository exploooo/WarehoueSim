#pragma once
#include <iostream>
#include "Units.h"

// TBDIF
// A class that represents a basic ContainerShelf
class ContainerShelf {
private:
    std::string ContainerShelfID;
    int MaxUnits;

public:

    friend std::ostream& operator<<(std::ostream& os, ContainerShelf item);
    friend bool operator==(ContainerShelf a, ContainerShelf b);
    friend bool operator==(ContainerShelf a, std::string str);

    //Default Constructor
    ContainerShelf()
    {};

    ContainerShelf(std::string containerShelfID, int maxUnits) : ContainerShelfID(containerShelfID), MaxUnits(maxUnits)
    {};

protected:
    int UnitsCount = 0;
};

std::ostream& operator<<(std::ostream& os, ContainerShelf item) {
    os << item.ContainerShelfID;
    return os;
}

bool operator==(ContainerShelf a, ContainerShelf b) {
    if (a.ContainerShelfID == b.ContainerShelfID) {
        return true;
    }
    else {
        return false;
    }
}
bool operator==(ContainerShelf a, std::string str) {
    if (a.ContainerShelfID == str) {
        return true;
    }
    else {
        return false;
    }
}
