#pragma once
class Monster1 : public Object
{
	Animation* m_Attack;
	Animation* m_Monster;

	LineMgr* m_Line;
public:
	Monster1(Vec2 Pos);
	~Monster1();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* other);
};

