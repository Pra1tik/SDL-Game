#include "game.h"
#include "Player.h"
#include "collider.h"
#include "StartScreen.h"
#include "SelectScreen.h"
#include "InstructionScreen.h"
#include "PauseScreen.h"
#include "Level.h"

bool Game::init(const char* title,int xpos, int ypos, int height, int width, bool flags)
{
   
    Uint32 windowState;
    if (!flags)
    {
        windowState=SDL_WINDOW_SHOWN;
    }
    else
    {
        height = SDL_WINDOW_FULLSCREEN;
        width = SDL_WINDOW_FULLSCREEN;
        windowState=SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING)>=0){
        pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,windowState);
        if(pWindow!=0){
            pRenderer=SDL_CreateRenderer(pWindow,-1,0);
            if (pRenderer!=0){
                SDL_SetRenderDrawColor(pRenderer,100,190,150,255);

                if (TTF_Init() == -1)
                {
                    std::cout << "Error initializing ttf" << TTF_GetError() << std::endl;
                    return false;
                }

                //Level object
                level1 = new Level("graphics/level1.txt", pRenderer, 1);
                level2 = new Level("graphics/level2.txt", pRenderer, 1);
                currentLevel = level1;

                //Initialize font
                TTF_Font* font = TTF_OpenFont("graphics/Fonts/pacifico/Pacifico.ttf",60);
                healthTexture = new TextureWrapper(pRenderer, font);
                levelCompleteTexture = new TextureWrapper(pRenderer, font);
                killCountTexture = new TextureWrapper(pRenderer, font);
            }
            else{
                std::cout << "Error " <<SDL_GetError()<<std::endl;
                return false;
            }
        }
        else{
            return false;
        }
        player = new Player(pRenderer);
        pCollider= new collider();
        tCollider= new collider();
        startScreen = new StartScreen(pRenderer);
        selectScreen = new SelectScreen(pRenderer);
        controls = new InstructionScreen(pRenderer);
        paused = new PauseScreen(pRenderer);
        runGame= true;
        currentGameState = START_SCREEN;

        //For enemy
        enemies = new Enemy(pRenderer, vec{64, 1536-52}, vec{64, 640});

        //Initialize enemy
        enemy1.push_back(new Enemy(pRenderer, vec{456, 400}, vec{456, 886}));
        enemy1.push_back(new Enemy(pRenderer, vec{1413, 208}, vec{1413, 1568}));
        enemy1.push_back(new Enemy(pRenderer, vec{1429, 784}, vec{1429, 1694}));
        enemy1.push_back(new Enemy(pRenderer, vec{1879, 1552}, vec{1879, 2579}));
        enemy1.push_back(new Enemy(pRenderer, vec{1868, 400}, vec{1868, 2088}));
        enemy1.push_back(new Enemy(pRenderer, vec{72, 1488}, vec{72, 976}));
        enemy1.push_back(new Enemy(pRenderer, vec{402, 1168}, vec{402, 542}));
        enemy1.push_back(new Enemy(pRenderer, vec{1417, 1232}, vec{1417, 1737}));

        enemy1a.push_back(new Enemy2(pRenderer, vec{2325, 208}));
        enemy1a.push_back(new Enemy2(pRenderer, vec{2708, 400}));
        enemy1a.push_back(new Enemy2(pRenderer, vec{2158, 1040}));
        enemy1a.push_back(new Enemy2(pRenderer, vec{2158, 1232}));
        enemy1a.push_back(new Enemy2(pRenderer, vec{72, 912}));
        enemy1a.push_back(new Enemy2(pRenderer, vec{72, 1168}));
        enemy1a.push_back(new Enemy2(pRenderer, vec{888, 400}));
        enemy1a.push_back(new Enemy2(pRenderer, vec{1598, 208}));
        enemy1a.push_back(new Enemy2(pRenderer, vec{2108, 400}));
        enemy1a.push_back(new Enemy2(pRenderer, vec{3058, 912}));
        enemy1a.push_back(new Enemy2(pRenderer, vec{3175, 1296}));

        enemy2.push_back(new Enemy(pRenderer, vec{305, 3024}, vec{305,560}));
        enemy2.push_back(new Enemy(pRenderer, vec{633, 2704}, vec{633, 798}));
        enemy2.push_back(new Enemy(pRenderer, vec{323, 2512}, vec{323, 553}));
        enemy2.push_back(new Enemy(pRenderer, vec{1798, 2128}, vec{1798, 1913}));
        enemy2.push_back(new Enemy(pRenderer, vec{72, 208}, vec{72, 252}));
        enemy2.push_back(new Enemy(pRenderer, vec{372, 208}, vec{372, 552}));
        enemy2.push_back(new Enemy(pRenderer, vec{652, 208}, vec{652, 832}));
        enemy2.push_back(new Enemy(pRenderer, vec{932, 208}, vec{208, 1080}));
        
        enemy2a.push_back(new Enemy2(pRenderer, vec{500, 2832}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{888, 2704}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{768, 2320}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{878, 2320}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{1018, 2192}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{1308, 2000}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{1488, 2000}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{2297, 2064}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{3018, 1936}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{3098, 1936}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{3200, 1424}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{1725, 592}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{1085, 208}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{2485, 464}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{2805, 656}));
        enemy2a.push_back(new Enemy2(pRenderer, vec{2872, 1040}));


        //For bullet
        playerBullet = new bullet;
        bulletTexture = new TextureWrapper(pRenderer);
        bulletTexture->loadFromFile("graphics/newBullet.png");

        return true;
    }

    return false;
}
void Game::render()
{
    std::string str;
    std::stringstream ss;
    ss << killCount;
    ss >> str;
    enemyDead = enemies->dead;
    SDL_RenderClear(pRenderer);
    switch (currentGameState)
    {
        case START_SCREEN:
            startScreen->render();
            break;
        case GAME_SCREEN:
            currentLevel->render();
            healthTexture->loadFromRenderedText("LIVES  : " + player->getLives(),color);
            healthTexture->render(10, 10);
            killCountTexture->loadFromRenderedText("KillCount  : " + str,color);
            killCountTexture->render(WindowWidth-killCountTexture->getWidth()-10, 10);
            player->render(currentLevel->camera);

            if(levelNum == 1)
            {
                for(auto it = enemy1.begin(); it != enemy1.end(); it++)
                {
                    (*it)->render(currentLevel->camera);
                }
                for(auto it = enemy1a.begin(); it != enemy1a.end(); it++)
                {
                    (*it)->render(currentLevel->camera, player->getPosition());                
                }

            }
            else if (levelNum == 2)
            {
                for(auto it = enemy2.begin(); it != enemy2.end(); it++)
                {
                    (*it)->render(currentLevel->camera);
                }
                for(auto it = enemy2a.begin(); it != enemy2a.end(); it++)
                {
                    (*it)->render(currentLevel->camera, player->getPosition());                
                }
            }
            
            if(playerBullet->bulletAlive)
            {
                bulletTexture->render(playerBullet->bulletPos.x - currentLevel->camera.x, playerBullet->bulletPos.y - currentLevel->camera.y);
            }

            

                if(levelNum == 1 && killCount >= enemy1.size() + enemy1a.size())
                {
                    levelCompleteTexture->loadFromRenderedText("Level 1 complete", color);
                    levelCompleteTexture->render(WindowWidth/2-levelCompleteTexture->getWidth()/2, WindowHeight/2-levelCompleteTexture->getHeight()/2);
                    SDL_RenderPresent(pRenderer);         
                    SDL_Delay(1000);
                    levelNum = 2;
                    currentLevel = level2;
                    killCount = 0;

                    player->setPosition(100, 3024);
                }
                else if(levelNum == 2 && killCount >= enemy2.size() + enemy2a.size())
                {
                    //Game over
                    levelCompleteTexture->loadFromRenderedText("Game completed", color);
                    levelCompleteTexture->render(WindowWidth/2-levelCompleteTexture->getWidth()/2, WindowHeight/2-levelCompleteTexture->getHeight()/2);
                    SDL_RenderPresent(pRenderer);         
                    SDL_Delay(1000);
                    killCount = 0;
                }
            

            break;
        case SELECT_SCREEN:
            selectScreen->render();
            break;
        case INSTRUCTIONS_SCREEN:
            controls->render();
            break;
        case PAUSE_SCREEN:
            paused->render();
            break;
        default:
            break;
    };
    SDL_RenderPresent(pRenderer);
}

