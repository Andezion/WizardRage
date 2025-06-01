#ifndef FIGHT_H
#define FIGHT_H
#include <vector>

class Bullet
{
public:
    float x, y, dx, dy, speed, targetX, targetY;
    float startX, startY;
    bool isMoving;

    size_t frame_counter;
    std::vector<sf::Texture> ball_textures;
    sf::Sprite sprite;
    sf::Clock animation_clock;

    Bullet(float X, float Y, float targetX, float targetY)
        : targetX(targetX), targetY(targetY), startX(X), startY(Y), frame_counter(0)
    {
        x = X;
        y = Y;
        dx = 0;
        dy = 0;
        speed = 600;
        isMoving = false;

        sprite.setPosition(x, y);
    }

    sf::Vector2f pos() const
    {
        return sprite.getPosition();
    }

    sf::FloatRect get_bounds() const
    {
        return sprite.getLocalBounds();
    }

    sf::Vector2f size() const
    {
        return {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
    }

    void loadTextures()
    {
        for (int i = 1; i <= 15; i++)
        {
            sf::Texture texture;
            if (texture.loadFromFile("Photos/MagicBallBlue/ball" + std::to_string(i) + ".png"))
            {
                ball_textures.push_back(texture);
            }
        }

        if (!ball_textures.empty())
        {
            sprite.setTexture(ball_textures[0]);
            sprite.setOrigin(ball_textures[0].getSize().x / 2, ball_textures[0].getSize().y / 2);

            sprite.setScale(0.1f, 0.1f);
        }
    }

    void update(float time)
    {
        if (isMoving)
        {
            x += dx * time;
            y += dy * time;

            sprite.setPosition(x, y);

            if (animation_clock.getElapsedTime().asMilliseconds() > 70 && !ball_textures.empty())
            {
                frame_counter = (frame_counter + 1) % ball_textures.size();
                sprite.setTexture(ball_textures[frame_counter]);
                animation_clock.restart();
            }
        }
    }

    void reset()
    {
        isMoving = false;
        dx = 0;
        dy = 0;
    }
};

#endif //FIGHT_H
