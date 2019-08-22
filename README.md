# SFML-ParticleSystem
Particle system for the SFML graphics library

## Prerequisites

This library uses SFML-2.4.2. It is untested on later versions.

## Usage

#include "ParticleSystem.h" to your project (make sure to add the header file to project settings).

Create a particle system using the ParticleSource constructor

ParticleSource pSource(numParticles, avgParticleLifetime, motionLambdaFunction);

The first two parameters are self-explanatory. The final parameter takes a lambda with paramters float and Particle&. The first parameter of this lambda passes through the current time, the second passes through a reference to a particle.

Within this lambda, the user can define any parametric quantity for position as a function of time. This allows for many types of motion to be defined such as fire (see main.cpp for example). Each particle comes with its own seed generated from an RNG algorithm in order for motion to be randomised.

To update all particle positions belonging to a source, call the member function "ParticleSource::updateParticles" with a specified time delta.

Finally, to draw all particles belonging to a source, call the member function "ParticleSource::draw" with an sf::RenderTarget to be drawn to. 

A particle source may be drawn optionally with a shader to enhance the appearance of a particle source. Shaders can be completely custom defined by the user (see test.frag, test.geom, test.vert).