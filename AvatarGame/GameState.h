#pragma once
#include "sgg/graphics.h"
#include <string> 



class GameState {
    
private:

    const std::string asset_path = "assets//";

    const float canvas_hei = 18.0f;
    const float canvas_wid = 32.0f;

    static GameState* unique_instance;

    GameState();

    class Player* player = 0;
    class Level* curr_level = 0;
    class Boss* boss = 0;

public:
    float g_offset_x =0.0f;
    float g_offset_y =0.0f;
    const float m_gravity = 9.8f;
    int tries = 1;

public:
    bool init();
    void draw();
    void update(float ms);

    ~GameState();
    static GameState* getInstance();

    float GetCanvasWidth() { return canvas_wid; }
    float GetCanvasHeight() { return canvas_hei; }

    std::string getAssetDir();
    std::string getAssetPath(const std::string& asset);
    
    class Player* getPlayer() { return player; };
    class Boss* getBoss() { return boss; };
    class Level* getLevel() { return curr_level; };
};
