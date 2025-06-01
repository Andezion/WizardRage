#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <cmath>

bool complex_world_checker(float x, float y, const std::vector<std::vector<int>>& table);
bool is_inside_world(float x, float y, float world_width, float world_height);
void draw_back(sf::RenderWindow& window, const std::vector<std::vector<int>>& table, const sf::View& camera);

#endif //BACKGROUND_H
