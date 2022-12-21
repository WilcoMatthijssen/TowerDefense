#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace TD{
    class Tower{
        sf::RectangleShape m_body;
        float m_health_points;

    public:
        void draw(sf::RenderWindow& window) const {
            window.draw(m_body);
        }

        void recieve_damage(const float& damage){
            m_health_points -= (damage < m_health_points) ? damage : 0;
        }

        bool is_destroyed() const{ 
            return m_health_points <= 0; 
        }
    };
};