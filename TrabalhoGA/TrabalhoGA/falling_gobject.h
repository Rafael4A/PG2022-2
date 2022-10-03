#ifndef FALLINGGOBJECT_H
#define FALLINGGOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"



class FallingObject : public GameObject
{
public:
    float   width;
    bool    shouldFall;
    bool    isLeaf;
    // Construtores.
    FallingObject();
    FallingObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);
    // Move laranja
    glm::vec2 Move(float dt, unsigned int window_width);
    // Reseta posicao e velocidade do item
    void      Reset(glm::vec2 position, glm::vec2 velocity);
    void      Teleport(glm::vec2 position);
    void      IncreaseVelocity(int numColl);
};

#endif