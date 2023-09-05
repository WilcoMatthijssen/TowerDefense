
#ifndef TD_ATTACKER_HPP
#define TD_ATTACKER_HPP

#include <ranges>
#include <SFML/Graphics.hpp>
#include <vector>
#include <TD_tower.hpp>
#include <array>
#include <iostream>
#include <source_location>



namespace TD{
    class Attacker{
        sf::RectangleShape m_body;
        float m_health_points;
        float m_speed;
        float m_attack_damage;
        sf::Clock m_clock;
        const std::vector<sf::Vector2f> * m_route;
        size_t m_current_route_index;

        sf::Texture text;

        size_t m_id = 1;

    public:

        size_t get_id() const{
            return m_id;
        }
        
        void set_route(const std::vector<sf::Vector2f> *const route){
            m_route = route;
            m_current_route_index = 0;
            m_body.setPosition(m_route->front());
        }

        sf::Vector2f get_position() const{
           return m_body.getPosition(); 
        }

        bool is_dead() const{ 
            return m_health_points == 0; 
        }

        void attack(Tower& tower){
            tower.recieve_damage(m_attack_damage);
        }

        void recieve_damage(const float damage){
            m_health_points -= std::min(damage, m_health_points);
        }

        void configure_stats(const float& health_points, const float& attack_damage, const float& speed){
     
            m_health_points = health_points;
            m_attack_damage = attack_damage;
            m_speed         = speed;
        }

        void configure(const sf::Vector2f size){
            m_body.setSize(size);
            m_body.setOrigin(size / 2.0F);
            // m_body.setFillColor(sf::Color::Magenta);
            m_clock.restart();

            text.loadFromFile("../../assets/walking.png");
            m_body.setTexture(&text);
        }

        void move_to_route_target(float steps){
            if(m_current_route_index == m_route->size()){
                return;
            }

            const auto diff = m_body.getPosition() - m_route->at(m_current_route_index);
            if(diff.x != 0){
                float x_delta = (steps < abs(diff.x)) ? steps : abs(diff.x);
                steps -= x_delta;
                x_delta *= (diff.x <= 0.f) ? 1.f : -1.f;
                m_body.move({x_delta, 0});
                m_body.setRotation((diff.x < 0.f) ? 0.f : 180.f);
            }
            else if(diff.y != 0){
                float y_delta = (steps < abs(diff.y)) ? steps : abs(diff.y);
                steps -= y_delta;
                y_delta *= (diff.y <= 0) ? 1 : -1;
                m_body.move({0, y_delta});
                m_body.setRotation((diff.y < 0.f) ? 90.f : 270.f);
            }
            
            if(steps != 0){
                ++m_current_route_index;
                move_to_route_target(steps);
            }
        }

        void animate(const float elapsed_seconds){
            elapsed_seconds;
        }

        void update(){

            std::cout<<std::source_location::current().line()<<std::endl;
            const float elapsed_seconds = m_clock.restart().asSeconds();
            move_to_route_target(elapsed_seconds * m_body.getSize().x * 10);
            animate(elapsed_seconds);
        }

        void draw(sf::RenderWindow& window) const{
            window.draw(m_body);
        }
    };
};
#endif
