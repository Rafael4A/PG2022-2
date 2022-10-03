#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"


//Propriedades cesto
const glm::vec2 PLAYER_SIZE(100.0f, 40.0f);
const float PLAYER_SPEED(650.0f);

//Propriedades laranja
const glm::vec2 INITIAL_FALLING_SPEED(0.0f, 300.0f);
const float FALLING_OBJECT_SIZE = 15.5f;

class Game
{
public:
    bool Keys[1024];
    unsigned int Width, Height;
    int COLLISION_COUNT = 1;
    int ORANGE_COUNT = 0;
    // Construtor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // Inicializacao (carrega shaders, texturas)
    void Init();
    // Loop de jogo
    void HandleInput(float dt);
    void Update(float dt);
    void Render();
    //Checa as colisoes
    void CheckCollisions();
    //Reseta o jogo quando a condicao de perda ocorre.
    void ResetPlayer();
};