#ifndef TD_MAP_HPP
#define TD_MAP_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <TD_fileparser.hpp>
#include <nlohmann/json.hpp>
#include <algorithm>
using json = nlohmann::json;

namespace TD{

      enum stuff{
            ROAD=0,
            PLACEABLE=1,
            OBSTACLE=2,
            PLACED=3
         };
    class Map{
    private:
        std::vector<std::pair<sf::RectangleShape, int>> m_tiles;
        sf::Vector2f m_position;
        sf::Vector2f m_size;
        size_t m_row_size;
        std::vector<sf::Vector2f> m_route;//{{1000,1000},{100,900},{900,300},{100,400},{100,100},{100,900},{900,300},{100,400},{100,100},{100,900},{900,300},{100,400}};

        void update_tile_size_and_position(){
            for(size_t i = 0; i < m_tiles.size(); ++i){
                const float x_pos = m_position.x + (m_size.x * (i % m_row_size));
                const float y_pos = m_position.y + (m_size.y * (i / m_row_size));

                m_tiles[i].first.setPosition({x_pos, y_pos});
                m_tiles[i].first.setSize(m_size);
            }
        }
      
    public:
        bool reserve_tower_spot(sf::Vector2i tile){
            const size_t tile_index = (tile.y * m_row_size) + tile.x;
            if(tile.x >= m_row_size || tile_index >= m_tiles.size() || get_tile_type(tile) != stuff::PLACEABLE ){
                return false;
            }

            m_tiles[tile_index].second = stuff::PLACED;
            return true;
        }

        std::vector<sf::Vector2f> pathCoordinates;

        void create_route(size_t row, size_t col) {
            // flooodfill
            size_t max_col = m_tiles.size() / m_row_size;
            if (row > m_row_size || col > max_col ||
                std::find(m_route.cbegin(), m_route.cend(), sf::Vector2f(1.0 * col, 1.0 * row)) != m_route.cend()
                || m_tiles[(row*m_row_size) + col].second != stuff::ROAD) {
                return; // Stop if out of bounds, already visited, or obstacle is present
            }

            m_route.push_back(sf::Vector2f(static_cast<float>(col), static_cast<float>(row)));

            create_route(row + 1, col);
            create_route(row - 1, col);
            create_route(row, col + 1);
            create_route(row, col - 1);
        }

        void draw(sf::RenderWindow& window) const{
            for(const auto& [tile, num]: m_tiles){
                window.draw(tile);
            }
        }
        stuff get_tile_type(sf::Vector2i pos){
            if(m_tiles.at((pos.y *m_row_size) + pos.x).second > stuff::PLACEABLE){
                return stuff::OBSTACLE;
            }
            return static_cast<stuff>(m_tiles.at((pos.y *m_row_size) + pos.x).second);
        }

        void create_tiles(Fileparser &fp){
            json& tile_json = fp.json_data["map"]["tiles"];
            json& tile_files = fp.json_data["map"]["tile_types"];
            m_row_size = tile_json[0].size();


            m_tiles.resize(tile_json.size() * m_row_size);
            // for(auto& [tile, num]: m_tiles){
            for (size_t i = 0; i < m_tiles.size(); ++i) {
                auto& [tile, num] = m_tiles[i];
                if (tile_json[i / m_row_size][i % m_row_size].is_number_integer()) {
                        num = tile_json[i / m_row_size][i % m_row_size].get<int>();
                } else {
                    // Handle the case where the value is not an integer (optional)
                    std::cerr << "Warning: JSON value is not an integer at index " << i << std::endl;
                    num = 0; // Default value or handle it as needed
                }
               

                const sf::Texture* text= fp.get_texture(tile_files[num].get<std::string>());
                tile.setTexture(text);

                // if (num != 0) {
                //     tile.setFillColor(sf::Color::Red);
                // } else {
                //     tile.setFillColor(sf::Color::Blue);
                // }

                tile.setOutlineColor(sf::Color::Green);
                tile.setOutlineThickness(1);
            }


            create_route(fp.json_data["map"]["start"][0].get<int>(), fp.json_data["map"]["start"][1].get<int>());
            for(sf::Vector2f& a: m_route){
                a.x *=  m_size.x;
                a.y *=  m_size.y;
            }
            update_tile_size_and_position();
        }
        
        void set_position_and_size(const sf::Vector2f position, const sf::Vector2f size){
            m_position = position;
            m_size = size;
            update_tile_size_and_position();
            
        }

        const std::vector<sf::Vector2f>& get_route(){
            return m_route;
        }

        sf::Vector2f get_total_size(){
            return {m_size.x * m_row_size, m_size.y * (m_tiles.size()/ m_row_size)};
        }
    };
};
#endif