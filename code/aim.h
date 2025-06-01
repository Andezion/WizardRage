#ifndef AIM_H
#define AIM_H

#include <SFML/Graphics.hpp>

float calculate_distance(const sf::Vector2f& point1, const sf::Vector2f& point2);
void draw_aim(sf::RenderWindow& window, const sf::Vector2f& characterPosition, const sf::Vector2f& cursorPosition);

#endif //AIM_H
