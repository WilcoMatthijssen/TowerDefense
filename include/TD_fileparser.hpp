#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <memory>
using json = nlohmann::json;

namespace TD{

    class Fileparser{
    public:
        void load(){
            std::string file_path = "../assets/config.json";

            try {
                // Open the file
                std::ifstream file_stream(file_path);
                if (!file_stream.is_open()) {
                    std::cerr << "Error opening file: " << file_path << std::endl;
                    return;
                }

                // Parse the JSON file
                file_stream >> json_data;

                // Close the file
                file_stream.close();
            } catch (const std::exception& e) {
                std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            }

            // std::cout << "Loaded JSON data:\n" << json_data.dump(4) << std::endl;
        }


        std::map<std::string, std::unique_ptr<sf::Texture>> texture;
        json json_data;


        sf::Texture * get_texture(std::string filename){
            if(!texture.contains(filename)){
                texture[filename] = std::make_unique<sf::Texture>();
                bool success = texture[filename]->loadFromFile(filename);
            }
            return texture.at(filename).get();
        }
            
    };
};