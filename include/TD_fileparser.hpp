#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

namespace TD{


    class Fileparser{
    public:
        std::map<std::string, sf::Texture> texture;

        sf::Vector2f get_tower_position(){
            return {1,1};
        }

        sf::Texture & get_texture(std::string filename){
            if(!texture.contains(filename)){
                texture[filename].loadFromFile(filename);
            }

            return texture.at(filename);
        }
        
    };
};