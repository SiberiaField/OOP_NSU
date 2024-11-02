#include "../Time/Time.hpp"
#include <iostream>
#include <vector>

class Clock{
    private:
        inline static int count = 0;

        void constructorMessage(){
            std::cout << "Clock constructor, count = " << ++count << endl;
        }

        void destructorMessage(){
            std::cout << "Clock destructor, count = " << --count << endl;
        }
    protected:
        Time t;
        bool format24;
    public:
        Clock(){
            format24 = true;
            constructorMessage();
        }

        Clock(int h, int m, int s, bool format24){
            t = Time(h, m, s);
            this->format24 = format24;
            constructorMessage();
        }

        Clock(const Clock& w){
            t = w.t;
            format24 = w.format24;
            constructorMessage();
        }

        ~Clock(){
            destructorMessage();
        }

        void showTime(){
            int h = t.GetHours();
            if(!format24){
                h = h > 12 ? h - 12 : h;
            }
            std::cout << "\n" << "H:" << h << " M:" <<
            t.GetMinutes() << " S:" << t.GetSeconds() << std::endl;
        }

        void setTime(const Time& t){
            this->t = t;
        }

        void changeFormat(bool format24){
            this->format24 = format24;
        }
};

class Wall_Clock : public Clock{
    private:
        inline static int count = 0;

        void constructorMessage(){
            std::cout << "Wall_Clock constructor, count = " << ++count << endl;
        }

        void destructorMessage(){
            std::cout << "Wall_Clock destructor, count = " << --count << endl;
        }
    protected:
        string room;
    public:
        Wall_Clock() : Clock(){
            room = "Kitchen";
            constructorMessage();
        }

        Wall_Clock(int h, int m, int s, bool format24, string room) : Clock(h, m, s, format24){
            this->room = room;
            constructorMessage();
        };

        Wall_Clock(const Wall_Clock& wc) : Clock(wc){
            room = wc.room;
            constructorMessage();
        }

        ~Wall_Clock(){
            destructorMessage();
        }

        void showTime(){
            int h = t.GetHours();
            if(!format24){
                h = h > 12 ? h - 12 : h;
            }
            std::cout << "\n" << "Time in " << room << " is "<< h << ":" <<
            t.GetMinutes() << ":" << t.GetSeconds() << std::endl;
        }

        void changeRoom(string room){
            this->room = room;
        }

        // using Clock::setTime;
        // using Clock::changeFormat;
};

class Watch : public Clock{
    private:
        inline static int count = 0;

        void constructorMessage(){
            std::cout << "Watch constructor, count = " << ++count << endl;
        }

        void destructorMessage(){
            std::cout << "Watch destructor, count = " << --count << endl;
        }
    protected:
        bool right_hand;
    public:
        Watch() : Clock(){
            right_hand = true;
            constructorMessage();
        }

        Watch(int h, int m, int s, bool format24, bool right_hand) : Clock(h, m, s, format24){
            this->right_hand = right_hand;
            constructorMessage();
        };

        Watch(const Watch& w) : Clock(w){
            right_hand = w.right_hand;
            constructorMessage();
        }

        ~Watch(){
            destructorMessage();
        }

        void showTime(){
            int h = t.GetHours();
            if(!format24){
                h = h > 12 ? h - 12 : h;
            }
            string hand = right_hand ? "right" : "left";

            std::cout << "\n" << "You look at your " << hand << " hand, time is "<< h << " hours, " <<
            t.GetMinutes() << " minutes, and " << t.GetSeconds() << " seconds" << std::endl;
        }

        void changeHand(bool right_hand){
            this->right_hand = right_hand;
        }

        // using Clock::setTime;
        // using Clock::changeFormat;
};

class Cuckoo_Clock final: public Wall_Clock{
    private:
        inline static int count = 0;
        string phrase;

        void constructorMessage(){
            std::cout << "Cuckoo_Clock constructor, count = " << ++count << endl;
        }

        void destructorMessage(){
            std::cout << "Cuckoo_Clock destructor, count = " << --count << endl;
        }
    public:
        Cuckoo_Clock() : Wall_Clock(){
            phrase = "Cuckoo";
            constructorMessage();
        }

        Cuckoo_Clock(int h, int m, int s, bool format24, 
                    string room, string phrase) : Wall_Clock(h, m, s, format24, room){
            this->phrase = phrase;
            constructorMessage();
        }

        Cuckoo_Clock(const Cuckoo_Clock& cc) : Wall_Clock(cc){
            phrase = cc.phrase;
        }

        ~Cuckoo_Clock(){
            destructorMessage();
        }

        void showTime(){
            int h = t.GetHours();
            if(!format24){
                h = h > 12 ? h - 12 : h;
            }
            std::cout << "\n" << phrase << "! Time in " << room << " is "<< h << ":" <<
            t.GetMinutes() << ":" << t.GetSeconds() << std::endl;
        }

        void changePhrase(string phrase){
            this->phrase = phrase;
        }

        // using Wall_Clock::changeRoom;
        // using Clock::setTime;
        // using Clock::changeFormat;
};

class Smart_Watch final: public Watch{
    private:
        inline static int count = 0;
        int day;
        vector<string> week = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

        void constructorMessage(){
            std::cout << "Smart_Watch constructor, count = " << ++count << endl;
        }

        void destructorMessage(){
            std::cout << "Smart_Watch destructor, count = " << --count << endl;
        }
    public:
        Smart_Watch() : Watch(){
            day = 0;
            constructorMessage();
        }

        Smart_Watch(int h, int m, int s, bool format24, 
                    bool right_hand, int day) : Watch(h, m, s, format24, right_hand){
            this->day = day;
            constructorMessage();
        }

        Smart_Watch(const Smart_Watch& sw) : Watch(sw){
            day = sw.day;
        }

        ~Smart_Watch(){
            destructorMessage();
        }

        void showTime(){
            int h = t.GetHours();
            if(!format24){
                h = h > 12 ? h - 12 : h;
            }
            std::cout << "\n" << week[day] << h << ":" <<
            t.GetMinutes() << ":" << t.GetSeconds() << std::endl;
        }

        void setDay(int day){
            if(0 <= day && day < 7){
                this->day = day;
            }
            else throw std::out_of_range("Day must be in [0, 6]");
        }

        // using Watch::changeHand;
        // using Clock::setTime;
        // using Clock::changeFormat;
};