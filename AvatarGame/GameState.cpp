#include "GameState.h"
#include "Level.h"
#include "Player.h"
#include "Boss.h"
#include<thread>
#include<chrono>

using namespace std::chrono_literals;

GameState::GameState()
{
}

GameState::~GameState()
{
    if (curr_level)
        delete curr_level;
}


bool GameState::init()
{

    curr_level = new Level("1.lvl");
    curr_level->init();
    
    player = new Player("Player");
    player->init();

    boss = new Boss("Boss");
    boss->init();

    graphics::preloadBitmaps(getAssetDir());

    return true;
}

void GameState::draw()

{
    if (!curr_level)
        return;
    if (curr_level->isActive()&& tries==1)
    {
        if (curr_level->m_about) {
            curr_level->about();
        }
        else
        {
            curr_level->menu();
        }
    }
    else {
        curr_level->draw();
    }   
}

void GameState::update(float ms)
{

    if (ms > 500) // ms
        return;

    float sleep_time = std::max(17.0f - ms, 0.0f);
    if (sleep_time > 0.0f)
    {
        std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(sleep_time));
    }

    if (!curr_level)
        return;

    if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
        curr_level->setActive(false);
    }

    if (curr_level->isActive() && tries==1)
    {
        if (curr_level->m_about) {
            curr_level->about();
        }else
        {
            curr_level->menu();
        }
    }
    else {
        curr_level->update(ms);
    }


}

GameState* GameState::getInstance()
{
    if (unique_instance == nullptr) 
    {
        unique_instance = new GameState();
    }
    return unique_instance;
}

std::string GameState::getAssetDir()
{
    return asset_path;
}

std::string GameState::getAssetPath(const std::string& asset)
{
    return asset_path + asset;
}

GameState* GameState::unique_instance = nullptr;