#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace Gpio {
    static void configurePin(int pinNumber, std::string direction) {
        std::fstream fs;
        std::ostringstream path;
        path << "/sys/class/gpio/gpio" << pinNumber << "/direction";

        if (!std::filesystem::exists(path.str())) {
            fs.open("/sys/class/gpio/export", std::fstream::out);
            fs << pinNumber;
            fs.close();
        }

        fs.open(path.str(), std::fstream::out);
        fs << direction;
        fs.close();
    }

    static void writeToPin(int pinNumber, bool value) {
        std::fstream fs;
        std::ostringstream path;
        path << "/sys/class/gpio/gpio" << pinNumber << "/value";
        fs.open(path.str(), std::fstream::out);
        char charValue = 48 + value;
        fs.put(charValue);
        fs.close();
    }

    static bool readFromPin(int pinNumber) {
        std::fstream fs;
        std::ostringstream path;
        path << "/sys/class/gpio/gpio" << pinNumber << "/value";
        fs.open(path.str(), std::fstream::in);
        char charValue = fs.get();
        fs.close();
        bool value = charValue - 48;

        return value;
    }
} // namespace Gpio