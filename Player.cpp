#include "Player.h"


Player::Player(SDL_Renderer* renderer)
{
    //TextureWrapper object
    //std::cout << "B\n";

    mTexture = new TextureWrapper(renderer);
    
    mTexture->loadFromFile("assets/player.png");

    //Set initial position
    setPosition(100, 300);
    setVelocity(10, imp);
    setAccleration(0, 0);

    //std::cout << "B\n";

}

void Player::CollisionUpdate(vec offset,vec tile)
{
    // std::cout<<tile.y<<std::endl;
    // // if(mAcc.y == 1)
    // // {
    // //     mVel.y = (mVel.y - gravity);
    // //     mPos.y -= (mVel.y * dt); 
    // // }

    // if(mPos.y > offset.y+300)  //this needs to be change after calculating collisions
    if(offset.x==0)  //this needs to be change after calculating collisions
    {
        
        mVel.y = imp;
        mAcc.y = 0;
        mPos.y += (offset.y-25);
    }
    // if (tile.y != 0)
    // {
    //     mPos.y= tile.y*50+290-110;
    // }
    if(offset.y ==0)  //this needs to be change after calculating collisions
    {
        mVel.y = imp;
        mAcc.y = 0;
        mPos.y = 600;
    }
    // mPos.y += offset.y*dt;
    mPos.x += offset.x;
}


void Player::update(int tileNum)
{

    // Update the positions
    if(mAcc.y == 1)
    {
        mVel.y = (mVel.y - gravity);
        mPos.y -= mVel.y * dt; 
    }

    if(mPos.y > 600)  //this needs to be change after calculating collisions
    {
        mVel.y = imp;
        mAcc.y = 0;
        mPos.y = 600;
    }
    

    mPos.x += mAcc.x * mVel.x;
}


void Player::render()
{
    //render the texture
    mTexture->render(mPos.x, mPos.y);
}


void Player::handleInput(SDL_Event& e, float deltaTime)
{

    dt = deltaTime;

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if(state[SDL_SCANCODE_RIGHT])
    {
        mAcc.x = 1;
    }
    else if(!state[SDL_SCANCODE_RIGHT])
    {
        mAcc.x = 0;
    }


    if(state[SDL_SCANCODE_LEFT])
    {
        mAcc.x = -1;
    }
    else if(state[SDL_SCANCODE_LEFT])
    {
        mAcc.x = 0;
    }

    if(jumpFlag == false && state[SDL_SCANCODE_SPACE])
    {
        mAcc.y = 1;
        jumpFlag = true;
    }
    else if(!state[SDL_SCANCODE_SPACE])
    {
        jumpFlag = false;
    }

}