#pragma once

#include <chrono>
#include <iostream>
#include <functional>

using Time = std::chrono::steady_clock::time_point;
using Duration = std::chrono::steady_clock::duration;
using namespace std::chrono;
using namespace std::literals;
using namespace std::placeholders;

class Alarm {
public:
    enum class Sound {Beep, Siren, Whistle};
    enum class Volume {Normal, Loud, LoudPlusPlus};

    static void setAlarm(Time t, Sound s, Duration d)
    {
        std::cout<<"setAlarm"<<std::endl;        
    }
    
    static void setAlarm(Time t, Sound s, Duration d, Volume v) //Overloaded
    {
        std::cout<<"setAlarm 2"<<std::endl;        
    }

    void test()
    {
        auto setSoundL = [](Sound s){
            setAlarm(steady_clock::now() + 1h, s, 30s);
        };

        using SetAlarm3ParamType = void (*)(Time t, Sound s, Duration d);
        auto setSoundB = 
            std::bind(static_cast<SetAlarm3ParamType>(setAlarm), 
                std::bind(std::plus<>(), std::bind(steady_clock::now),  1h),
                _1, 30s);

        setSoundL(Sound::Beep);
        setSoundB(Sound::Beep);
    }
};