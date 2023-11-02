#ifndef TD_BULLET_HPP
#define TD_BULLET_HPP

// #include <TD_defender.hpp>
#include <TD_attacker.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numbers>
#include <cmath>
namespace TD
{

    class Bullet
    {
    public:
        Bullet(float speed, float damage, sf::Vector2f pos_def, sf::Vector2f pos_attack)
        {
            m_damage = damage;
            m_speed = speed;

            m_body.setPosition(pos_def);
            m_body.setFillColor(sf::Color::Blue);
            m_body.setSize(sf::Vector2f(40, 15));

            const auto diff = pos_attack - pos_def;
            m_direction = std::atan2(diff.y, diff.x);

            m_body.setRotation(m_direction * 180 / std::numbers::pi);

            m_clock.restart();
            m_distance = 0;
        }

        bool update(std::vector<Attacker> &attackers)
        {

            bool hit = false;
            const double distance = m_clock.restart().asMilliseconds() * m_speed;
            m_distance += distance;
            m_body.move(distance * std::cos(m_direction), distance * std::sin(m_direction));
            std::erase_if(attackers, [&](auto &attacker)
                          {
                if(!hit && attacker.get_global_bounds().intersects(m_body.getGlobalBounds())){
                    attacker.recieve_damage(m_damage);
                    hit = true;
                }
                return attacker.is_dead(); });

            return hit || (m_distance > 2000);
        }

        void draw(sf::RenderWindow &window) const
        {
            window.draw(m_body);
        }

        sf::RectangleShape m_body;
        // bool hit = false;
        float m_damage;
        float m_speed;
        float m_direction;
        float m_distance;
        sf::Clock m_clock;
    };
}

#endif