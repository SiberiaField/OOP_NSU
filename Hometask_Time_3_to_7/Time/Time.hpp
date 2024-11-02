#ifndef CLASS_TIME
#define CLASS_TIME


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
};


#endif