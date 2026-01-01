#pragma once
#include "GameObject.h"
#include "Player.h"
#include "box.h"
#include <sgg/graphics.h>
#include <array>

class Boss : public GameObject, public Box
{
	std::vector<std::string> m_idle;
	std::vector<std::string> m_runl;
	std::vector<std::string> m_runr;
	std::vector<std::string> m_atk;
	std::vector<std::string> m_ratk;
	
	bool m_dead = false;

	float w;
	float h;

	const float m_max_speed = 8.0f;
	const float m_accel_horizontal = 3.0f;
	const float m_gravity = 9.8f;
	const float max_hp = 10000;

	float distance;
	
public:
	std::vector<std::string> m_die;
	graphics::Brush boss_br;
	graphics::Brush bar_br;

	float b_vx = 0.0f;
	float b_vy = 0.0f;

	bool m_attacking = false;
	bool t = false;
	float hp = 10000;

public:
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	Boss(std::string name) : GameObject(name) {}

	void DrawDeath();
	void TakeDamage(float dd);
	void Attack();

protected:
	//environment based moving
	void PathFind(float dt);
	void HealthBar();

	~Boss() override;
};