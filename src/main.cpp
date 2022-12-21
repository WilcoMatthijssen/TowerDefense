#include <SFML/Graphics.hpp>
#include "tower_defense.hpp"
#include <ranges>
#include <iostream>
#include <TD_map.hpp>
#include <TD_attacker.hpp>
#include <filesystem>


int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Tower Defense" };
    window.clear(sf::Color::Blue);

    // window.setFramerateLimit(60);
    window.setFramerateLimit(144);

    TD::Tower_defense td;

    td.start();
    

    // TD::Map m;
    // std::vector<TD::Attacker> a;
    // a.resize(1);
    // TD::Defender d;
    // d.set_target(&a[0]);
    // a[0].configure({80,80});
    // // a.set_position({600,300});
    // m.set_position_and_size({1,1}, {100,100});
    // m.create_tiles({10,10});

    // a[0].set_route(&(m.get_route()));
    std::cout<<std::filesystem::current_path()<<std::endl;


    while (window.isOpen())
    {
        td.update();
        td.draw(window);
        
        // m.draw(window);
        // a[0].draw(window);
        // a[0].update();
        // d.draw(window);
        // // d.rotate_to_target(sf::Mouse::getPosition(window));
        // d.update(a);
        window.display();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
    }
}