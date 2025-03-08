#ifndef CHARACTERS_H
#define CHARACTERS_H

class Mage
{
public:
    float X_cord, Y_cord;
    int where, type;
    std::vector<sf::Texture> stand_1, stand_2;
    std::vector<sf::Texture> run_1, run_2;
    std::vector<sf::Texture> attack_1, attack_2;

    sf::Sprite current_sprite;
    size_t frame_counter;
    sf::Clock animation_clock;

    Mage(float x, float y) : X_cord(x), Y_cord(y), where(0), type(0), frame_counter(0) {}

    void loadTextures(int type)
    {
        if(type == 0)
        {
            for (int i = 1; i <= 5; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/BlueMage/mag" + std::to_string(i) + ".png");
                stand_1.push_back(texture);
            }
            for (int i = 1; i <= 5; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/BlueMage/mag" + std::to_string(i) + "1.png");
                stand_2.push_back(texture);
            }
            for (int i = 1; i <= 4; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/BlueMage/run" + std::to_string(i) + ".png");
                run_1.push_back(texture);
            }
            for (int i = 1; i <= 4; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/BlueMage/run" + std::to_string(i) + "1.png");
                run_2.push_back(texture);
            }
            for (int i = 1; i <= 15; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/BlueMage/attack" + std::to_string(i) + ".png");
                attack_1.push_back(texture);
            }
            for (int i = 1; i <= 15; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/BlueMage/1attack" + std::to_string(i) + ".png");
                attack_2.push_back(texture);
            }

            current_sprite.setTexture(stand_1[0]);
        }
        if(type == 1)
        {
            for (int i = 1; i <= 5; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/RedMage/magr" + std::to_string(i) + ".png");
                stand_1.push_back(texture);
            }
            for (int i = 1; i <= 5; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/RedMage/1magr" + std::to_string(i) + ".png");
                stand_2.push_back(texture);
            }
            for (int i = 1; i <= 4; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/RedMage/runr" + std::to_string(i) + ".png");
                run_1.push_back(texture);
            }
            for (int i = 1; i <= 4; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/RedMage/runr" + std::to_string(i) + "1.png");
                run_2.push_back(texture);
            }
            for (int i = 1; i <= 15; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/RedMage/attackr" + std::to_string(i) + ".png");
                attack_1.push_back(texture);
            }
            for (int i = 1; i <= 15; i++)
            {
                sf::Texture texture;
                texture.loadFromFile("Photos/RedMage/1attackr" + std::to_string(i) + ".png");
                attack_2.push_back(texture);
            }

            current_sprite.setTexture(stand_1[0]);
        }

        current_sprite.setPosition(X_cord, Y_cord);
    }

    void move_x(const float dx)
    {
        X_cord = X_cord + dx;
        current_sprite.setPosition(X_cord, Y_cord);
        type = 1;
    }

    void move_y(const float dy)
    {
        Y_cord = Y_cord + dy;
        current_sprite.setPosition(X_cord, Y_cord);
        type = 1;
    }

    void attack()
    {
        type = 2;
    }

    sf::Vector2f pos() const
    {
        return current_sprite.getPosition();
    }

    sf::Vector2f size() const
    {
        return {current_sprite.getGlobalBounds().width, current_sprite.getGlobalBounds().height};
    }

    void update()
    {
        if (type == 1)
        {
            if (animation_clock.getElapsedTime().asMilliseconds() > 100)
            {
                frame_counter = (frame_counter + 1) % run_1.size();
                if (where == 0)
                {
                    current_sprite.setTexture(run_1[frame_counter]);
                }
                else
                {
                    current_sprite.setTexture(run_2[frame_counter]);
                }
                animation_clock.restart();
            }
            type = 0;
        }
        else if (type == 2)
        {
            if (animation_clock.getElapsedTime().asMilliseconds() > 70)
            {
                frame_counter = (frame_counter + 1) % attack_1.size();
                if (where == 0)
                {
                    current_sprite.setTexture(attack_1[frame_counter]);
                }
                else
                {
                    current_sprite.setTexture(attack_2[frame_counter]);
                }
                animation_clock.restart();
            }
            type = 0;
        }
        else
        {
            if (animation_clock.getElapsedTime().asMilliseconds() > 100)
            {
                frame_counter = (frame_counter + 1) % stand_1.size();
                if (where == 0)
                {
                    current_sprite.setTexture(stand_1[frame_counter]);
                }
                else
                {
                    current_sprite.setTexture(stand_2[frame_counter]);
                }
                animation_clock.restart();
            }
        }
    }

    size_t getFrameCounter() const
    {
        return frame_counter;
    }


    void draw(sf::RenderWindow &window) const
    {
        window.draw(current_sprite);
    }

    void setDirection(int dir)
    {
        where = dir;
    }
};

#endif //CHARACTERS_H
