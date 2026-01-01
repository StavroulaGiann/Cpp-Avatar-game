#include "sgg/graphics.h" 
#include "GameState.h"



void init() 
{
    GameState::getInstance()->init();
}

void update(float ms)
{
    GameState::getInstance()->update(ms);
}
    
void draw()
{
    GameState::getInstance()->draw();
}

int main(int argc,char** argv)
{
    graphics::createWindow(960, 540, "Cave Monk");

    GameState::getInstance()->init();

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(GameState::getInstance()->GetCanvasWidth(), GameState::getInstance()->GetCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();
    return 0;
}