void Game::update()
{
    enemyDead = enemies->dead;
    switch (currentGameState)
    {
        case (GAME_SCREEN):
            player->animate();
            player->update();
            currentLevel->update(player->getPosition(),player->getTexture());
            // if (!enemyDead)
            // {
            //     enemies->update(player->getPosition());
            // }
            // else
            // {
            //     enemies->~Enemy();
            // }
            if (player->shake)
            {
                currentLevel->shake = true;
            }
            else
            {
                currentLevel->shake = false;
            }
            
            int enemyUpdateValue;
            // enemyUpdateValue = enemies->update(player->getPosition(),{playerBullet->bulletPos.x,playerBullet->bulletPos.y, bulletTexture->getWidth(), bulletTexture->getHeight()}, playerBullet->bulletAlive);
            
            if(levelNum == 1)
            {
                for(auto it = enemy1.begin(); it != enemy1.end(); it++)
                {
                    if(playerBullet->bulletAlive && !(*it)->dead)
                    {
                        playerBullet->bulletAlive = !((*it)->bulletEnemyCollision({playerBullet->bulletPos.x,playerBullet->bulletPos.y, bulletTexture->getWidth(), bulletTexture->getHeight()}));
                        if(!playerBullet->bulletAlive) killCount++;
                    }
                    if(!(*it)->dead)
                    {
                        enemyUpdateValue = (*it)->update(player->getPosition());
                        if (enemyUpdateValue == 3)
                        {
                            player->reduceLife(0);
                        }
                    
                    }
                    
                }

                for(auto it = enemy1a.begin(); it != enemy1a.end(); it++)
                {
                    if(playerBullet->bulletAlive && !(*it)->dead)
                    {
                        playerBullet->bulletAlive = !((*it)->bulletEnemyCollision({playerBullet->bulletPos.x,playerBullet->bulletPos.y, bulletTexture->getWidth(), bulletTexture->getHeight()}));
                        if(!playerBullet->bulletAlive) killCount++;
                        
                    }
                    if(!(*it)->dead)
                    {
                        enemyUpdateValue = (*it)->update(player->getPosition());
                        if (enemyUpdateValue == 3)
                        {
                            player->reduceLife(0);
                        }

                        if((*it)->arrowPlayerCollision(SDL_Rect{player->getPosition().x, player->getPosition().y, playerWidth, playerHeight}))
                        {
                            player->reduceLife(1);
                        }

                //         if((*it)->arrow1.arrowAlive)
                //         {
                            
                //             if((*it)->arrow1.arrowtPos.x > currentLevel->camera.x + WindowWidth)
                //             {
                //                 (*it)->arrow1.arrowAlive = false;
                //             } 
                //             else
                //             {
                //                 int arrowX = (*it)->arrow1.arrowtPos.x / (currentLevel->tileWidth * currentLevel->scale);
                //                 int arrowY = (*it)->arrow1.arrowtPos.x / (currentLevel->tileHeight * currentLevel->scale);
                //                 SDL_Rect arrowRect = {(*it)->arrow1.arrowtPos.x, (*it)->arrow1.arrowtPos.x, (*it)->arrowTexture->getWidth(), (*it)->arrowTexture->getHeight()};
                                
                //                 for(int i = 0; i < 1; i++)
                //                 {
                //                     for(int j = 0; j < 1; j++)
                //                     {
                //                         if(arrowY+i < currentLevel->mRow && arrowX+j < currentLevel->mCol)
                //                         {
                //                             if(currentLevel->mTileMatrix[arrowY+i][arrowX+j] != -1)
                //                             {
                //                                 SDL_Rect tile = {(arrowX+i)*currentLevel->tileWidth*currentLevel->scale, (arrowY+j)*currentLevel->tileHeight*currentLevel->scale, currentLevel->tileWidth*currentLevel->scale, currentLevel->tileHeight*currentLevel->scale};

                //                                 if(arrowRect.x < (tile.x + tile.w) && (arrowRect.x + arrowRect.w) > tile.x &&
                //                                         arrowRect.y < (tile.y + tile.h) && (arrowRect.y + arrowRect.h) > tile.y)
                //                                 {
                //                                     (*it)->arrow1.arrowAlive = false;
                //                                 }
                //                             }
                //                         }
                //                     }
                //                 }
                //             }
                //         }
                        
                   }
                    
                }
            }
            else if (levelNum == 2)
            {
                 for(auto it = enemy2.begin(); it != enemy2.end(); it++)
                {
                    if(playerBullet->bulletAlive && !(*it)->dead)
                    {
                        playerBullet->bulletAlive = !((*it)->bulletEnemyCollision({playerBullet->bulletPos.x,playerBullet->bulletPos.y, bulletTexture->getWidth(), bulletTexture->getHeight()}));
                        if(!playerBullet->bulletAlive) killCount++;
                        
                    }
                    if(!(*it)->dead)
                    {
                        enemyUpdateValue = (*it)->update(player->getPosition());
                        if (enemyUpdateValue == 3)
                        {
                            player->reduceLife(0);
                        }
                    
                    }
                    
                }

                for(auto it = enemy2a.begin(); it != enemy2a.end(); it++)
                {
                    if(playerBullet->bulletAlive && !(*it)->dead)
                    {
                        playerBullet->bulletAlive = !((*it)->bulletEnemyCollision({playerBullet->bulletPos.x,playerBullet->bulletPos.y, bulletTexture->getWidth(), bulletTexture->getHeight()}));
                        if(!playerBullet->bulletAlive) killCount++;
                        
                    }
                    if(!(*it)->dead)
                    {
                        enemyUpdateValue = (*it)->update(player->getPosition());
                        if (enemyUpdateValue == 3)
                        {
                            player->reduceLife(0);
                        }

                        if((*it)->arrowPlayerCollision(SDL_Rect{player->getPosition().x, player->getPosition().y, playerWidth, playerHeight}))
                        {
                            player->reduceLife(1);
                        }
        
                    }
                    
                }
            }
            
            //std::cout << killCount << std::endl;
            
            
            
            //For bullet
            if(playerBullet->bulletAlive)
            {
                playerBullet->bulletPos = {playerBullet->bulletPos.x+playerBullet->bulletVel.x, playerBullet->bulletPos.y};
                //mBulletTexture.render(pBullet.bulletPos.x - camera.x, pBullet.bulletPos.y - camera.y);

                if(playerBullet->bulletPos.x > currentLevel->camera.x + WindowWidth)
                {
                    playerBullet->bulletAlive = false;
                } 
                else
                {
                    int bulletX = playerBullet->bulletPos.x / (currentLevel->tileWidth * currentLevel->scale);
                    int bulletY = playerBullet->bulletPos.y / (currentLevel->tileHeight * currentLevel->scale);
                    SDL_Rect bulletRect = {playerBullet->bulletPos.x, playerBullet->bulletPos.y, bulletTexture->getWidth(), bulletTexture->getHeight()};
                    
                    for(int i = 0; i < 1; i++)
                    {
                        for(int j = 0; j < 2; j++)
                        {
                            if(bulletY+i < currentLevel->mRow && bulletX+j < currentLevel->mCol)
                            {
                                if(currentLevel->mTileMatrix[bulletY+i][bulletX+j] != -1)
                                {
                                    SDL_Rect tile = {(bulletX+i)*currentLevel->tileWidth*currentLevel->scale, (bulletY+j)*currentLevel->tileHeight*currentLevel->scale, currentLevel->tileWidth*currentLevel->scale, currentLevel->tileHeight*currentLevel->scale};

                                    if(bulletRect.x < (tile.x + tile.w) && (bulletRect.x + bulletRect.w) > tile.x &&
                                            bulletRect.y < (tile.y + tile.h) && (bulletRect.y + bulletRect.h) > tile.y)
                                    {
                                        playerBullet->bulletAlive = false;
                                    }
                                }
                            }
                        }
                    }
                }
            }           
            break;
        case (START_SCREEN):
            break;
        case (SELECT_SCREEN):
            break;
        case (PAUSE_SCREEN):
            break;
        default:
            break;
    }
}

