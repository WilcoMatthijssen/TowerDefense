#include "tower_defense.hpp"
#include <SFML/Graphics.hpp>



int main(){
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Tower Defense" };

    window.setFramerateLimit(144);
    TD::Tower_defense td;
    td.start();
    TD::Fileparser f;
    f.load();

    while (window.isOpen()){
        td.update();
        td.draw(window);
        td.attacker_spawn_routine();

        window.display();

        for (auto event = sf::Event{}; window.pollEvent(event);){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                // Check if the event is a mouse button press
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Handle left mouse button click
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    td.place_turret(sf::Vector2f(mousePosition.x, mousePosition.y));
                }
                break;
                default:
                    break;
            }   
        }
        window.clear();
    }
}
