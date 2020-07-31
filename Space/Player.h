#pragma once
class Player : public Object
{
	Sprite* m_Sprite;

	LineMgr* m_Line;
public:
	Player();
	~Player();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* other);
};

