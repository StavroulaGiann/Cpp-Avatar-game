#include "Boss.h"
#include "Player.h"
#include "Level.h"
#include "util.h"
#include "GameState.h"
#include <iostream>
#include<thread>
#include<chrono>
using namespace std;
using namespace std::chrono_literals;

void Boss::update(float dt)
{
    

    float delta_time = dt / 1000.0f;
    int sprite_idle = (int) fabs(graphics::getGlobalTime() / 100.0f) % 6;
    boss_br.texture = m_idle[sprite_idle];
    distance = m_state->getPlayer()->m_pos_x - m_pos_x;
    
    PathFind(dt);
    
    b_vy += delta_time * m_gravity;
    m_pos_y += b_vy * delta_time;
    
    GameObject::update(dt);
}

void Boss::init()
{
    m_pos_x = m_state->GetCanvasWidth() / 2.0f + 40;
    m_pos_y = m_state->GetCanvasHeight() / 2.0f;

    m_height = 6.6f;
    m_width = 5.5f;
    w = 13.5f;
    h = 9.1;
   
    boss_br.fill_opacity = 1.0f;
    boss_br.outline_opacity = 0.0f;

    m_idle.push_back(m_state->getAssetPath("boss_idle_(1).png"));
    m_idle.push_back(m_state->getAssetPath("boss_idle_(2).png"));
    m_idle.push_back(m_state->getAssetPath("boss_idle_(3).png"));
    m_idle.push_back(m_state->getAssetPath("boss_idle_(4).png"));
    m_idle.push_back(m_state->getAssetPath("boss_idle_(5).png"));
    m_idle.push_back(m_state->getAssetPath("boss_idle_(6).png"));

    m_runl.push_back(m_state->getAssetPath("boss_walk_(1).png"));
    m_runl.push_back(m_state->getAssetPath("boss_walk_(2).png"));
    m_runl.push_back(m_state->getAssetPath("boss_walk_(3).png"));
    m_runl.push_back(m_state->getAssetPath("boss_walk_(4).png"));
    m_runl.push_back(m_state->getAssetPath("boss_walk_(5).png"));
    m_runl.push_back(m_state->getAssetPath("boss_walk_(6).png"));
    m_runl.push_back(m_state->getAssetPath("boss_walk_(7).png"));
    m_runl.push_back(m_state->getAssetPath("boss_walk_(8).png"));
    m_runl.push_back(m_state->getAssetPath("boss_walk_(9).png"));
    m_runl.push_back(m_state->getAssetPath("boss_walk_(10).png"));

    m_runr.push_back(m_state->getAssetPath("boss_rwalk_(1).png"));
    m_runr.push_back(m_state->getAssetPath("boss_rwalk_(2).png"));
    m_runr.push_back(m_state->getAssetPath("boss_rwalk_(3).png"));
    m_runr.push_back(m_state->getAssetPath("boss_rwalk_(4).png"));
    m_runr.push_back(m_state->getAssetPath("boss_rwalk_(5).png"));
    m_runr.push_back(m_state->getAssetPath("boss_rwalk_(6).png"));
    m_runr.push_back(m_state->getAssetPath("boss_rwalk_(7).png"));
    m_runr.push_back(m_state->getAssetPath("boss_rwalk_(8).png"));
    m_runr.push_back(m_state->getAssetPath("boss_rwalk_(9).png"));
    m_runr.push_back(m_state->getAssetPath("boss_rwalk_(10).png"));

    m_die.push_back(m_state->getAssetPath("boss_death_(1).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(2).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(3).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(4).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(5).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(6).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(7).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(8).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(9).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(10).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(11).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(12).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(13).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(14).png"));
    m_die.push_back(m_state->getAssetPath("boss_death_(15).png"));

    m_atk.push_back(m_state->getAssetPath("boss_atk_(1).png"));
    m_atk.push_back(m_state->getAssetPath("boss_atk_(2).png"));
    m_atk.push_back(m_state->getAssetPath("boss_atk_(3).png"));
    m_atk.push_back(m_state->getAssetPath("boss_atk_(4).png"));
    m_atk.push_back(m_state->getAssetPath("boss_atk_(5).png"));
    m_atk.push_back(m_state->getAssetPath("boss_atk_(6).png"));
    m_atk.push_back(m_state->getAssetPath("boss_atk_(7).png"));
    m_atk.push_back(m_state->getAssetPath("boss_atk_(8).png"));
    m_atk.push_back(m_state->getAssetPath("boss_atk_(9).png"));
    m_atk.push_back(m_state->getAssetPath("boss_atk_(10).png"));
    m_atk.push_back(m_state->getAssetPath("boss_atk_(11).png"));

    m_ratk.push_back(m_state->getAssetPath("boss_ratk_(1).png"));
    m_ratk.push_back(m_state->getAssetPath("boss_ratk_(2).png"));
    m_ratk.push_back(m_state->getAssetPath("boss_ratk_(3).png"));
    m_ratk.push_back(m_state->getAssetPath("boss_ratk_(4).png"));
    m_ratk.push_back(m_state->getAssetPath("boss_ratk_(5).png"));
    m_ratk.push_back(m_state->getAssetPath("boss_ratk_(6).png"));
    m_ratk.push_back(m_state->getAssetPath("boss_ratk_(7).png"));
    m_ratk.push_back(m_state->getAssetPath("boss_ratk_(8).png"));
    m_ratk.push_back(m_state->getAssetPath("boss_ratk_(9).png"));
    m_ratk.push_back(m_state->getAssetPath("boss_ratk_(10).png"));
    m_ratk.push_back(m_state->getAssetPath("boss_ratk_(11).png"));
}

