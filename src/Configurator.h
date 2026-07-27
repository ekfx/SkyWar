#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <map>
#include <expected>
#include <optional>
#include <memory>
#include <variant>
#include <meta>
#include <type_traits>
#include <cstdint>
#include "Advanced.hpp"

class Configurator {
private:
    std::map<std::string, float> n_data;
    std::map<std::string, std::string> c_data;
    int READ_PREFERENCE;
    /*
        0  -> automatic
        1  -> only text
        -1 -> only numbers
    */

public:
    Configurator(int read_preference = 0) : READ_PREFERENCE(read_preference) {};
    ~Configurator() {};

    ERRORCODE Read(const std::filesystem::path& source_path);    
    std::expected<float, ERRORCODE> GetValueN(const std::string& key);
    std::expected<std::string, ERRORCODE> GetValueC(const std::string& key);
    
    std::map<std::string, float>& GetMapN();
    std::map<std::string, std::string>& GetMapC();

    void CleanN();
    void CleanC();
    void Clean();
};

#endif // CONFIGURATOR_H