#include "Time_Friends.hpp"

//Private
void Time::Normalize_Sec(Time& t){
    int shift_seconds;
    int shift_minutes;
    if(t.GetSeconds() < 0 || t.GetSeconds() > 59){
        shift_minutes = t.GetSeconds() / 60;
        if(t.GetSeconds() < 0){
            if(t.GetSeconds() - 60 * shift_minutes != 0)
                shift_minutes--;
        }
        t.minutes += shift_minutes;

        shift_seconds = t.GetSeconds() - (t.GetSeconds() / 60) * 60;
        if(shift_seconds < 0){
            t.seconds = 60 + shift_seconds;
        }
        else t.seconds = shift_seconds;   
    }
}

void Time::Normalize_Min(Time& t){
    int shift_minutes;
    int shift_hours;
    if(t.GetMinutes() < 0 || t.GetMinutes() > 59){
        shift_hours = t.GetMinutes() / 60;
        if(t.GetMinutes() < 0){
            if(t.GetMinutes() - 60 * shift_hours != 0)
                shift_hours--;
        }
        t.hours += shift_hours;

        shift_minutes = t.GetMinutes() - (t.GetMinutes() / 60) * 60;
        if(shift_minutes < 0){
            t.minutes = 60 + shift_minutes;
        }
        else t.minutes = shift_minutes;
    }
}

void Time::Normalize(Time& t){
    Normalize_Sec(t);
    Normalize_Min(t);
    if(t.GetHours() < 0){
        t.hours = 0;
    }
    else if(t.GetHours() > 23){
        t.hours = 23;
    }
}

//Public
Time::Time() noexcept{
    hours = minutes = seconds = 0;
    count++;
    cout << "Constructor has called, object's count = " << count << endl;
}

Time::Time(int h, int m, int s): hours(h), minutes(m), seconds(s){
    if(h < 0)
        throw std::invalid_argument("\nERROR: Hours must be positive\n");
    count++;
    cout << "Constructor has called, object's count = " << count << endl;
    Normalize(*this);
}
            
// конструктор копирования
Time::Time(const Time& t) noexcept{
    hours = t.hours;
    minutes = t.minutes;
    seconds = t.seconds;
    Normalize(*this);
    count++;
    cout << "Constructor has called, object's count = " << count << endl;
}

Time::~Time() noexcept{
    count--;
    cout << "Destructor has called, object's count = " << count << endl;
}

void Time::print_count() noexcept{
    cout << "Created " << count <<
    " objects" << endl;
}

void Time::printTime() const noexcept {
    std::cout << "H:" << this->GetHours() << " M:" <<
    this->GetMinutes() << " S:" << this->GetSeconds() << std::endl;
}

int Time::toSeconds() noexcept{
    return seconds + minutes * 60 + hours * 3600;
}

Time& Time::operator = (const Time& other){
    hours = other.hours;
    minutes = other.minutes;  
    seconds = other.seconds;
    return *this;
}

int Time::operator - (int s){
    return this->toSeconds() - s;
}

Time& Time::operator += (int s) {
    seconds += s;
    Normalize(*this);
    return *this;
}

Time& Time::operator -= (int s){
    seconds -= s;
    Normalize(*this);
    return *this;
}

bool Time::operator == (Time& t){
    return seconds == t.GetSeconds() && minutes == t.GetMinutes() && hours == t.GetHours();
}