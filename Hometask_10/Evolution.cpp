#ifndef EVOLUTION
#define EVOLUTION


#include <iostream>

class GenericCreature{
    protected:
        std::string name;
    public:
        virtual void eat() = 0;

        GenericCreature(){
            name = "Unnamed";
        }

        GenericCreature(std::string name){
            this->name = name;
        }

        virtual ~GenericCreature(){
            name.clear();
        }

        void say_name(){
            std::cout << "\nMy name is " << name << std::endl;
        }
};

class OceanCreature: public GenericCreature{
    public:
        OceanCreature() : GenericCreature(){}
        OceanCreature(std::string name) : GenericCreature(name){}
        ~OceanCreature(){
            name.clear();
        }

        void eat() override{
            std::cout << "OceanCreature eat fish" << std::endl;
        }

        void swim(int m){
            std::cout << name << " has swum " << m << " metres" << std::endl;
        }
};

class Amphibious: public OceanCreature{
    public:
        Amphibious() : OceanCreature(){}
        Amphibious(std::string name) : OceanCreature(name){}
        ~Amphibious(){
            name.clear();
        }

        void eat() override{
            std::cout << "Amphibious eat fish and other amphibious" << std::endl;
        }

        void walk(int m){
            std::cout << name << " has walked " << m << " metres" << std::endl;
        }
};

class TerrestrialCreature: public Amphibious{
    public:
        TerrestrialCreature() : Amphibious(){}
        TerrestrialCreature(std::string name) : Amphibious(name){}
        ~TerrestrialCreature(){
            name.clear();
        }

        void eat() override{
            std::cout << "TerrestrialCreature eat forest food" << std::endl;
        }

        void swim(int m) = delete;
};

class Bird: public TerrestrialCreature{
    public:
        Bird() : TerrestrialCreature(){}
        Bird(std::string name) : TerrestrialCreature(name){}
        ~Bird(){
            name.clear();
        }

        void eat() override{
            std::cout << "Bird eat worms and bugs" << std::endl;
        }

        void fly(int h){
            std::cout << name << " is flying at a height of " << h << " metres" << std::endl;
        }
 };

class Waterfowl: public Bird{
    public:
        Waterfowl() : Bird(){}
        Waterfowl(std::string name) : Bird(name){}
        ~Waterfowl(){
            name.clear();
        }

        void eat() override{
            std::cout << "Waterfowl doesn't eat worms and bugs but eat fish" << std::endl;
        }
        
        using OceanCreature::swim;
};


#endif