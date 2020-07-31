#pragma once
enum class Status
{
	IDLE,
	RUN,
	JUMP,
	NONE
};
class Player : public Object
{
	Animation* m_Idle;
	Animation* m_RRun;
	Animation* m_LRun;

	Animation* m_Player;

	LineMgr* m_Line;
public:
	Player();
	~Player();

	Vec2 m_Directon;
	int m_LandAngle;
	int m_BaseAngle;

	float m_Speed;
	
	float m_JumpTime;
	float m_JumpPower;

	Status m_PlayerStatus;

	void Run();
	void Jump();
	void Gravity();
	void SetDirection();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* other);
};

