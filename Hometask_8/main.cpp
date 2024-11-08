#include "Evolution.hpp"

int main(){
    GenericCreature gc("generic");
    OceanCreature oc("ocean");
    Amphibious am("amphibious");
    TerrestrialCreature tc("terrestrial");
    Bird b("bird");
    Waterfowl wf("waterfowl");

    gc.say_name();

    oc.say_name();
    oc.swim(2);

    am.say_name();
    am.swim(4);
    am.walk(3);

    tc.say_name();
    tc.walk(1);
    //tc.swim(3);

    b.say_name();
    b.walk(3);
    b.fly(4);
    //b.swim(2);

    wf.say_name();
    wf.walk(1);
    wf.swim(4);
    wf.fly(5);
}