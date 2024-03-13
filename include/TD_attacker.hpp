
#ifndef TD_ATTACKER_HPP
#define TD_ATTACKER_HPP

#include <ranges>
#include <SFML/Graphics.hpp>
#include <vector>
#include <TD_tower.hpp>
#include <TD_fileparser.hpp>
#include <array>
#include <iostream>
#include <numbers>
#include <algorithm>
#include <stack>
namespace TD{
class Attacker{
private:
    sf::RectangleShape m_body;
    float m_health_points=100;
    float m_speed= 10;
    float m_attack_damage;
    sf::Clock m_clock;
    const std::vector<sf::Vector2f> * m_route;
    size_t m_current_route_index;

    sf::Texture text;

    size_t m_id = 1;

public:

    size_t get_id() const;
    
    void set_route(const std::vector<sf::Vector2f> *const route);

    sf::Vector2f get_position() const;

    sf::FloatRect get_global_bounds();

    bool is_dead() const;

    void attack(Tower& tower);

    void recieve_damage(const float damage);

    void configure_stats(const float& health_points, const float& attack_damage, const float& speed);

    void configure(sf::Vector2f size, Fileparser &fp);
    
    void move_to_route_target(float steps);

 
    void animate(const float elapsed_seconds);
    void update();

    void draw(sf::RenderWindow& window) const;
};
};
#endif
