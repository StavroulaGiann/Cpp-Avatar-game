#include "Player.h"
#include "util.h"
#include "Boss.h"
#include "Level.h"
#include "GameState.h"


void Player::update(float dt)
{
    float delta_time = dt / 1000.0f;

	movePlayer(dt);
    
    if (graphics::getKeyState(graphics::SCANCODE_Q)) {
        m_attacking=true;
    }

	m_state->g_offset_x = m_state->GetCanvasWidth() / 2.0f - m_pos_x;
	m_state->g_offset_y = m_state->GetCanvasHeight() / 2.0f - m_pos_y;
    
    GameObject::update(dt);
}

void Player::init()
{
    setActive(true);

    hp = 10000;

    m_pos_x = m_state->GetCanvasWidth() / 2.0f;
    m_pos_y = m_state->GetCanvasHeight() - 1;

    m_height = 1.1f;
    m_width = 0.8f;
    w = 9.6;
    h = 4.1;

    player_br.fill_opacity = 1.0f;
    player_br.outline_opacity = 0.0f;


    m_idle.push_back(m_state->getAssetPath("idle_(1).png"));
    m_idle.push_back(m_state->getAssetPath("idle_(2).png"));
    m_idle.push_back(m_state->getAssetPath("idle_(3).png"));
    m_idle.push_back(m_state->getAssetPath("idle_(4).png"));
    m_idle.push_back(m_state->getAssetPath("idle_(5).png"));
    m_idle.push_back(m_state->getAssetPath("idle_(6).png"));

    m_atk.push_back(m_state->getAssetPath("atk_(1).png"));
    m_atk.push_back(m_state->getAssetPath("atk_(2).png"));
    m_atk.push_back(m_state->getAssetPath("atk_(3).png"));
    m_atk.push_back(m_state->getAssetPath("atk_(4).png"));
    m_atk.push_back(m_state->getAssetPath("atk_(5).png"));
    m_atk.push_back(m_state->getAssetPath("atk_(6).png"));

    m_latk.push_back(m_state->getAssetPath("latk_(1).png"));
    m_latk.push_back(m_state->getAssetPath("latk_(2).png"));
    m_latk.push_back(m_state->getAssetPath("latk_(3).png"));
    m_latk.push_back(m_state->getAssetPath("latk_(4).png"));
    m_latk.push_back(m_state->getAssetPath("latk_(5).png"));
    m_latk.push_back(m_state->getAssetPath("latk_(6).png"));

    m_air_atk.push_back(m_state->getAssetPath("air_atk_(1).png"));
    m_air_atk.push_back(m_state->getAssetPath("air_atk_(2).png"));
    m_air_atk.push_back(m_state->getAssetPath("air_atk_(3).png"));
    m_air_atk.push_back(m_state->getAssetPath("air_atk_(4).png"));
    m_air_atk.push_back(m_state->getAssetPath("air_atk_(5).png"));
    m_air_atk.push_back(m_state->getAssetPath("air_atk_(6).png"));

    m_air_latk.push_back(m_state->getAssetPath("air_latk_(1).png"));
    m_air_latk.push_back(m_state->getAssetPath("air_latk_(2).png"));
    m_air_latk.push_back(m_state->getAssetPath("air_latk_(3).png"));
    m_air_latk.push_back(m_state->getAssetPath("air_latk_(4).png"));
    m_air_latk.push_back(m_state->getAssetPath("air_latk_(5).png"));
    m_air_latk.push_back(m_state->getAssetPath("air_latk_(6).png"));

    m_runl.push_back(m_state->getAssetPath("runl_(1).png"));
    m_runl.push_back(m_state->getAssetPath("runl_(2).png"));
    m_runl.push_back(m_state->getAssetPath("runl_(3).png"));
    m_runl.push_back(m_state->getAssetPath("runl_(4).png"));
    m_runl.push_back(m_state->getAssetPath("runl_(5).png"));
    m_runl.push_back(m_state->getAssetPath("runl_(6).png"));
    m_runl.push_back(m_state->getAssetPath("runl_(7).png"));
    m_runl.push_back(m_state->getAssetPath("runl_(8).png"));

    m_runr.push_back(m_state->getAssetPath("run_(1).png"));
    m_runr.push_back(m_state->getAssetPath("run_(2).png"));
    m_runr.push_back(m_state->getAssetPath("run_(3).png"));
    m_runr.push_back(m_state->getAssetPath("run_(4).png"));
    m_runr.push_back(m_state->getAssetPath("run_(5).png"));
    m_runr.push_back(m_state->getAssetPath("run_(6).png"));
    m_runr.push_back(m_state->getAssetPath("run_(7).png"));
    m_runr.push_back(m_state->getAssetPath("run_(8).png"));

    m_die.push_back(m_state->getAssetPath("death_(1).png"));
    m_die.push_back(m_state->getAssetPath("death_(2).png"));
    m_die.push_back(m_state->getAssetPath("death_(3).png"));
    m_die.push_back(m_state->getAssetPath("death_(4).png"));
    m_die.push_back(m_state->getAssetPath("death_(5).png"));
    m_die.push_back(m_state->getAssetPath("death_(6).png"));
    m_die.push_back(m_state->getAssetPath("death_(7).png"));
    m_die.push_back(m_state->getAssetPath("death_(8).png"));
    m_die.push_back(m_state->getAssetPath("death_(9).png"));
    m_die.push_back(m_state->getAssetPath("death_(10).png"));
    m_die.push_back(m_state->getAssetPath("death_(11).png"));
    m_die.push_back(m_state->getAssetPath("death_(12).png"));
    m_die.push_back(m_state->getAssetPath("death_(13).png"));
    m_die.push_back(m_state->getAssetPath("death_(14).png"));
    m_die.push_back(m_state->getAssetPath("death_(15).png"));
    m_die.push_back(m_state->getAssetPath("death_(16).png"));
    m_die.push_back(m_state->getAssetPath("death_(17).png"));
    m_die.push_back(m_state->getAssetPath("death_(18).png"));
}

