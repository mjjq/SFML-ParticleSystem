#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <time.h>

struct Particle
{
    sf::Vector2f initialPosition = {0.0f, 0.0f};
    sf::Vector2f position = {0.0f, 0.0f};

    float lifetime;

    int seed;
    int seed2;

    sf::Color color = sf::Color::Red;
};


typedef std::function<void(float, Particle&) > VecFunction;


class ParticleSource
{
    const float MAX_TIME = 1e+10;
    float currTime = 0.0f;

    std::vector<Particle > particles;
    std::vector<sf::Vertex > verts;

    VecFunction pathFunction;

    sf::Vector2f sourcePosition = {0.0f, 0.0f};

public:
    ParticleSource(unsigned int numParticles,
                   float avgLifetime,
                   VecFunction _pathFunction) :
                       pathFunction{_pathFunction}
    {
        srand(time(NULL));
        for(int i=0; i<numParticles; ++i)
        {
            Particle p;
            p.seed = rand();
            p.seed2 = rand();

            p.lifetime = avgLifetime * rand() / RAND_MAX;
            p.position = sourcePosition;
            p.initialPosition = sourcePosition;

            particles.push_back(p);


            sf::Vertex vert({0.0f, 0.0f}, p.color);
            verts.push_back(vert);
        }
    }


    void updateParticles(float dt)
    {
        for(int i=0; i<particles.size(); ++i)
        {
            float newTime = fmodf(currTime + dt, particles[i].lifetime);
            if(newTime < fmodf(currTime, particles[i].lifetime))
            {
                particles[i].seed = rand();
                particles[i].seed2 = rand();
                particles[i].initialPosition = sourcePosition;
                //std::cout << particles[i].seed << " newseed\n";
            }

            pathFunction(newTime, particles[i]);
            verts[i].position = particles[i].position;
            verts[i].color = particles[i].color;
        }

        currTime += dt;
        if(currTime > MAX_TIME)
            currTime = 0.0f;
    }

    void draw(sf::RenderWindow& window, sf::RenderStates& state)
    {
        window.draw(verts.data(), verts.size(), sf::Points, state);
    }

    void setPosition(sf::Vector2f position) { sourcePosition = position; }
};

#endif // PARTICLE_SYSTEM_H
