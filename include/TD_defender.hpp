#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "TD_attacker.hpp"
#include <algorithm>
#include <math.h>
#include <numbers>
#include <TD_bullet.hpp>
#include <ranges>
namespace TD{
    class Defender{
    private:
        sf::RectangleShape m_body;
        double m_attack_damage= 5;
        double m_range = 7420;

        sf::Time m_reloadspeed = sf::seconds(0.05);
        sf::Clock m_reload_clock;

        size_t m_target_id = 0;
        size_t m_id;
    public:
        Defender(sf::Vector2f pos, size_t id): m_id{id}, m_body{{80,80}}{
            // m_reload_clock.restart();
            m_body.setPosition(pos);
            m_body.setFillColor(sf::Color::Cyan);
            m_body.setOrigin({40,40});
        }

        size_t get_id() { 
            return m_id;
        }

        bool is_selected(sf::Vector2f point){
            return m_body.getGlobalBounds().contains(point.x, point.y);
         }

        sf::Vector2f get_position() const {
            return m_body.getPosition();
        }

        void draw(sf::RenderWindow &window) const {
            window.draw(m_body);
        }

        double get_damage(){
            return m_attack_damage;
        }

        float get_speed(){
            return m_reloadspeed.asSeconds();
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
            double min_range = m_range;
            
            for(auto target_it = targets.begin(); target_it < targets.end(); ++target_it){
                if ((target_it->get_id() == m_target_id) && (get_distance(*target_it) < m_range)){
                    found_target = target_it;
                    break;
                }

                const double distance = get_distance(*target_it);
                if(distance < min_range){
                    min_range = distance;
                    found_target = target_it;
                }
            }

            if(found_target == targets.end()){
                return;
            }

            m_target_id = found_target->get_id();
            rotate_to_position(found_target->get_position());
            if(m_reload_clock.getElapsedTime() > m_reloadspeed){
                m_reload_clock.restart();
                bullets.emplace_back(1, m_attack_damage, get_position(), found_target->get_position());
            }
        }


        void rotate_to_position(const sf::Vector2f& position){
            const sf::Vector2f xy_diff = position - m_body.getPosition();
            const double rotation = atan2(xy_diff.y, xy_diff.x) * 180 / std::numbers::pi;
            m_body.setRotation(rotation + 180);
        }
    };
};
