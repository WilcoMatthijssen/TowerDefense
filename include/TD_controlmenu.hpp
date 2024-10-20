
#ifndef TD_CONTROLMENU_HPP
#define TD_CONTROLMENU_HPP

#include <ranges>
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <iostream>
#include <numbers>
#include <algorithm>
#include <stack>
#include <format>
#include <chrono>
namespace TD{

    class ConfigMenu{

        sf::RectangleShape m_body;
        sf::Text m_clock_text;
        sf::Text m_money_text;
        sf::Text m_wave_text;

        float m_money =0 ;


        sf::Clock m_clock;
        sf::Font m_font;
        public:

        void configure(sf::Vector2f pos){
            m_body.setPosition(pos.x, 0);
            m_body.setSize({500, pos.y});
            m_body.setFillColor(sf::Color::Green);

            m_font.loadFromFile("../assets/Roboto-Black.ttf");

            m_clock_text.setCharacterSize(50);
            m_clock_text.setFillColor(sf::Color::Red);
            m_clock_text.setPosition({pos.x + 10, 10});
            m_clock_text.setFont(m_font);


            m_money_text.setCharacterSize(50);
            m_money_text.setFillColor(sf::Color::Red);
            m_money_text.setPosition({pos.x + 10, 110});
            m_money_text.setFont(m_font);
            m_money_text.setString("0$");


            m_wave_text.setCharacterSize(50);
            m_wave_text.setFillColor(sf::Color::Red);
            m_wave_text.setPosition({pos.x + 10, 210});
            m_wave_text.setFont(m_font);
            m_wave_text.setString("-");


            m_clock.restart();
        }

        void update(){
            size_t seconds = static_cast<size_t>(m_clock.getElapsedTime().asSeconds()) % 60;
            size_t minutes = static_cast<size_t>(m_clock.getElapsedTime().asSeconds()) / 60;
            m_clock_text.setString(std::format("{:02}:{:02}", minutes, seconds));
        }

        void set_wave_number(size_t number){
            m_wave_text.setString(std::format("{}", number));
        }

        void add_money(float amount){
            m_money += amount;
            m_money_text.setString(std::format("{}$", m_money));
        }
        
        bool subtract_money(float amount){
            if(amount > m_money){
                return false;
            }
            m_money -= amount;
            m_money_text.setString(std::format("{}$", m_money));

            return true;
        }

        void draw(sf::RenderWindow &window) const {
            window.draw(m_body);
            window.draw(m_clock_text);
            window.draw(m_money_text);
            window.draw(m_wave_text);

        }
    };
}
#endif