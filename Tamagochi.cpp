#include "Header.h"
#include "form.h"
#include "game.h"
#include <iostream>
#include <string>

int main()
{
    // Создание окна 
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default);
    
    // Создание сцены
    game::scene game_scene;
    game::scene menu_scene;

    // Создание объектов для сцены
    form::Button dance(10, 10, 150, 30, L"Танцы");
    form::Button eat(10, 60, 150, 30, L"Кушать");
    form::Button sleep(10, 110, 150, 30, L"Спать");
    form::Button notsleep(10, 160, 150, 30, L"Проснуться");

    form::CircleProgresBar Indicator_hungry(275, 100);
    Indicator_hungry.sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    form::CircleProgresBar Indicator_happines(375, 100);
    Indicator_happines.sprite.setTextureRect(sf::IntRect(50, 0, 50, 50));
    form::CircleProgresBar Indicator_fatigue(475, 100);
    Indicator_fatigue.sprite.setTextureRect(sf::IntRect(100, 0, 50, 50));

    game::Person pers("img/sprites.jpg", 328, 228, 1, 1, false, 3);
    pers.setTextureRect(0, 0, 64, 64);

    // Загружаем объект в сцену
    game_scene.addObj(&dance);
    game_scene.addObj(&eat);
    game_scene.addObj(&sleep);
    game_scene.addObj(&notsleep);
    game_scene.addObj(&pers);
    game_scene.addObj(&Indicator_hungry);
    game_scene.addObj(&Indicator_happines);
    game_scene.addObj(&Indicator_fatigue);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case(sf::Event::Closed):
                window.close();
                break;
            case(sf::Event::MouseButtonPressed):
                switch (event.mouseButton.button)
                {
                case(sf::Mouse::Left):

                    if (dance.select(sf::Mouse::getPosition(window)))
                    {
                        if (!pers.ani_happines) {
                            pers.ani_happines = true;
                            if (pers.p_happines < 100 && !pers.ani_sleep) {
                                pers.p_happines += 10;
                            }
                            Indicator_happines.updatePercent(pers.p_happines);
                        }
                    }

                    if (eat.select(sf::Mouse::getPosition(window)))
                    {
                        if (!pers.ani_eat) {
                            pers.ani_eat = true;
                            if (pers.p_hungry < 100 && !pers.ani_sleep) {
                                pers.p_hungry += 10;
                            }
                            Indicator_hungry.updatePercent(pers.p_hungry);
                        }
                    }

                    if (sleep.select(sf::Mouse::getPosition(window)))
                    {
                        pers.ani_sleep = true;
                    }

                    if (notsleep.select(sf::Mouse::getPosition(window)))
                    {
                        pers.ani_sleep = false;
                        pers.getSprite()->setTextureRect(sf::IntRect(0, 0, 64, 64));
                    }
                    break;
                default:
                    break;
                }
                break;
            case(sf::Event::Resized):
                window.setView(
                    sf::View(
                        sf::Vector2f(event.size.width / 2.0f, event.size.height / 2.0f),
                        sf::Vector2f((float)event.size.width, (float)event.size.height)
                    )
                );
                break;
            default:
                break;
            }
        }

        pers.ffun();
        pers.feat();
        pers.fsleep(&Indicator_fatigue);
        pers.flife(&Indicator_hungry, &Indicator_happines, &Indicator_fatigue);

        window.clear();

        game_scene.draw(window);

        window.display();
        sf::sleep(milliseconds(1));
    }

    return 0;
}