// Online C++ compiler to run C++ program online
#include <iostream>
#include <type_traits>

#define DEBUG true

struct Logger {
public:
    enum Level {
    debug, info
};

    template <typename T>
    Logger& operator<<(const T& msg)
    {   
        if constexpr ( std::is_same<T, int>::value) {
            std::cout << std::to_string (msg);
        }else{
            std::cout << msg;
        }
        return *this;
    }

    friend Logger& log(Logger& logger, Level n)
    {
        logger.debug_level = n;
        return logger;
    }
    
    Logger::Level debug_level;
};

int main() {
    // Write C++ code here
    Logger l;
    log(l, Logger::Level::info) << "Hello world!";

    return 0;
}