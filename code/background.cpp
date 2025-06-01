#include "background.h"

bool complex_world_checker(float x, float y, const std::vector<std::vector<int>>& table)
{
    int i = static_cast<int>(std::floor(x / 40));
    int j = static_cast<int>(std::floor(y / 40));
    return table[i][j] < 5;
}

bool is_inside_world(const float x, const float y, const float world_width, const float world_height)
{
    return (x >= 0 && x <= world_width - 60 && y >= 0 && y <= world_height - 60);
}
void draw_back(sf::RenderWindow& window, const std::vector<std::vector<int>>& table, const sf::View& camera)
{
    constexpr float cell_size = 40;

    sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));

    sf::FloatRect visible_area = camera.getViewport();
    int start_x = static_cast<int>(camera.getCenter().x - camera.getSize().x / 2) / cell_size;
    int start_y = static_cast<int>(camera.getCenter().y - camera.getSize().y / 2) / cell_size;
    int end_x = static_cast<int>(camera.getCenter().x + camera.getSize().x / 2) / cell_size;
    int end_y = static_cast<int>(camera.getCenter().y + camera.getSize().y / 2) / cell_size;

    start_x = std::max(0, start_x);
    start_y = std::max(0, start_y);
    end_x = std::min(static_cast<int>(table.size()) - 1, end_x);
    end_y = std::min(static_cast<int>(table[0].size()) - 1, end_y);

    for (int i = start_x; i <= end_x; i++)
    {
        for (int j = start_y; j <= end_y; j++)
        {
            cell.setPosition(static_cast<float>(i) * cell_size, static_cast<float>(j) * cell_size);

            switch (table[i][j])
            {
                case 0:
                    cell.setFillColor(sf::Color(42, 34, 49));
                break;
                case 1:
                    cell.setFillColor(sf::Color(41, 33, 48));
                break;
                case 2:
                    cell.setFillColor(sf::Color(44, 33, 49));
                break;
                case 3:
                    cell.setFillColor(sf::Color(41, 33, 46));
                break;
                case 4:
                    cell.setFillColor(sf::Color(40, 32, 47));
                break;
                default:
                    cell.setFillColor(sf::Color::Black);
            }

            window.draw(cell);
        }
    }
}