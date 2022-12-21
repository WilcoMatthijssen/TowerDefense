#ifndef TD_DEFENDER_HPP
#define TD_DEFENDER_HPP

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <TD_attacker.hpp>
#include <algorithm>
#include <math.h>
#include <numbers>



namespace TD{
    class Defender{
        sf::RectangleShape m_body;
        float m_attack_damage;
        size_t m_target_id = 0;
        sf::Clock m_reload_clock;
        float m_range = 69420;


    public:
        void draw(sf::RenderWindow& window) const {
            window.draw(m_body);
        }


        void attack(Attacker& attacker){
            attacker.recieve_damage(m_attack_damage);
        }
    

        void set_target(Attacker * attacker){
            // m_target_id = attacker->get_id();
            m_reload_clock.restart();
            m_body.setPosition({500,500});
            m_body.setSize({100,100});
            m_body.setFillColor(sf::Color::Cyan);
            m_body.setOrigin({50,50});
        }


        float get_distance(const Attacker target) const{
            const auto xy_distance = target.get_position() - m_body.getPosition();
            return std::sqrtf((xy_distance.x * xy_distance.x) + (xy_distance.y * xy_distance.y));
        }


        void update(std::vector<Attacker>& targets){
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
            if(m_reload_clock.getElapsedTime().asSeconds() > 0.5F){
                m_reload_clock.restart();
                std::cout<<"Poef"<<std::endl;
            }
        }


        void rotate_to_position(const sf::Vector2f& position){
            const sf::Vector2f diff = position - m_body.getPosition();
            const float rotation = (atan2(diff.y, diff.x)) * 180 / std::numbers::pi_v<float>;
            m_body.setRotation(rotation + 180);
        }
    };
};
#endif
