#ifndef TD_MAP_HPP
#define TD_MAP_HPP
#include <SFML/Graphics.hpp>
#include <vector>

namespace TD{
    class Map{
    private:
        std::vector<sf::RectangleShape> m_tiles;
        sf::Vector2f m_position;
        sf::Vector2f m_size;
        size_t m_row_size;
        std::vector<sf::Vector2f> m_route{{1000,1000},{100,900},{900,300},{100,400},{100,100},{100,900},{900,300},{100,400},{100,100},{100,900},{900,300},{100,400}};

        void update_tile_size_and_position(){
            for(size_t i = 0; i < m_tiles.size(); ++i){
                const float x_pos = m_position.x + (m_size.x * (i % m_row_size));
                const float y_pos = m_position.y + (m_size.y * (i / m_row_size));

                m_tiles[i].setPosition({x_pos, y_pos});
                m_tiles[i].setSize(m_size);
            }
        }
         
    public:

        void draw(sf::RenderWindow& window) const{
            for(const auto& tile: m_tiles){
                window.draw(tile);
            }
        }

        void create_tiles(const sf::Vector2u& size){
            m_tiles.resize(size.x * size.y);
            m_row_size = size.x;
            for(auto& tile: m_tiles){
                tile.setFillColor(sf::Color::Red);
                tile.setOutlineColor(sf::Color::Green);
                tile.setOutlineThickness(1);
            }
            update_tile_size_and_position();
        }
        
        void set_position_and_size(const sf::Vector2f& position, const sf::Vector2f& size){
            m_position = position;
            m_size = size;
            update_tile_size_and_position();
        }

        const std::vector<sf::Vector2f>& get_route(){
            return m_route;
        }
    };
};
#endif