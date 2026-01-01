#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Boss.h"
#include "GameState.h"
#include <sgg/graphics.h>
#include <list>
#include <vector>
#include <string>


class Level : public GameObject
{
	graphics::Brush backg1;
	graphics::Brush backg2;
	graphics::Brush backg3;
	graphics::Brush backg4;
	graphics::Brush backg5;
	graphics::Brush backg6;
	graphics::Brush backg7;
	graphics::Brush backg8;
	graphics::Brush backg9;

	graphics::Brush temp_br;

	std::vector<Box> m_blocks;
	const float m_block_size = 1.0f;
	graphics::Brush m_block_brush;

	float center_x = m_state->GetCanvasWidth()/2.0f;
	float center_y = m_state->GetCanvasHeight() / 2.0f;

	std::vector<GameObject*> m_static_objects;
	std::list<GameObject*> m_dynamic_objects;

	// dedicated method to draw a block
	void drawBlock(int i);

	// detect collisions
	void checkCollisions();

public:
	bool m_about;
	float groundlvl;
public:
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	void menu();
	void about();
	void gameover();

	Level(const std::string& name = "Level1");
	~Level() override;

};