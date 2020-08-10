#pragma once
class Monster1 : public Object
{
	Animation* m_Attack;
	Animation* m_Idle;
	Animation* m_Monster;

	Sprite* m_ColBox;
	Sprite* m_RightBox;
	Sprite* m_LeftBox;
	Sprite* m_Foot;

	LineMgr* m_Line;
public:
	Monster1(Vec2 Pos);
	~Monster1();

	Status m_Status;

	float vy;
	bool m_isGround;

	void Gravity();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* other);
};

