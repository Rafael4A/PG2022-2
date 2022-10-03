#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include <GLFW/glfw3.h>
#include "falling_gobject.h";
#include "game_object.h";
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <Windows.h>



SpriteRenderer* Renderer;
GameObject* Player;
FallingObject* Orange;

Game::Game(unsigned int width, unsigned int height)
    : Keys(), Width(width), Height(height)
{}

Game::~Game()
{
    delete Renderer;
    delete Player;
    delete Orange;
}

void Game::Init()
{
    // Carrega shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    // Configura shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    Shader myShader;
    myShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(myShader);

    // Carrega texturas
    ResourceManager::LoadTexture("textures/background.png", true, "background");
    ResourceManager::LoadTexture("textures/leaf.png", true, "leaf");
    ResourceManager::LoadTexture("textures/orange.png", true, "orange");
    ResourceManager::LoadTexture("textures/basket.png", true, "basket");

    //Cria objetos
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("basket"));
    glm::vec2 orangePos = glm::vec2((rand() % this->Width + 1) - FALLING_OBJECT_SIZE, FALLING_OBJECT_SIZE);
    Orange = new FallingObject(orangePos, FALLING_OBJECT_SIZE, INITIAL_FALLING_SPEED, ResourceManager::GetTexture("orange"));

    MessageBox(0, _T("Bem vindo ao jogo das laranjas!\nO objetivo é pegar todas as laranjas que cairem da árvore, sem pegar nenhuma das folhas que também podem cair!\nPara iniciar o jogo basta clicar \"Enter\" após fechar essa mensagem. Para controlar o cesto, basta utilizar as setas do teclado!"), _T("Iniciar jogo"), MB_OK | MB_ICONINFORMATION);

}

void Game::Update(float dt)
{
    //Move item
    Orange->Move(dt, this->Width);
    //Checa colisoes
    this->CheckCollisions();
    //Depois de 3 laranjas, cai uma folha
    Orange->isLeaf = COLLISION_COUNT % 4 == 0;
    
    
    //Reinicia caso laranja cair
    if (Orange->isLeaf == false && Orange->Position.y >= this->Height)
        this->ResetPlayer();
    
    //Segue jogo caso folha caia
    if (Orange->Position.y >= this->Height && Orange->isLeaf == true) {
        glm::vec2 orangePos = glm::vec2((rand() % this->Width + 1) - FALLING_OBJECT_SIZE, FALLING_OBJECT_SIZE);
        COLLISION_COUNT += 1;
        Orange->Teleport(orangePos);
    }
}

void Game::HandleInput(float dt)
{
    float velocity = PLAYER_SPEED * dt;
    if (this->Keys[GLFW_KEY_LEFT])
    {
        //Move cesto para esquerda sem sair da tela
        if (Player->Position.x >= 0.0f)
            Player->Position.x -= velocity;
        
    }
    if (this->Keys[GLFW_KEY_RIGHT])
    {
        //Move cesto para direita sem sair da tela
        if (Player->Position.x <= this->Width - Player->Size.x)
            Player->Position.x += velocity;
        
    }
    //Inicia jogo com "Enter"
    if (this->Keys[GLFW_KEY_ENTER])
        Orange->shouldFall = true;
}

void Game::Render()
{
    //Define textura e renderiza background
    Texture2D background;
    background = ResourceManager::GetTexture("background");
    Renderer->DrawSprite(background, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);


    //Define textura folha
    if (Orange->isLeaf == true) {
        Orange->Sprite = ResourceManager::GetTexture("leaf");
    }
    //Define textura laranja
    else {
        Orange->Sprite = ResourceManager::GetTexture("orange");
    }
    //Renderiza objetos
    Orange->Draw(*Renderer);
    Player->Draw(*Renderer);
}


void Game::ResetPlayer()
{
    //Aviso de fim de jogo
    std::string mensagem = "Fim de jogo!\nVoce coletou: " + std::to_string(ORANGE_COUNT) + " laranjas.\n";
    mensagem += "Para recomecar, basta clicar em ok e apertar \"Enter\"";
    LPWSTR ws = new wchar_t[mensagem.size() + 1];
    copy(mensagem.begin(), mensagem.end(), ws);
    ws[mensagem.size()] = 0; // zero at the end
    MessageBox(0, ws, _T("Fim de jogo"), MB_OK | MB_ICONINFORMATION);

    //Reseta cesto, laranja e colisões
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    glm::vec2 orangePos = glm::vec2((rand() % this->Width + 1) - FALLING_OBJECT_SIZE, FALLING_OBJECT_SIZE);
    Orange->Reset(orangePos, INITIAL_FALLING_SPEED);
    COLLISION_COUNT = 1;
    ORANGE_COUNT = 0;
}


bool CheckObjectsCollision(GameObject& one, GameObject& two)
{
    // Colisão do x
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // Colisão do y
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;

    return collisionX && collisionY;
}

void Game::CheckCollisions()
{
    //Caso jogador pegue laranja
    bool collided = CheckObjectsCollision(*Orange, *Player);
    if (collided && Orange->isLeaf == false) {
        glm::vec2 orangePos = glm::vec2((rand() % this->Width + 1) - FALLING_OBJECT_SIZE, FALLING_OBJECT_SIZE);
        Orange->IncreaseVelocity(COLLISION_COUNT);
        COLLISION_COUNT += 1;
        ORANGE_COUNT += 1;
        
        Orange->Teleport(orangePos);
    }
    //Caso jogador pegue folha
    if (collided && Orange->isLeaf == true) {
        ResetPlayer();
    }
}