void Boss::draw()
{
    HealthBar();

    graphics::drawRect(m_pos_x + m_state->g_offset_x , m_pos_y , w , 
        h,boss_br);
}

void Boss::HealthBar() {

    float wid = m_width * (hp / max_hp);
    float x = m_pos_x + ( m_width/2 * (hp/max_hp)) + m_state->g_offset_x - m_width/2;
    SETCOLOR(bar_br.fill_color,0.0f,1.0f,0.0f);

    graphics::drawRect(x, m_pos_y - 4.0f, wid,
        0.5f,bar_br);
}

void Boss::Attack() {
    HealthBar();
    if (!t) {
        SATimer = new Timer(1.0f);
        SATimer->start();
        t = true;
    }
    if (SATimer->isRunning()) {
        if (distance < 0) {
                int sprite_atk = (int)fabs(SATimer->operator float() * 10);
                boss_br.texture = m_atk[sprite_atk];
                graphics::drawRect(m_pos_x + m_state->g_offset_x, m_pos_y, w,
                    h, boss_br);
        }
        else {
                int sprite_atk = (int)fabs(SATimer->operator float() * 10);
                boss_br.texture = m_ratk[sprite_atk];
                graphics::drawRect(m_pos_x + m_state->g_offset_x, m_pos_y, w,
                    h, boss_br);
        }
    }
    else {
        if (fabs(distance) <= m_state->getBoss()->m_width + m_width / 2) {
            m_state->getPlayer()->TakeDamage(500);
        }
        t = false;
        m_attacking = false;
    }
}

void Boss::TakeDamage(float dd){
    hp -= dd;
    if (hp<=0) {
        setActive(false);
    }
}

void Boss::DrawDeath() {
    if (!m_dead) {
        SATimer = new Timer(1.4f);
        SATimer->start();
        m_dead = true;
    }
    if (SATimer->isRunning()) {
        int sprite_die =(int)fabs(SATimer->operator float()*10);
        boss_br.texture = m_die[sprite_die];
        graphics::drawRect(m_pos_x + m_state->g_offset_x, m_pos_y , w,
            h, boss_br);
    }
    else {
        graphics::drawRect(m_pos_x + m_state->g_offset_x, m_pos_y , w,
            h, boss_br);
    }
}

void Boss::PathFind(float dt)
{
    float delta_time = dt / 1000.0f;
    float move = 0.0;
    int sprite_run = (int)fabs(graphics::getGlobalTime() / 100.0f) % 10;
    if (fabs(distance) > m_state->getPlayer()->m_width + m_width / 2) {
        if (fabs(distance) <= 10 && fabs(distance) > m_state->getPlayer()->m_width + m_width / 2) {
            if (distance > 0) {
                boss_br.texture = m_runr[sprite_run];
                move = 1;
            }
            else {
                boss_br.texture = m_runl[sprite_run];
                move = -1;
            }
            b_vx = m_accel_horizontal;
            m_pos_x += delta_time * b_vx * move;
        }
    }
    else {
        m_attacking = true;
    }

}

Boss::~Boss(){
    
    delete m_state->getBoss();
}
