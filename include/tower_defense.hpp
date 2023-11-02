#pragma once
#ifndef TD_TOWER_DEFENSE_HPP
#define TD_TOWER_DEFENSE_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>
#include <string>

#include <TD_attacker.hpp>
#include <TD_defender.hpp>
#include <TD_tower.hpp>
#include <TD_map.hpp>
#include <TD_fileparser.hpp>
#include <TD_bullet.hpp>


namespace TD{
    class Tower_defense{
        Map m_map;
        Tower m_tower;
        std::vector<Defender> m_defenders;
        std::vector<Attacker> m_attackers;
        std::vector<Bullet> m_bullets;

        size_t m_current_wave_number;
        std::vector<std::tuple<std::string, size_t>> waves;


    public:
        void draw(sf::RenderWindow& window) const{
            m_map  .draw(window);
            m_tower.draw(window);

            for(const Attacker& attacker: m_attackers){
                attacker.draw(window);
            }

            for(const Defender& defender: m_defenders){
                defender.draw(window);
            }

            for(const Bullet& bullet: m_bullets){
                bullet.draw(window);
            }
        }

        void update(){
            for(auto& attacker: m_attackers){
                attacker.update();
            }

            for(auto& defender: m_defenders){
                defender.update(m_attackers, m_bullets);
            }

            // Also directly removes the bullet from the vector when it hits an attacker
            std::erase_if(m_bullets, [&](Bullet& bullet){
                return bullet.update(m_attackers);
            });
        }



        void attacker_spawn_routine(){

        }
        
        void start(){
            m_defenders.push_back(Defender());

            m_attackers.resize(1);
            m_attackers[0].configure({80,80});
            m_map.set_position_and_size({1,1}, {100,100});
            m_map.create_tiles({10,10});

            m_attackers[0].set_route(&(m_map.get_route()));
        }
        
        size_t get_current_wave_number() const{
            return m_current_wave_number;
        }

        size_t get_amount_of_waves() const{
            return m_current_wave_number;
        }

        size_t get_remaining_attackers() const{
            return m_attackers.size();
        }

        bool have_defenders_won(){
            return (get_current_wave_number() == get_amount_of_waves()) && is_round_won();
        }

        bool is_round_won(){
            return m_attackers.empty();
        }
        bool have_attackers_won(){
            return m_tower.is_destroyed();
        }
        bool is_game_over(){
            return have_attackers_won() || have_defenders_won();
        }
    };
};

#endif