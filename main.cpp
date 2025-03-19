#include <complex>
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include "background.h"
#include "characters.h"
#include "fight.h"
#include "info.h"
#include "aim.h"
#include "collision.h"

int switcher_for_bots(const double dist)
{
    if(dist > 200 && dist < 500)
    {
        return 2;
    }
    if(dist <= 200)
    {
        return 1;
    }
    return 0;
}
double is_near(const Mage& object1, const Mage& object2)
{
    double dist = sqrt(pow(object2.X_cord - object1.X_cord, 2) + pow(object2.Y_cord - object1.Y_cord, 2));

    return dist;
}



float enemy_x = 2000;
float enemy_y = 2000;

float enemy_stat_health = 100.0f;
float enemy_stat_armor = 100.0f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "MiddleEarth");
 
    Mage character(1100, 1100);
    character.loadTextures(0);
    info info(100, 100, 100, 100);

    Mage enemy(enemy_x, enemy_y);
    enemy.loadTextures(1);
    info_enemy info_enemy(enemy_stat_health, enemy_stat_armor, enemy.X_cord, enemy.Y_cord);

    sf::View camera(sf::FloatRect(0, 0, 1200, 800));
    camera.setCenter(character.X_cord, character.Y_cord);
    circle_for_collision for_player(600 + (character.X_cord - camera.getCenter().x),
                                  400 + (character.Y_cord - camera.getCenter().y));

    int world = 130;
    float full_world = static_cast<float>(world) * 40;

    std::vector table(world, std::vector<int>(world));
    for (int i = 0; i < 130; i++)
    {
        for (int j = 0; j < 130; j++)
        {
            if(i == 0 || j == 0 || i == 129 || j == 129)
            {
                table[i][j] = 4 + rand() % 5;
            }
            else if(i == 1 || j == 1 || i == 128 || j == 128)
            {
                table[i][j] = 3 + rand() % 5;
            }
            else if(i == 2 || j == 2 || i == 127 || j == 127)
            {
                table[i][j] = 2 + rand() % 5;
            }
            else if(i == 3 || j == 3 || i == 126 || j == 126)
            {
                table[i][j] = 1 + rand() % 5;
            }
            else
            {
                table[i][j] = rand() % 5;
            }
        }
    }

    sf::Font text;
    text.loadFromFile("letters.ttf");
    sf::Text coordinates;

    coordinates.setFont(text);
    coordinates.setString("");

    coordinates.setCharacterSize(20);
    coordinates.setFillColor(sf::Color::White);

    sf::Clock clock_for_bullet;
    std::vector<Bullet> bullets;

    sf::Clock hold;

    float targetX;
    float targetY;

    while (window.isOpen())
    {
        float time = clock_for_bullet.restart().asSeconds();

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q))
            {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (info.mana_size > 10 && hold.getElapsedTime().asMilliseconds() > 700)
                {
                    info.update_mana(0.05);

                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

                    targetX = pos.x;
                    targetY = pos.y;

                    Bullet bullet(600 + (character.X_cord - camera.getCenter().x),
                                  400 + (character.Y_cord - camera.getCenter().y),
                                  targetX, targetY);

                    float distance = std::sqrt((targetX - bullet.x) * (targetX - bullet.x) +
                                               (targetY - bullet.y) * (targetY - bullet.y));

                    bullet.dx = (targetX - bullet.x) / distance * bullet.speed;
                    bullet.dy = (targetY - bullet.y) / distance * bullet.speed;

                    bullet.isMoving = true;

                    bullet.loadTextures();
                    bullets.push_back(bullet);

                    hold.restart();
                }
            }
        }

        for (auto &bullet : bullets)
        {
            if (bullet.isMoving)
            {
                float dist = std::sqrt((bullet.x - bullet.startX) * (bullet.x - bullet.startX) +
                                       (bullet.y - bullet.startY) * (bullet.y - bullet.startY));

                if (dist > 500.0f)
                {
                    bullet.isMoving = false;
                }

                float distance = std::sqrt((targetX - bullet.x) * (targetX - bullet.x) +
                                           (targetY - bullet.y) * (targetY - bullet.y));

                /*if(is_hit(enemy, bullet))
                {
                    info_enemy.update_health(0.1);
                }*/

                if (distance < 1.0f)
                {
                    bullet.isMoving = false;
                }
            }

            bullet.update(time);
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                             [](const Bullet& bullet)
                             {
                                 return !bullet.isMoving;
                             }),
              bullets.end());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            character.setDirection(0);
            if(is_inside_world(character.X_cord + 0.5f, character.Y_cord, full_world, full_world)
                && complex_world_checker(character.X_cord + 0.5f, character.Y_cord, table)
                && info.stamina_size > 1)
            {
                character.move_x(0.5);
            }
            for_player.set_position(600 + (character.X_cord - camera.getCenter().x),
                                  400 + (character.Y_cord - camera.getCenter().y));
            info.update_stamina(0.02);
            info.update_mana(-0.05);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            character.setDirection(1);
            if(is_inside_world(character.X_cord - 0.5f, character.Y_cord, full_world, full_world)
                && complex_world_checker(character.X_cord - 0.5f, character.Y_cord, table)
                && info.stamina_size > 1)
            {
                character.move_x(-0.5);
            }
            for_player.set_position(600 + (character.X_cord - camera.getCenter().x),
                                  400 + (character.Y_cord - camera.getCenter().y));
            info.update_stamina(0.02);
            info.update_mana(-0.05);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            character.setDirection(0);
            if(is_inside_world(character.X_cord, character.Y_cord - 0.5f, full_world, full_world)
                && complex_world_checker(character.X_cord, character.Y_cord - 0.5f, table)
                && info.stamina_size > 1)
            {
                character.move_y(-0.5);
            }
            for_player.set_position(600 + (character.X_cord - camera.getCenter().x),
                                  400 + (character.Y_cord - camera.getCenter().y));
            info.update_stamina(0.02);
            info.update_mana(-0.05);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            character.setDirection(1);
            if(is_inside_world(character.X_cord, character.Y_cord + 0.5f, full_world, full_world)
                && complex_world_checker(character.X_cord, character.Y_cord + 0.5f, table)
                && info.stamina_size > 1)
            {
                character.move_y(0.5);
            }
            for_player.set_position(600 + (character.X_cord - camera.getCenter().x),
                                  400 + (character.Y_cord - camera.getCenter().y));
            info.update_stamina(0.02);
            info.update_mana(-0.05);
        }

        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(info.mana_size > 10)
            {

                character.attack();
            }
            info.update_mana(0.05);
            info.update_stamina(-0.04);
        }
        else
        {
            info.update_stamina(-0.04);
            info.update_mana(-0.05);
        }


        double dist = is_near(character, enemy);
        switch (switcher_for_bots(dist))
        {
            case 2:
                if(character.X_cord > enemy.X_cord)
                {
                    enemy.setDirection(0);
                }
                if(character.X_cord < enemy.X_cord)
                {
                    enemy.setDirection(1);
                }
                if(character.X_cord > enemy.X_cord &&
                is_inside_world(enemy.X_cord, enemy.Y_cord, full_world, full_world)
                && complex_world_checker(enemy.X_cord, enemy.Y_cord, table))
                {
                    enemy.setDirection(0);
                    enemy.move_x(0.1);
                    info_enemy.update_x(0.1);
                }
                if(character.Y_cord > enemy.Y_cord &&
                is_inside_world(enemy.X_cord, enemy.Y_cord, full_world, full_world)
                && complex_world_checker(enemy.X_cord, enemy.Y_cord, table))
                {
                    enemy.move_y(0.1);
                    info_enemy.update_y(0.1);
                }
                if(character.X_cord < enemy.X_cord &&
                is_inside_world(enemy.X_cord, enemy.Y_cord, full_world, full_world)
                && complex_world_checker(enemy.X_cord, enemy.Y_cord, table))
                {
                    enemy.setDirection(1);
                    enemy.move_x(-0.1);
                    info_enemy.update_x(-0.1);
                }
                if(character.Y_cord < enemy.Y_cord &&
                is_inside_world(enemy.X_cord, enemy.Y_cord, full_world, full_world)
                && complex_world_checker(enemy.X_cord, enemy.Y_cord, table))
                {
                    enemy.move_y(-0.1);
                    info_enemy.update_y(-0.1);
                }
                break;
            case 1:
                if(character.X_cord > enemy.X_cord)
                {
                    enemy.setDirection(0);
                }
                if(character.X_cord < enemy.X_cord)
                {
                    enemy.setDirection(1);
                }
                enemy.attack();
                break;
            default:
                break;
        }

        character.update();
        enemy.update();

        coordinates.setString("X - " + std::to_string(static_cast<int>(character.X_cord)) +
                          " Y - " + std::to_string(static_cast<int>(character.Y_cord)));

        float frame_left = camera.getCenter().x - camera_window_width / 2;
        float frame_right = camera.getCenter().x + camera_window_width / 2;
        float frame_top = camera.getCenter().y - camera_window_height / 2;
        float frame_bottom = camera.getCenter().y + camera_window_height / 2;

        if (character.X_cord < frame_left)
        {  
            camera.setCenter(character.X_cord + camera_window_width / 2, camera.getCenter().y);
        }
        else if (character.X_cord > frame_right)
        {
            camera.setCenter(character.X_cord - camera_window_width / 2, camera.getCenter().y);
        }

        if (character.Y_cord < frame_top)
        {
            camera.setCenter(camera.getCenter().x, character.Y_cord + camera_window_height / 2);
        }
        else if (character.Y_cord > frame_bottom)
        {
            camera.setCenter(camera.getCenter().x, character.Y_cord - camera_window_height / 2);
        }

        window.setView(camera);

        window.clear(sf::Color::Black);

        draw_back(window, table, camera);
        character.draw(window);
        enemy.draw(window);
        info_enemy.draw(window);

        sf::Vector2i cursorPosition = sf::Mouse::getPosition(window);
        if (sf::Vector2f worldPosition = window.mapPixelToCoords(cursorPosition); worldPosition.x > character.X_cord)
        {
            character.setDirection(0);
        }
        else
        {
            character.setDirection(1);
        }
        draw_aim(window, sf::Vector2f(character.X_cord, character.Y_cord), window.mapPixelToCoords(cursorPosition));

        window.setView(window.getDefaultView());
        coordinates.setPosition(1020, 770);

        info.draw(window);

        window.draw(coordinates);

        for (const auto &bullet : bullets)
        {
            if (bullet.isMoving)
            {
                window.draw(bullet.sprite);
            }
        }

        for_player.draw(window);

        window.display();
    }

    return 0;
}
