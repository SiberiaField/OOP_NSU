#include "Clocks.cpp"

int main(){
    Clock c;

    Watch w;
    Wall_Clock wc;
    wc.changeRoom("Bedroom");
    wc.showTime();

    Smart_Watch sw;
    Cuckoo_Clock cc;
    cc.changePhrase("Hello");
    cc.showTime();
}