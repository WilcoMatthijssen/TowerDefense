#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <TD_attacker.hpp>
#include <algorithm>
#include <math.h>
#include <numbers>
#include <TD_bullet.hpp>
#include <ranges>
namespace TD{
    class Defender{
        sf::RectangleShape m_body;
        float m_attack_damage= 5;
        float m_speed =5;
        size_t m_target_id = 0;
        sf::Clock m_reload_clock;
        float m_range = 69420;


    public:
        Defender(){

            m_reload_clock.restart();
            m_body.setPosition({500,500});
            m_body.setSize({100,100});
            m_body.setFillColor(sf::Color::Cyan);
            m_body.setOrigin({50,50});
        }
         sf::Vector2f get_position() const{
           return m_body.getPosition(); 
        }
        void draw(sf::RenderWindow& window) const {
            window.draw(m_body);
        }

        float get_damage(){
            return m_attack_damage;
        }
        float get_speed(){
            return m_speed;
        }

        void attack(Attacker& attacker){
            attacker.recieve_damage(m_attack_damage);
        }

        float get_distance(const Attacker& target) const{
            const sf::Vector2f xy_diff = target.get_position() - m_body.getPosition();
            return std::sqrt((xy_diff.x * xy_diff.x) + (xy_diff.y * xy_diff.y));
        }


        void update(std::vector<Attacker>& targets, std::vector<Bullet>& bullets){
            auto found_target = targets.end();
            float min_range = m_range;
            
            for(auto target = targets.begin(); target < targets.end(); ++target){
                if ((target->get_id() == m_target_id) && (get_distance(*target) < m_range)){
                    found_target = target;
                    break;
                }

                const float distance = get_distance(*target);
                if(distance < min_range){
                    min_range = distance;
                    found_target = target;
                }
            }

            if(found_target == targets.end()){
                return;
            }

            m_target_id = found_target->get_id();
            rotate_to_position(found_target->get_position());
            if(m_reload_clock.getElapsedTime().asSeconds() > 0.050f){
                m_reload_clock.restart();
                bullets.push_back(Bullet(1, m_attack_damage, get_position(), found_target->get_position()));
            }
        }


        void rotate_to_position(const sf::Vector2f& position){
            const sf::Vector2f xy_diff = position - m_body.getPosition();
            const float rotation = atan2(xy_diff.y, xy_diff.x) * 180 / std::numbers::pi;
            m_body.setRotation(rotation + 180);
        }
    };
};
