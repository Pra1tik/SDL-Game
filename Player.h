#pragma once
#include "Character.h"
#include <SDL2/SDL.h>
#include "defaultVar.h"
#include <sstream>

class Player : public Character
{
    public:
        Player(SDL_Renderer* renderer);

        void update() override;
        void render(SDL_Rect rect) override;
        void handleInput(SDL_Event& e, float deltaTime);
        void CollisionUpdate (vec offset,int tileRow[], int tiles);
        void animate();
        void reduceLife(int i); //0 for enemyCollision, 1 for arrow Collision
        std::string getLives();

        bool leftFacing = false, rightFacing = true;
        bool shake = false;

    private:
        int mlives = 50;
        float dt = 0;
        bool mAlive = true;
        bool jumpFlag = false;
        bool isJumping = false;
        bool isShooting = false;
        int gravity = 30;
        const int imp = 900;
        const int fall = 0;
        const int maxFall = -750;
        bool falling=false;
        int tileRowPlayerClass[100];
        int count=0;
        vec previousOffset {0,0};
        vec currentFrame{0,0};
        SDL_RendererFlip flip;
        int pTiles;
        int shotTimer = 0;
};