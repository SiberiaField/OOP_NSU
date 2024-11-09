#include "Evolution.cpp"

int main(){
    //GenericCreature gc("generic");
    OceanCreature oc("ocean");
    Amphibious am("amphibious");
    TerrestrialCreature tc("terrestrial");
    Bird b("bird");
    Waterfowl wf("waterfowl");

    oc.say_name();
    oc.swim(2);
    oc.eat();

    am.say_name();
    am.swim(4);
    am.walk(3);
    am.eat();

    tc.say_name();
    tc.walk(1);
    tc.eat();
    //tc.swim(3);

    b.say_name();
    b.walk(3);
    b.fly(4);
    b.eat();
    //b.swim(2);

    wf.say_name();
    wf.walk(1);
    wf.swim(4);
    wf.fly(5);
    wf.eat();
}