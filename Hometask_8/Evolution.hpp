#ifndef EVOLUTION
#define EVOLUTION


#include <iostream>

class GenericCreature{
    protected:
        std::string name;
    public:
        GenericCreature(){
            name = "Unnamed";
        }

        GenericCreature(std::string name){
            this->name = name;
        }

        ~GenericCreature(){
            name.clear();
        }

        void say_name();
};

class OceanCreature: public GenericCreature{
    protected:
        using GenericCreature::name;
    public:
        OceanCreature() : GenericCreature(){}
        OceanCreature(std::string name) : GenericCreature(name){}
        ~OceanCreature(){
            name.clear();
        }

        void swim(int m);
};

class Amphibious: public OceanCreature{
    protected:
        using GenericCreature::name;
    public:
        Amphibious() : OceanCreature(){}
        Amphibious(std::string name) : OceanCreature(name){}
        ~Amphibious(){
            name.clear();
        }

        void walk(int m);
};

class TerrestrialCreature: protected Amphibious{
    protected:
        using Amphibious::name;
    public:
        TerrestrialCreature() : Amphibious(){}
        TerrestrialCreature(std::string name) : Amphibious(name){}
        ~TerrestrialCreature(){
            name.clear();
        }

        using Amphibious::walk;
        using GenericCreature::say_name;
};

class Bird: public TerrestrialCreature{
    public:
        Bird() : TerrestrialCreature(){}
        Bird(std::string name) : TerrestrialCreature(name){}
        ~Bird(){
            name.clear();
        }

        using Amphibious::walk;
        void fly(int h);
 };

class Waterfowl: public Bird{
    public:
        Waterfowl() : Bird(){}
        Waterfowl(std::string name) : Bird(name){}
        ~Waterfowl(){
            name.clear();
        }

        using OceanCreature::swim;
        using Amphibious::walk;
        using Bird::fly;
};


#endif