#ifndef COLLISION_H
#define COLLISION_H

class circle_for_collision
{
public:
    sf::CircleShape circle;

    float x, y;

    float radius = 100;

    circle_for_collision(const float dx, const float dy)
    {
        x = dx;
        y = dy;

        circle.setRadius(radius);
        circle.setPosition(sf::Vector2f(x - 2 * radius / 3, y - 2 * radius / 3));
        circle.setFillColor(sf::Color(100, 100, 100, 100));
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(circle);
    }

    void set_position(const float dx, const float dy)
    {
        x = dx;
        y = dy;
        circle.setPosition(sf::Vector2f(x - 2 * radius / 3, y - 2 * radius / 3));
    }

    sf::CircleShape get_circle() const
    {
        return circle;
    }

    sf::Vector2f get_position() const
    {
        return circle.getPosition();
    }
};

#endif //COLLISION_H