void Game::clean()
{
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}
void Game::handleEvents(float deltaTime)
{
    SDL_GetMouseState(&mousePos.x,&mousePos.y);
    dt = deltaTime;
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT || currentGameState == EXIT_SCREEN)
        {

            runGame=false;
        }
        else if (event.key.keysym.sym== SDLK_SPACE && currentGameState == START_SCREEN)
        {

            currentGameState = SELECT_SCREEN;
        }
        else if(currentGameState == SELECT_SCREEN && selectScreen->isInsidePlay(mousePos))
        {
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
    
                currentGameState = GAME_SCREEN;
            }
        }
        else if(currentGameState == SELECT_SCREEN && selectScreen->isInsideExit(mousePos))
        {
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
    
                currentGameState = EXIT_SCREEN;
            }
        }
        else if(currentGameState == SELECT_SCREEN && selectScreen->isInsideInstruction(mousePos))
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
    
                currentGameState = INSTRUCTIONS_SCREEN;
            }
        }
        else if(currentGameState == INSTRUCTIONS_SCREEN && controls->isInsideReturn(mousePos))
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
    
                currentGameState = SELECT_SCREEN;
            }
        }
        else if (currentGameState == GAME_SCREEN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            currentGameState = PAUSE_SCREEN;
        }
        else if (currentGameState ==  PAUSE_SCREEN && paused->isInsideResume(mousePos))
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                currentGameState = GAME_SCREEN;
            }
        }
        else if (currentGameState ==  PAUSE_SCREEN && paused->isInsideExit(mousePos))
        {
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                currentGameState = EXIT_SCREEN;
            }
        }
        else if (currentGameState == GAME_SCREEN)
        {

            player->handleInput(event, dt);
            
            //For shooting
            const Uint8* state = SDL_GetKeyboardState(NULL);
            
            if(state[SDL_SCANCODE_LSHIFT] && !playerBullet->shootFlag && !playerBullet->bulletAlive)
            {
                playerBullet->bulletAlive = true;
                playerBullet->shootFlag = true;

                vec bulletSpawnPos;

                if (player->rightFacing)
                {
                    bulletSpawnPos = {player->getPosition().x +playerWidth , player->getPosition().y + 55};
                }
                else
                {
                    bulletSpawnPos = {player->getPosition().x , player->getPosition().y + 55};
                }
                playerBullet->bulletPos = bulletSpawnPos;
                playerBullet->bulletVel.x = (player->leftFacing ? -12 : 12);
            }
            else if(!state[SDL_SCANCODE_LSHIFT])
            {
                playerBullet->shootFlag = false;
            }
            if(state[SDL_SCANCODE_N])
            {
                killCount++;
            }
            
        }
    }
    if (currentGameState == GAME_SCREEN)
    {
        Collider(player,currentLevel);

    }
}

