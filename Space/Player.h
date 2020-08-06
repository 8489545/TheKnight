#pragma once
enum class Status
{
	IDLE,
	RUN,
	JUMP,
	ATTACK,
	DASH,
	NONE
};
class Player : public Object
{
	Animation* m_Idle;
	Animation* m_Run;
	Animation* m_Jump;
	Animation* m_Attack;
	Animation* m_Dash;

	Animation* m_Player;

	Sprite* m_ColBox;
	Sprite* m_HeadCol;
	Sprite* m_FootCol;
	Sprite* m_Left;
	Sprite* m_Right;

	LineMgr* m_Line;
public:
	Player();
	~Player();

	Vec2 m_Directon;
	int m_LandAngle;
	int m_BaseAngle;

	float m_Speed;
	int m_Hp;
	int m_MaxHp;

	int m_Mp;
	int m_MaxMp;

	float m_AttackLate;
	float m_Damage;

	bool m_LastDireIsRight;
	bool m_isGround;

	bool m_RightCol;
	bool m_LeftCol;
	
	Vec2 m_JumpPos;
	float m_JumpTime;
	float m_JumpPower;
	float m_JumpAccel;
	float m_JumpLate;

	Vec2 Pos;

	int m_AttackLastFrame;

	Status m_PlayerStatus;

	float m_DashCooldown;
	float m_DashTime;

	float m_HealCooldown;

	float m_MpRegenTime;

	void SetLookingDirection();
	void Gravity();
	void Run();
	void Jump();
	void Attack();
	void Dash();
	void Heal();
	void SetDirection();

	void Update(float deltaTime, float Time);
	void Render();
	void OnCollision(Object* other);
};

