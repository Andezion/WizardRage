#ifndef INFO_H
#define INFO_H

inline float camera_window_width = 300;
inline float camera_window_height = 200;

class info_enemy
{
public:
    double health_size;
    double armor_size;

    float x;
    float y;

    sf::RectangleShape health;
    sf::RectangleShape armor;

    sf::RectangleShape background_health;
    sf::RectangleShape background_armor;

    sf::RectangleShape background;

    info_enemy(const int n1, const int n2, float x_cord, float y_cord) : health_size(n1), armor_size(n2), x(x_cord), y(y_cord)
    {
        health = create_bar(health_size, sf::Color::Red, {x - 15.0f, y - 20.0f}, 2);
        armor = create_bar(armor_size, sf::Color(128, 128, 128), {x - 15.0f, y - 10.0f}, 2);

        background_health = create_bar(100, sf::Color::White, {x - 15.0f, y - 20.0f}, 2);
        background_armor = create_bar(100, sf::Color::White, {x - 15.0f, y - 10.0f}, 2);

        background = create_bar(110, sf::Color(237, 208, 145), {x - 20.0f, y - 25.0f}, 1);
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(background);

        window.draw(background_health);
        window.draw(background_armor);

        window.draw(health);
        window.draw(armor);
    }

    void update_x(const float dx)
    {
        x = x + dx;
        background.setPosition(x - 20.0f, y - 25.0f);

        background_health.setPosition(x - 15.0f, y - 20.0f);
        background_armor.setPosition(x - 15.0f, y - 10.0f);

        health.setPosition(x - 15.0f, y - 20.0f);
        armor.setPosition(x - 15.0f, y - 10.0f);
    }
    void update_y(const float dy)
    {
        y = y + dy;
        background.setPosition(x - 20.0f, y - 25.0f);

        background_health.setPosition(x - 15.0f, y - 20.0f);
        background_armor.setPosition(x - 15.0f, y - 10.0f);

        health.setPosition(x - 15.0f, y - 20.0f);
        armor.setPosition(x - 15.0f, y - 10.0f);
    }

    void update_health(const double amount)
    {
        if(health_size - amount > 0 && health_size - amount <= 100)
        {
            health_size = health_size - amount;
        }

        health.setSize(sf::Vector2f(static_cast<float>(health_size), health.getSize().y));
    }
    void update_armor(const double amount)
    {
        if(armor_size - amount > 0 && armor_size - amount <= 100)
        {
            armor_size = armor_size - amount;
        }
        armor.setSize(sf::Vector2f(static_cast<float>(armor_size), armor.getSize().y));
    }
private:
    static sf::RectangleShape create_bar(const int size, const sf::Color color, const sf::Vector2f position, int type)
    {
        sf::RectangleShape bar;
        if(type == 1)
        {
            bar.setSize(sf::Vector2f(static_cast<float>(size), 25.0f));
        }
        else
        {
            bar.setSize(sf::Vector2f(static_cast<float>(size), 5.0f));
        }

        bar.setPosition(position);
        bar.setFillColor(color);

        bar.setOutlineColor(sf::Color::Black);
        bar.setOutlineThickness(1);

        return bar;
    }
};

class info
{
public:
    int health_size;
    int armor_size;
    double mana_size;
    double stamina_size;

    sf::RectangleShape health;
    sf::RectangleShape armor;
    sf::RectangleShape mana;
    sf::RectangleShape stamina;

    sf::RectangleShape background_health;
    sf::RectangleShape background_armor;
    sf::RectangleShape background_mana;
    sf::RectangleShape background_stamina;

    sf::RectangleShape background;

    info(const int n1, const int n2, const int n3, const int n4)
        : health_size(n1), armor_size(n2), mana_size(n3), stamina_size(n4)
    {
        health = create_bar(health_size, sf::Color::Red, {10.0f, 10.0f}, 2);
        armor = create_bar(armor_size, sf::Color(128, 128, 128), {10.0f, 20.0f}, 2);
        mana = create_bar(mana_size, sf::Color::Blue, {10.0f, 30.0f}, 2);
        stamina = create_bar(stamina_size, sf::Color::Green, {10.0f, 40.0f}, 2);

        background_health = create_bar(100, sf::Color::White, {10.0f, 10.0f}, 2);
        background_armor = create_bar(100, sf::Color::White, {10.0f, 20.0f}, 2);
        background_mana = create_bar(100, sf::Color::White, {10.0f, 30.0f}, 2);
        background_stamina = create_bar(100, sf::Color::White, {10.0f, 40.0f}, 2);

        background = create_bar(110, sf::Color(237, 208, 145), {5.0f, 5.0f}, 1);
    }

    void draw(sf::RenderWindow &window) const
    {
        window.draw(background);

        window.draw(background_health);
        window.draw(background_armor);
        window.draw(background_mana);
        window.draw(background_stamina);

        window.draw(health);
        window.draw(armor);
        window.draw(mana);
        window.draw(stamina);
    }

    void update_stamina(const double amount)
    {
        if(stamina_size - amount > 0 && stamina_size - amount <= 100)
        {
            stamina_size = stamina_size - amount;
        }

        stamina.setSize(sf::Vector2f(static_cast<float>(stamina_size), stamina.getSize().y));
    }
    void update_mana(const double amount)
    {
        if(mana_size - amount > 0 && mana_size - amount <= 100)
        {
            mana_size = mana_size - amount;
        }
        mana.setSize(sf::Vector2f(static_cast<float>(mana_size), mana.getSize().y));
    }
private:
    static sf::RectangleShape create_bar(const int size, const sf::Color color, const sf::Vector2f position, int type)
    {
        sf::RectangleShape bar;
        if(type == 1)
        {
            bar.setSize(sf::Vector2f(static_cast<float>(size), 45.0f));
        }
        else
        {
            bar.setSize(sf::Vector2f(static_cast<float>(size), 5.0f));
        }

        bar.setPosition(position);
        bar.setFillColor(color);

        bar.setOutlineColor(sf::Color::Black);
        bar.setOutlineThickness(1);

        return bar;
    }
};

#endif //INFO_H
