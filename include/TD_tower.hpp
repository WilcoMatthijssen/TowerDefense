#pragma once
#include <SFML/Graphics.hpp>
#include <TD_fileparser.hpp>
#include <vector>

namespace TD{
    class Tower{
    private:
        sf::RectangleShape m_body;
        float m_health_points;

    public:
        void configure(sf::Vector2f size, Fileparser &fp){
            m_body.setSize(size);
            m_body.setOrigin(m_body.getSize() / 2.0F);
            m_body.setTexture(fp.get_texture("../assets/walking.png"));
        }


        void draw(sf::RenderWindow& window) const {
            window.draw(m_body);
        }

        void recieve_damage(const float& damage){
            m_health_points -= std::min(damage, m_health_points);
        }

        bool is_destroyed() const{ 
            return m_health_points <= 0; 
        }

        void set_postition(const sf::Vector2f position){
            m_body.setPosition(position);
        }
    };
};
