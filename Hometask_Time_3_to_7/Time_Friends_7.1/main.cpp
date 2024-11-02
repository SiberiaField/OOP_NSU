#include "Time_Friends.hpp"

int main(){
    Time t(22, 33, 10);
    showTime(t);

    SimpleWatch sw;
    sw.printTime(t);
}