void Game::Collider(Player* player,Level* level)
{
    vec player1=player->getPosition();
    SDL_Rect pCol{player1.x,player1.y,80,110};
    pCollider->setRect(pCol);
    int FirstRow = ((player->getPosition().y)/64 - 1) > 0 ? (player->getPosition().y)/64 - 1 : 0;
    int LastRow = FirstRow + 4 >= level->mRow - 1 ? level->mRow - 1 : FirstRow+4;
    int FirstColumn = (player->getPosition().x)/64 - 2 > 0 ? (player->getPosition().x)/64 - 2 : 0;
    int LastColumn = FirstColumn + 5 >= level->mCol ? level->mCol : FirstColumn + 5;
    for (int row = LastRow;row>=FirstRow;row--)
    {
        for ( int column = FirstColumn; column < LastColumn; column++)
        {
            SDL_Rect pTil{column  * 64,row * 64 -25,64,64};  // y is subtracted by the half of tilewidth to make player stay on the top of tile
            tCollider->setRect(pTil);
            // std::cout<<back->getPosYTiles(row,column)<<std::endl;
            if (level->mTileMatrix[row][column]>=0)
            {
                if(pCollider->checkCollision(*tCollider,0.0f))
                {

                    // int initTileMember = (FirstColumn-10) > 0 ? FirstColumn-10 : 0;
                    for (int i=0;i<level->mCol;i++){tilesOfCollidedRow[i]=level->mTileMatrix[row][i];}
                    vec offset=pCollider->getOffset();
                    if (pCollider->GetPositionX()>tCollider->GetPositionX()){offset.x*=-1;}
                    // if (pCollider->GetPositionX()>tCollider->GetPositionX()+50){offset.x/=2;}
                    if (pCollider->GetPositionX()<tCollider->GetPositionX() && pCollider->GetPositionX()+80>tCollider->GetPositionX()+TileWidth){offset.x=0;}
                    if (pCollider->GetPositionX()>tCollider->GetPositionX() && pCollider->GetPositionX()<tCollider->GetPositionX()+TileWidth){offset.x=0;}
                    if (pCollider->GetPositionY()>tCollider->GetPositionY())
                    {
                        offset.y*=-1;
                        for (int i{0};i<level->mCol;i++){tilesOfCollidedRow[i]= -1;} //while jumping make the tiles as open space
                    }
                    player->CollisionUpdate(offset,tilesOfCollidedRow, level->mCol);
                    breakflag= true;
                    break;
                }
            }     
        }
        if (breakflag)
        {
            breakflag = false;
            break;
        }
    }
}


Game::~Game()
{
    delete player;
    delete pCollider;
    delete tCollider;
    delete startScreen;
    delete controls;
    delete level1;
    delete level2;
    delete enemyLocation;
    delete playerBullet;
    delete enemyBullet;
    delete healthTexture;
    delete levelCompleteTexture;
    delete killCountTexture;

    for(auto enemy : enemy1)
    {
        delete enemy;
    }
    for(auto enemy : enemy1a)
    {
        delete enemy;
    }
    for(auto enemy : enemy2)
    {
        delete enemy;
    }
    for(auto enemy : enemy2a)
    {
        delete enemy;
    }
}