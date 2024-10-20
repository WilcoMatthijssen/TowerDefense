#ifndef TD_BULLET_HPP
#define TD_BULLET_HPP

// #include <TD_defender.hpp>
#include "TD_attacker.hpp"
#include "TD_controlmenu.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numbers>
#include <cmath>

namespace TD{

    class Bullet{
    public:
        Bullet(double speed, double damage, sf::Vector2f pos_def, sf::Vector2f pos_attack): m_speed{speed}, m_damage{damage}{
            m_body.setPosition(pos_def);
            m_body.setFillColor(sf::Color::Blue);
            m_body.setSize(sf::Vector2f(40, 15));
            m_body.setOrigin(m_body.getSize() / 2.0F);


            const auto diff = pos_attack - pos_def;
            m_direction = std::atan2(diff.y, diff.x);

            m_body.setRotation(m_direction * 180 / std::numbers::pi);

            // m_clock.restart();
            m_distance = 0;
        }

        void move(){
            const double distance = m_clock.restart().asMilliseconds() * m_speed;
            m_distance += distance;
            m_body.move(distance * std::cos(m_direction), distance * std::sin(m_direction));
        }

        bool check_collission(std::vector<Attacker> &attackers, ConfigMenu& menu){
            bool hit = false;
            std::erase_if(attackers, [&](auto &attacker){
                if(!hit && attacker.get_global_bounds().intersects(m_body.getGlobalBounds())){
                    menu.add_money(attacker.recieve_damage(m_damage));
                    hit = true;
                }
                return attacker.is_dead(); });
            return hit;
        }

        bool update(std::vector<Attacker> &attackers, ConfigMenu& menu){
            move();
            return check_collission(attackers, menu) || (m_distance > 2000);
        }

        void draw(sf::RenderWindow &window) const{
            window.draw(m_body);
        }

    private:
        sf::RectangleShape m_body;
        double m_damage;
        double m_speed;
        double m_direction;
        double m_distance;
        sf::Clock m_clock;
    };
}

#endif