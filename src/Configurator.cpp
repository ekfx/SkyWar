#include "Configurator.h"

ERRORCODE Configurator::Read(const std::filesystem::path& source_path) {
    if (!std::filesystem::exists(source_path)) {
        return ERRORCODE::FILE_DONT_EXIST;
    } else {
        std::ifstream t_file;
        
        t_file.open(source_path.string().c_str());
        if (t_file.is_open()) {
            std::string t_line        = "";
            std::string t_key         = "";
            bool        equal_trigger = false; 
            
            while (std::getline(t_file, t_line)) {
                std::string s_value = "";
                bool is_number      = false;
                
                if (t_line.empty()) {
                    // there's nothing here
                } else if ((t_line[0] == '#') || 
                            (t_line[0] == '/' && t_line[1] == '/') ||
                            (t_line[0] == ' ')) {
                    // this is a commentary or inappropriate format
                } else {
                    size_t index_equal;
                    for (size_t i = 0; i < t_line.length(); i++) {
                        if (t_line[i] == '=') {
                            equal_trigger = true;
                            index_equal = i;
                        }
                        
                        if (!equal_trigger && t_line[i] != '=') {
                            t_key += t_line[i];
                        } 
                        
                        if (equal_trigger && i != index_equal) {
                            s_value += t_line[i];
                            
                        }
                    }
                    
                    if (READ_PREFERENCE == 0) {
                        // for generic (have restrictions)
                        std::string c = "";
                        c = s_value.at(0);
                        if (c.find_first_of("1234567890-+") != c.npos) {
                            // se nao encontrar retorna npos (-1 ou o maior valor possivel para uint)
                            // queremos que NAO encontre para que seja numero.
                            is_number = true;
                        } else {
                            is_number = false;
                        }
                        
                        
                        // std::cout << "KEY: " << t_key << " - VALUE: " << s_value << " - NUMBER: " << is_number << std::endl;
                        // system("pause"); 
                        
                        if (is_number) {
                            n_data.insert({t_key, std::stof(s_value) });
                        } else {
                            c_data.insert({t_key, s_value });
                        }

                    } else if (READ_PREFERENCE == 1) {
                        // for text
                        c_data.insert({t_key, s_value });
                    } else if (READ_PREFERENCE == -1) {
                        // for number
                        n_data.insert({t_key, std::stof(s_value) });
                    } else {
                        return ERRORCODE::INVALID_READ;
                    }
                    
                    equal_trigger       = false;
                    t_key               = "";
                    t_line              = "";
                }
            }
        } else {
            return ERRORCODE::COULDNT_OPEN_FILE;
        }
        t_file.close();
        return ERRORCODE::SUCCESS;
    }
}

std::expected<float, ERRORCODE> Configurator::GetValueN(const std::string& key) {
    auto iterador = n_data.find(key);
    std::map<std::string, float>::iterator null_it{};
    
    if (iterador != null_it) {
        return iterador->second;    
    } else {
        return std::unexpected(ERRORCODE::NOT_FOUND_KEY);
    }
}
    
std::expected<std::string, ERRORCODE> Configurator::GetValueC(const std::string& key) {
    auto iterador = c_data.find(key);
    std::map<std::string, std::string>::iterator null_it{};
    
    if (iterador != null_it) {
        return iterador->second;    
    } else {
        return std::unexpected(ERRORCODE::NOT_FOUND_KEY);
    }
}

std::map<std::string, float>& Configurator::GetMapN() {
    return n_data;
}
std::map<std::string, std::string>& Configurator::GetMapC() {
    return c_data;
}

void Configurator::CleanN() {
    n_data.clear();
}

void Configurator::CleanC() {
    c_data.clear();
}

void Configurator::Clean() {
    n_data.clear();
    c_data.clear();
}