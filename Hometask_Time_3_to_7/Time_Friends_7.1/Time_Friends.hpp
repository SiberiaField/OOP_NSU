#ifndef FRIEND_TIME
#define FRIEND_TIME


#include <iostream>

using namespace std;

class Time{
    int hours, minutes, seconds;
    static inline unsigned count = 0;

    private:
        static void Normalize_Sec(Time& t);
        static void Normalize_Min(Time& t);
        static void Normalize(Time& t);

    public:
        // defaults
        Time() noexcept;
        Time(int h, int m, int s);
        // конструктор копирования
        Time(const Time& t) noexcept;
        ~Time() noexcept;

        int GetHours() const { return hours; }
        int GetMinutes() const { return minutes; }
        int GetSeconds() const { return seconds; }

        void printTime() const noexcept;
        static void print_count() noexcept;
        int toSeconds() noexcept;

        Time& operator = (const Time& other);
        int operator - (int s);
        Time& operator += (int s);
        Time& operator -= (int s);
        bool operator == (Time& t);

        friend class SimpleWatch;
        friend void showTime(const Time& t) noexcept;
        friend void changeTime(Time& t, int h, int m, int s);
};

class SimpleWatch{
    private:
        bool format24;
    public:
        SimpleWatch(){
            format24 = true;
        }

        void printTime(const Time& t) const noexcept{
            int h = t.hours;
            if(!format24){
                h = h > 12 ? h - 12 : h;
            }
            std::cout << "H:" << h << " M:" <<
            t.minutes << " S:" << t.seconds << std::endl;
        }
        
        void setTime(Time& t, int h, int m, int s){
            t.hours = h;
            t.minutes = m;
            t.seconds = s;
            Time::Normalize(t);
        }

        void setFormat(bool format24){
            this->format24 = format24;
        }
};

class Watch{
    private:
        static inline bool format24 = true;
    public:
        friend void showTime(const Time& t) noexcept{
            int h = t.hours;
            if(!format24){
                h = h > 12 ? h - 12 : h;
            }
            std::cout << "H:" << h << " M:" <<
            t.minutes << " S:" << t.seconds << std::endl;
        }

        friend void changeTime(Time& t, int h, int m, int s){
            t.hours = h;
            t.minutes = m;
            t.seconds = s;
            Time::Normalize(t);
        }

        void setFormat(bool format24){
            this->format24 = format24;
        }
};


#endif