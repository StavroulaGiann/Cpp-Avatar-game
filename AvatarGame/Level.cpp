#include "Level.h"
#include <sgg/graphics.h>
#include "Player.h"
#include "Boss.h"
#include <iostream>
#include "util.h"
using namespace std;


void Level::update(float dt)
{
    if (m_state->getPlayer()->isActive()) {
        if (m_state->getPlayer()->m_attacking) {
            m_state->getPlayer()->Attack();
        }
        m_state->getPlayer()->update(dt);
        if (m_state->getBoss()->isActive()) {
            if (m_state->getBoss()->m_attacking) {
                m_state->getBoss()->Attack();
            }
            else {
                m_state->getBoss()->update(dt);
            }
        }
        else {
            m_state->getBoss()->DrawDeath();
        }
    }
    else {
        if (groundlvl == m_state->getPlayer()->m_pos_y) {
            m_state->getPlayer()->DrawDeath();
        }
        else {
            m_state->getPlayer()->update(dt);
        }

    }

    checkCollisions();

    GameObject::update(dt);
}

void Level::menu()
{
    float width = m_state->GetCanvasWidth();
    float height = m_state->GetCanvasHeight();
    graphics::Brush m;
    m.outline_opacity = 0.0f;
    m.texture = m_state->getAssetPath("pap.png");
    graphics::drawRect(center_x, center_y, width, height, m);
    m.texture = m_state->getAssetPath("MENU.png");
    graphics::drawRect(m_state->GetCanvasWidth() / 2, m_state->GetCanvasHeight() / 2, width / 1.5f, height, m);
    m.texture = m_state->getAssetPath("sp_atk_11.png");
    graphics::drawRect(center_x, center_y + 3.0f, 1.0f * width, 0.4f * width, m);
    if(graphics::getKeyState(graphics::SCANCODE_I)){
        m_about = true;
    }    
    return;
}

void Level::about() {
    float width = m_state->GetCanvasWidth();
    float height = m_state->GetCanvasHeight();
    graphics::Brush m;
    m.outline_opacity = 0.0f;
    m.texture = m_state->getAssetPath("about.png");
    graphics::drawRect(m_state->GetCanvasWidth() / 2, m_state->GetCanvasHeight() / 2, width, height, m);
    if (graphics::getKeyState(graphics::SCANCODE_B)) {
        m_about = false;
    }
}

void Level::init()
{
    m_about = false;

    for (int i = 0;i <= 50 ;i++) {
        m_blocks.push_back(Box(center_x - i, m_state->GetCanvasHeight() , m_block_size, m_block_size));
        m_blocks.push_back(Box(center_x + i, m_state->GetCanvasHeight() , m_block_size, m_block_size));
    }
    for(int i = 0;i<= 10;i++)
    {
        m_blocks.push_back(Box(center_x + 50, m_state->GetCanvasHeight() - i, m_block_size, m_block_size));
        m_blocks.push_back(Box(center_x - 50, m_state->GetCanvasHeight() - i, m_block_size, m_block_size));
    }
    m_blocks.push_back(Box(center_x +11, m_state->GetCanvasHeight() - 3 , m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x +10, m_state->GetCanvasHeight() - 3 , m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x +9, m_state->GetCanvasHeight() - 3 , m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x +8, m_state->GetCanvasHeight() - 3 , m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x - 11, m_state->GetCanvasHeight() - 6 , m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x - 10, m_state->GetCanvasHeight() - 6 , m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x - 9, m_state->GetCanvasHeight() - 6 , m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x - 8, m_state->GetCanvasHeight() - 6 , m_block_size, m_block_size));

    m_blocks.push_back(Box(center_x , m_state->GetCanvasHeight() - 3, m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x + 1, m_state->GetCanvasHeight() - 3, m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x + 2, m_state->GetCanvasHeight() - 3, m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x + 3, m_state->GetCanvasHeight() - 3, m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x - 1, m_state->GetCanvasHeight() - 6, m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x - 2, m_state->GetCanvasHeight() - 6, m_block_size, m_block_size));
    m_blocks.push_back(Box(center_x - 3, m_state->GetCanvasHeight() - 6, m_block_size, m_block_size));
    
}

void Level::gameover() {
    graphics::Brush br;
    br.texture = m_state->getAssetPath("gameover.png");
    br.outline_opacity = 0.0f;
    m_blocks.clear();
    graphics::drawRect(center_x,center_y, m_state->GetCanvasWidth(), m_state->GetCanvasHeight(), br);
    if (graphics::getKeyState(graphics::SCANCODE_R)) {
        m_state->tries++;
        m_state->init();
        m_state->draw();
    }
    return;
}

void Level::drawBlock(int i)
{
    Box& box = m_blocks[i];

    m_block_brush.texture = m_state->getAssetPath("tileset.png");
    m_block_brush.fill_opacity = 1.0f;
    SETCOLOR(m_block_brush.fill_color,0.5f,0.f,1.0f);
    m_block_brush.outline_opacity = 0.0f;
    float x = box.m_pos_x + m_state->g_offset_x;
    float y = box.m_pos_y ;

   
    graphics::drawRect(x, y, box.m_width, box.m_height, m_block_brush);

   /* if (m_state->m_debugging)
        graphics::drawRect(x, y, m_block_size, m_block_size, m_block_brush_debug);*/

}

