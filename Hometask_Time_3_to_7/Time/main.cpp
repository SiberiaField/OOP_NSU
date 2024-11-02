#include "Time.hpp"
#include <iostream>
#include <vector>
#include <memory>

int main(){
    Time t(22, -10, -10);
    t.printTime();
    cout << t.toSeconds() << endl;
    cout << t - 60 << endl;
    Time t1(t);
    cout << (t1 == t) << endl;
    Time::print_count();

    //6.1a
    Time* ptr = new Time{22, 33, 77};
    ptr->printTime();
    Time* arr = new Time[4];
    arr[0] = Time(33, 14, 30);
    arr[0].printTime();

    //6.1б
    vector<Time> t_vec;
    t_vec.push_back(t);
    t_vec[0].printTime();

    //6.1в
    std::unique_ptr<Time> uniqptr = std::make_unique<Time>(22, 11, 58);
    std::shared_ptr<Time> shareptr = std::make_shared<Time>(33, 20, 5);
    (*shareptr).printTime();
    delete[] arr;

    //6.2
    try{
        Time t2(-10, 5, 6);
    }
    catch(const std::exception& exp){
        std::cerr << exp.what() << std::endl;
    }
}