void Player::draw()
{   
    HealthBar();
    
    graphics::drawRect(m_state->GetCanvasWidth() / 2.0f, m_pos_y - 1.29f, w,
        h, player_br);
}

void Player::DrawDeath() {
    if (!m_dead) {
        SATimer = new Timer(1.7f);
        SATimer->start();
        m_dead = true;
    }
    if (SATimer->isRunning()) {
        int sprite_die = (int)fabs(SATimer->operator float() * 10);
        player_br.texture = m_die[sprite_die];
        graphics::drawRect(m_state->GetCanvasWidth() / 2.0f, m_pos_y - 1.29f,w,
            h, player_br);
    }
    else {
        m_state->getLevel()->gameover();
    }
}

void Player::HealthBar() {

    float w = m_width * (hp / max_hp);
    float x = m_pos_x + (m_width / 2 * (hp / max_hp)) + m_state->g_offset_x - m_width / 2;
    SETCOLOR(bar_br.fill_color, 0.0f, 1.0f, 0.0f);

    graphics::drawRect(x , m_pos_y - 1.0f, w * 2,
        0.5f, bar_br);
}

void Player::TakeDamage(float dd) {
    hp -= dd;
    if (hp <= 0) {
        setActive(false);
    }
} 

void Player::Attack() {
    HealthBar();
    float distance = m_state->getBoss()->m_pos_x - m_pos_x;
    if (!t) {
        SATimer = new Timer(0.5f);
        SATimer->start();
        t = true;
    }
    if (SATimer->isRunning()) {
        if (distance > 0) {
            if (m_state->getLevel()->groundlvl==m_pos_y){

                int sprite_atk = (int)fabs(SATimer->operator float() * 10);
                player_br.texture = m_atk[sprite_atk];
                graphics::drawRect(m_state->GetCanvasWidth() / 2.0f, m_pos_y - 1.29f, w,
                    h, player_br);
            }
            else {
                int sprite_atk = (int)fabs(SATimer->operator float() * 10);
                player_br.texture = m_air_atk[sprite_atk];
                graphics::drawRect(m_state->GetCanvasWidth() / 2.0f, m_pos_y - 1.29f, w,
                    h, player_br);
            }
        }
        else {
            if (m_state->getLevel()->groundlvl == m_pos_y) {
                int sprite_atk = (int)fabs(SATimer->operator float() * 10);
                player_br.texture = m_latk[sprite_atk];
                graphics::drawRect(m_state->GetCanvasWidth() / 2.0f, m_pos_y - 1.29f, w,
                    h, player_br);
            }
            else {
                int sprite_atk = (int)fabs(SATimer->operator float() * 10);
                player_br.texture = m_air_latk[sprite_atk];
                graphics::drawRect(m_state->GetCanvasWidth() / 2.0f, m_pos_y - 1.29f, w,
                    h, player_br);
            }
        }
    }
    else {
        if (fabs(distance) <= m_state->getBoss()->m_width + m_width / 2 ) {
            m_state->getBoss()->TakeDamage(300);
        }
        m_attacking = false;
        t = false;
    }    
}

void Player::movePlayer(float dt)
{
    float delta_time = dt / 1000.0f;
    int sprite_run = (int)fabs(graphics::getGlobalTime()/100.0f) % 8;
    int sprite_idle = (int)fabs(graphics::getGlobalTime() / 100.0f) % 6;
    player_br.texture = m_idle[sprite_idle];
   
    float move = 0.0f;

    if (graphics::getKeyState(graphics::SCANCODE_A)) {
        player_br.texture = m_runl[sprite_run];
        move = - 1.0f;
    }
    if (graphics::getKeyState(graphics::SCANCODE_D)) {
        player_br.texture = m_runr[sprite_run];
        move = 1.0f;
    }


    m_vx = std::min(m_max_velocity, m_vx + delta_time * move * m_accel_horizontal);
    m_vx = std::max(-m_max_velocity, m_vx);
    
    m_vx -= 0.2f * m_vx/(0.1f+fabs(m_vx));
    
    if (fabs(m_vx) < 0.01f)
        m_vx = 0.0f;

    m_pos_x += delta_time * m_vx;


    if (m_vy == 0.0f)
        m_vy -= (graphics::getKeyState(graphics::SCANCODE_W) ? m_accel_vertical : 0.0f)*0.02f;

    m_vy += delta_time * m_state->m_gravity;

    
    m_pos_y += m_vy * delta_time;    
}