void Level::checkCollisions()
{
    float offset;
    for (auto& block : m_blocks)
    {
        offset = 0.0f;
        if (offset=m_state->getPlayer()->intersectDown(block))
        {
            m_state->getPlayer()->m_pos_y += offset;
            m_state->getPlayer()->m_vy = 0.0f;
            groundlvl = m_state->getPlayer()->m_pos_y;
            break;
        }
    }

    for (auto& block : m_blocks)
    {
        offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectSideways(block))
        {
            m_state->getPlayer()->m_pos_x += offset;
            m_state->getPlayer()->m_vx = 0.0f;
            break;
        }

    }    

    for (auto& block : m_blocks)
    {
        offset = 0.0f;
        if (offset = m_state->getBoss()->intersectSideways(block)) {
            block.m_pos_x = 1000.0f;

            break;
        }

    }
    if (m_state->getBoss()->isActive()) {
        Box m_boss = Box(m_state->getBoss()->m_pos_x, m_state->getBoss()->m_pos_y, m_state->getBoss()->m_width, m_state->getBoss()->m_height);
        offset = 0.0f;
        if (offset = m_state->getPlayer()->intersectSideways(m_boss))
        {
            m_state->getPlayer()->m_pos_x += offset;
            m_state->getPlayer()->m_vx = 0.0f;
            
        }

        for (auto& block : m_blocks)
        {
            offset = 0.0f;
            if (offset = m_state->getBoss()->intersectDown(block))
            {
                m_state->getBoss()->m_pos_y += offset;
                m_state->getBoss()->b_vy = 0.0f;
                break;
            }
        }
    }
}

void Level::draw()
{
    float w = m_state->GetCanvasWidth() * 2.0f;
    float h = m_state->GetCanvasHeight() * 2.0f;
    
    for (int i = -4; i < 4; i++)
    {
        graphics::drawRect(i * w + center_x + m_state->g_offset_x, 0.0, w,
            h, backg1);
    }
    for (int i = -4; i < 4; i++)
    {
        graphics::drawRect(i * w + center_x + m_state->g_offset_x * 1.1, 0.0f, w,
            h, backg2);
    }
    for (int i = -4; i < 4; i++)
    {
        graphics::drawRect(i * w + center_x + m_state->g_offset_x * 1.3, +0.0, w,
            h, backg4);
    }
    for (int i = -4; i < 4; i++)
    {
        graphics::drawRect(i * w + center_x + m_state->g_offset_x * 1.4, +0.0, w,
            h, backg5);
    }
    for (int i = -4; i < 4; i++)
    {
        graphics::drawRect(i * w + center_x + m_state->g_offset_x * 1.6, +0.0, w,
            h, backg7);
    }
    for (int i = -4; i < 4; i++)
    {
        graphics::drawRect(i * w + center_x + m_state->g_offset_x * 1.7, +0.0, w,
            h, backg8);

    }
    for (int i = -4; i < 4; i++)
    {
        graphics::drawRect(i * w + center_x + m_state->g_offset_x * 1.8, +0.0, w,
            h, backg9);

    }
   
    if (m_state->getBoss()->isActive())
    {
        if (m_state->getBoss()->m_attacking) {
            m_state->getBoss()->Attack();
        }
        else {
            m_state->getBoss()->draw();
        }
    }
    else {
        m_state->getBoss()->DrawDeath();
    }

    if (m_state->getPlayer()->isActive()) {
        if (m_state->getPlayer()->m_attacking) {
            m_state->getPlayer()->Attack();
        }
        else {
            m_state->getPlayer()->draw();
        }
    }    
    else {
        if (groundlvl == m_state->getPlayer()->m_pos_y) {
            m_state->getPlayer()->DrawDeath();
        }
        else {
            m_state->getPlayer()->draw();
        }
    }
    
    for (int i = 0; i < m_blocks.size(); i++)
    {
        drawBlock(i);
    }

}

Level::Level(const std::string& name)
{
    backg1.texture = m_state->getAssetPath("1.png");
    backg1.outline_opacity = 0.0f;

    backg2.texture = m_state->getAssetPath("2.png");
    backg2.outline_opacity = 0.0f;

    backg3.texture = m_state->getAssetPath("3fx.png");
    backg3.outline_opacity = 0.0f;

    backg4.texture = m_state->getAssetPath("4.png");
    backg4.outline_opacity = 0.0f;

    backg5.texture = m_state->getAssetPath("5.png");
    backg5.outline_opacity = 0.0f;

    backg6.texture = m_state->getAssetPath("6fx.png");
    backg6.outline_opacity = 0.0f;

    backg7.texture = m_state->getAssetPath("7.png");
    backg7.outline_opacity = 0.0f;

    backg8.texture = m_state->getAssetPath("8fx.png");
    backg8.outline_opacity = 0.0f;

    backg9.texture = m_state->getAssetPath("9.png");
    backg9.outline_opacity = 0.0f;

    m_block_brush.fill_opacity = 0.0f;
}

Level::~Level()
{
    for (auto p_gob : m_static_objects)
        if (p_gob) delete p_gob;

    for (auto p_gob : m_dynamic_objects)
        if (p_gob) delete p_gob;
}
