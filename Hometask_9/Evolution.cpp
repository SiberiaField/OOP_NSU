#include "Evolution.hpp"

// GenericCreature
void GenericCreature::say_name(){
    std::cout << "\nMy name is " << name << std::endl;
}

// OceanCreature
void OceanCreature::swim(int m){
    std::cout << name << " has swum " << m << " metres" << std::endl;
}

// Amphibious
void Amphibious::walk(int m){
    std::cout << name << " has walked " << m << " metres" << std::endl;
}

// Bird
void Bird::fly(int h){
    std::cout << name << " is flying at a height of " << h << " metres" << std::endl;
}
