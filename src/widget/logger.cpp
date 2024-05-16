#include "logger.h"

#include <chrono>
#include <iostream>

void
Logger::log(std::chrono::time_point<std::chrono::system_clock> t, std::string operationName)
{
    const std::time_t t_c = std::chrono::system_clock::to_time_t(t);
    std::cout << "The system clock is currently at " << std::ctime(&t_c) << ": "
        << operationName<<std::endl;
}
