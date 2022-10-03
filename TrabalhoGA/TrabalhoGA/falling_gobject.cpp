#include "falling_gobject.h"


FallingObject::FallingObject()
    : GameObject(), width(12.5f), shouldFall(false), isLeaf(false) { }

FallingObject::FallingObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f), velocity), width(radius), shouldFall(false), isLeaf(false) { }

glm::vec2 FallingObject::Move(float dt, unsigned int window_width)
{
    // Caso jogo estja iniciado
    if (this->shouldFall)
    {
        // Move laranja
        this->Position += this->Velocity * dt;
        this->Rotation += 150 * dt;

    }
    return this->Position;
}

// Reseta laranja
void FallingObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->shouldFall = false;
    this->isLeaf = false;
    this->Rotation = 0;
}

//Teleporta laranja
void FallingObject::Teleport(glm::vec2 position) {

    this->Position = position;
}

//Acelera laranja
void FallingObject::IncreaseVelocity(int numColl) {
    this->Velocity += glm::vec2(0.0f, numColl);
}