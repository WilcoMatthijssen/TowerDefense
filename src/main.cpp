#include <SFML/Graphics.hpp>
#include "tower_defense.hpp"
#include <ranges>
#include <iostream>
#include <TD_map.hpp>
#include <TD_attacker.hpp>
#include <filesystem>

#include <ranges>
#include <fstream>
#include <unordered_map>

int main(){
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Tower Defense" };

    window.setFramerateLimit(144);
    TD::Tower_defense td;
    td.start();

    // std::cout<<std::filesystem::current_path()<<std::endl;


    while (window.isOpen()){
        td.update();
        td.draw(window);

        window.display();

        for (auto event = sf::Event{}; window.pollEvent(event);){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear();
    }
}