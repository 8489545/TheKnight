#pragma once
class Monster1 : public Object
{
	Animation* m_Attack;
	Animation* m_Idle;
	Animation* m_Run;
	Animation* m_Hit;
	Animation* m_Death;
	Animation* m_Monster;

	Sprite* m_ColBox;
	Sprite* m_RightBox;
	Sprite* m_LeftBox;
	Sprite* m_Foot;
	Sprite* m_AttackBox;

	Sprite* m_Sight;

	LineMgr* m_Line;
public:
	Monster1(Vec2 Pos);
	~Monster1();

	Status m_Status;

	float vy;
	bool m_isGround;
	bool m_isRight;
	bool m_RightCol;
	bool m_LeftCol;
	bool m_isAggro;

	float m_Speed;

	float m_MoveTime;
	int m_MoveDist;

	void Gravity();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* other);
};

