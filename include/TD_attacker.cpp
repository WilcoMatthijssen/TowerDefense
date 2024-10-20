
#include "TD_attacker.hpp"
#include <ranges>
#include <SFML/Graphics.hpp>
#include <vector>
#include <TD_tower.hpp>
#include <TD_fileparser.hpp>
#include <array>
#include <iostream>
#include <numbers>
#include <algorithm>


namespace TD{

    size_t Attacker::get_id() const{
        return m_id;
    }

    
    void Attacker::set_route(const std::vector<sf::Vector2f> *const route){
        m_route = route;
        m_current_route_index = 0;
        m_body.setPosition(m_route->front());
    }


    sf::Vector2f Attacker::get_position() const{
        return m_body.getPosition(); 
    }

    sf::FloatRect Attacker::get_global_bounds(){
        return m_body.getGlobalBounds();
    }

    bool Attacker::is_dead() const{ 
        return m_health_points == 0; 
    }

    void Attacker::attack(Tower& tower){
        tower.recieve_damage(m_attack_damage);
    }

    float Attacker::recieve_damage(const float damage){
        m_health_points -= std::min(damage, m_health_points);
        return is_dead() ? 0 : m_reward;
    }

    void Attacker::configure_stats(const float& health_points, const float& attack_damage, const float& speed){
    
        m_health_points = health_points;
        m_attack_damage = attack_damage;
        m_speed         = speed;
    }

    void Attacker::configure(sf::Vector2f size, Fileparser &fp){
        m_body.setSize(size);
        m_body.setOrigin(m_body.getSize() / 2.0F);

        // m_body.setFillColor(sf::Color::Magenta);
        m_clock.restart();

        
        m_body.setTexture(fp.get_texture("../assets/walking.png"));
    }

    
    void Attacker::move_to_route_target(float steps){
        if (m_current_route_index == m_route->size()){
            return;
        }

        const sf::Vector2f direction = m_route->at(m_current_route_index) - m_body.getPosition();
        const float distanceToTarget = std::sqrt(direction.x * direction.x + direction.y * direction.y);
   
        if (distanceToTarget != 0.0f) {
            float moveDistance = std::min(steps, distanceToTarget);
            m_body.move(direction / distanceToTarget * moveDistance);
            m_body.setRotation(std::atan2(direction.y, direction.x) * 180.0f / std::numbers::pi + 180.0f);
            steps -= moveDistance;
        }

        if (steps > 0.0f) {
            ++m_current_route_index;
            move_to_route_target(steps);
        }
    }



    void Attacker::animate(const float elapsed_seconds){
        elapsed_seconds;
    }

    void Attacker::update(){

        // std::cout<<std::source_location::current().line()<<std::endl;
        const float elapsed_seconds = m_clock.restart().asSeconds();
        move_to_route_target(elapsed_seconds * m_body.getSize().x * m_speed);
        animate(elapsed_seconds);
    }

    void Attacker::draw(sf::RenderWindow& window) const{
        window.draw(m_body);
    }
};
