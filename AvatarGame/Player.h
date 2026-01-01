#pragma once
#include "GameObject.h"
#include "box.h"
#include <sgg/graphics.h>
#include <array>

class Player : public GameObject ,public Box
{
	std::vector<std::string> m_idle;
	std::vector<std::string> m_runl;
	std::vector<std::string> m_runr;
	std::vector<std::string> m_atk;
	std::vector<std::string> m_latk;
	std::vector<std::string> m_air_atk;
	std::vector<std::string> m_air_latk;
	std::vector<std::string> m_die;

	graphics::Brush player_br;
	graphics::Brush bar_br;


	bool m_dead = false;
	float w;
	float h;


	float hp ;
	const float m_accel_horizontal = 35.0f;
	const float m_accel_vertical = 450.f;
	const float m_max_velocity = 60.0f;
	const float max_hp = 10000;

public:
	float m_vx = 0.0f;
	float m_vy = 0.0f;


	bool m_attacking = false;
	bool t = false;

public:
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	Player(std::string name) : GameObject(name) {}

	void DrawDeath();
	void Attack();
	void TakeDamage(float dd);

protected:
	// dynamic motion control
	void movePlayer(float dt);
	void HealthBar();
	
	
};
