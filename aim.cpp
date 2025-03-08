#include "aim.h"
#include <cmath>

float calculate_distance(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    return sqrtf(std::pow(point2.x - point1.x, 2) + std::pow(point2.y - point1.y, 2));
}
void draw_aim(sf::RenderWindow& window, const sf::Vector2f& characterPosition, const sf::Vector2f& cursorPosition)
{
    float distance = calculate_distance(characterPosition, cursorPosition);

    float minRadius = 5.0f;
    float maxRadius = 50.0f;

    float radius = std::clamp(distance / 5.0f, minRadius, maxRadius);

    sf::CircleShape dynamicCircle(radius);
    dynamicCircle.setFillColor(sf::Color::Transparent);
    dynamicCircle.setOutlineColor(sf::Color::White);
    dynamicCircle.setOutlineThickness(1.0f);
    dynamicCircle.setOrigin(radius, radius);
    dynamicCircle.setPosition(cursorPosition.x, cursorPosition.y);

    window.draw(dynamicCircle);
}