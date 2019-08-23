#include <iostream>

#include "ParticleSystem.h"

#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window;
    sf::VideoMode mode(800, 800);
    window.create(mode, "test");

    sf::View view;
    view.setCenter({0.0f, 0.0f});
    window.setView(view);

    VecFunction pF = [](float t, Particle& p) {
        float constant = 1.0f * (float)(p.seed - RAND_MAX/2)/(float)RAND_MAX;

        float constant2 = 1.0f * (float)(p.seed2 - RAND_MAX/2)/(float)RAND_MAX;

        float f1 = 20.0f*log(1.0f + 1.0f*t);
        float f2 = 20.0f*log(1.0f + 1.0f*t);
        float x = 1.0f*constant * f1;
        float y = 1.0f*constant2 * f2;

        uint8_t value = 255/(1.0f + 0.1f*t);
        p.color = sf::Color(value, 0, value);
        p.position = sf::Vector2f{x,y} + p.initialPosition;
    };

    VecFunction pF2 = [](float t, Particle& p) {
        float constant = 1.0f * (float)(p.seed - RAND_MAX/2)/(float)RAND_MAX;

        float constant2 = 1.0f * (float)(p.seed2 - RAND_MAX/2)/(float)RAND_MAX;


        float alpha = 0.3f;
        sf::Vector2f g = 1.0f/alpha * sf::Vector2f{0.0f, -1.0f};
        sf::Vector2f v0 = {5.0f*constant, 5.0f*constant2};

        float exp = 1.0f - pow(2.71828, -alpha * t);
        sf::Vector2f f = t * g +  exp * 1.0f/alpha * (v0 - g) + 5.0f*v0;

        float f1 = 20.0f*log(1.0f + 50.0f*t);
        float f2 = 20.0f*log(1.0f + 50.0f*t);
        float x = 1.0f*constant * f1 + 200.0f;
        float y = 1.0f*constant2 * f2;

        float temp = pow(2.71828, - 0.5f * t / p.lifetime);

        p.color = sf::Color(255 * temp, 255 * temp * temp, 255 * pow(temp, 6), 255 * pow(temp, 5) );
        p.position = f + p.initialPosition;
    };

    VecFunction pF3 = [](float t, Particle& p) {
        float constant = 1.0f * (float)(p.seed - RAND_MAX/2)/(float)RAND_MAX;

        float constant2 = 1.0f * (float)(p.seed2 - RAND_MAX/2)/(float)RAND_MAX;

        float x = 20.0f * (constant + 5.0f) * cosf(0.01f*t + 0.5f*3.141f*constant2);
        float y = 20.0f * (constant + 5.0f) * sinf(0.062f*t + 0.5f*3.141f*constant2);

        uint8_t value = 255/(1.0f + 0.2f*t);
        p.color = sf::Color(value, 0, value);
        p.position = sf::Vector2f{x,y} + p.initialPosition;
    };

    ParticleSource pSource(100, 60.0f, pF);

    sf::Shader shader;
    shader.loadFromFile("test.vert", "test.geom", "test.frag");
    sf::RenderStates state(&shader);

    while(window.isOpen())
    {
        sf::Event currEvent;

        while(window.pollEvent(currEvent))
        {
            switch(currEvent.type)
            {
                case(sf::Event::Closed):
                    window.close();
                    break;
                default:
                    break;
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            pSource.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

        window.clear(sf::Color::Black);


        pSource.updateParticles(1.0f);

        pSource.draw(window, &state);

        //window.draw(circle);

        window.display();
        sf::sleep(sf::milliseconds(8));
    }
}
