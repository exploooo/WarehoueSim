#pragma once
#include<iostream>

// A parent abstract Cargo object
// TBDIF
// Future inheritance to distinct Cargo Types
class Cargo {
public:

    virtual void showContent() = 0;

};

class EmptyCargoSpace : public Cargo {
private:
    std::string ContentDescription = "Empty Space";

public:

    virtual void showContent() {
        std::cout << ContentDescription << std::endl;
    }

};

class FoodCargo : public Cargo {
private:
    std::string ContentDescription = "Food";

public:

    virtual void showContent() {
        std::cout << ContentDescription << std::endl;
    }
};