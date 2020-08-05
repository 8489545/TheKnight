#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_Idle = new Animation();
	m_Idle->SetParent(this);
	m_Idle->Init(7, true);
	m_Idle->AddContinueFrame(L"Painting/Player/Idle/", 1, 11);

	m_Run = new Animation();
	m_Run->SetParent(this);
	m_Run->Init(7, true);
	m_Run->AddContinueFrame(L"Painting/Player/Run/", 1, 8);

	m_Jump = new Animation();
	m_Jump->SetParent(this);
	m_Jump->Init(7, true);
	m_Jump->AddContinueFrame(L"Painting/Player/Jump/", 1, 4);

	m_AttackLastFrame = 7;

	m_Attack = new Animation();
	m_Attack->SetParent(this);
	m_Attack->Init(14, true);
	m_Attack->AddContinueFrame(L"Painting/Player/Attack/", 1, m_AttackLastFrame);

	m_Dash = new Animation();
	m_Dash->SetParent(this);
	m_Dash->Init(14, true);
	m_Dash->AddContinueFrame(L"Painting/Player/Dash/", 1, 4);

	m_Player = m_Idle;
	m_Player->SetParent(this);
	m_PlayerStatus = Status::IDLE;

	SetPosition(1920 / 2, 1500);

	m_ColBox = Sprite::Create(L"Painting/Player/ColBox.png");
	m_ColBox->m_Position = m_Position;

	m_HeadCol = Sprite::Create(L"Painting/Player/Head.png");
	m_HeadCol->m_Position = m_Position;

	m_FootCol = Sprite::Create(L"Painting/Player/Foot.png");
	m_FootCol->m_Position = m_Position;

	m_Left = Sprite::Create(L"Painting/Player/Side.png");
	m_Left->m_Position = m_Position;

	m_Right = Sprite::Create(L"Painting/Player/Side.png");
	m_Right->m_Position = m_Position;

	m_Line = new LineMgr();
	m_Line->Init(1, true);
	m_Line->SetColor(D3DXCOLOR(255, 255, 255, 255));

	m_Speed = 500.f;

	m_BaseAngle = 0;
	m_LandAngle = 0 + m_BaseAngle;
	m_BaseAngle = 90;

	m_JumpPower = 75.f;
	m_JumpTime = 0;
	m_JumpAccel = 0.f;

	m_Hp = 100;
	m_MaxHp = 100;

	m_Mp = 100;
	m_MaxMp = 100;

	m_LastDireIsRight = true;
	m_isGround = false;

	m_Layer = 2;

	m_RightCol = false;
	m_LeftCol = false;

	m_Damage = 25;
	m_AttackLate = 0.f;
	m_JumpLate = 0.f;

	m_DashCooldown = 0.f;
	m_DashTime = 0.1f;
}

Player::~Player()
{
}

void Player::SetLookingDirection()
{
	if (m_LastDireIsRight)
	{
		m_Scale.x = 1;
	}
	else if (!m_LastDireIsRight)
	{
		m_Scale.x = -1;
	}
}

void Player::Gravity()
{
	static float vy = 0;
	vy += GR * dt;

	if (!m_isGround)
	{
		m_Position.y += vy;
	}
	else
		vy = 0.f;
}

void Player::Run()
{
	if (INPUT->GetKey('D') == KeyState::PRESS && m_PlayerStatus != Status::JUMP)
	{
		m_LastDireIsRight = true;
		m_Player = m_Run;
		if(!m_RightCol)
			Translate(m_Directon.x * m_Speed * dt, m_Directon.y * -m_Speed * dt);
		m_PlayerStatus = Status::RUN;
	}
	if (INPUT->GetKey('D') == KeyState::UP && m_PlayerStatus == Status::RUN)
	{
		m_Player = m_Idle;
		m_PlayerStatus = Status::IDLE;
	}

	if (INPUT->GetKey('A') == KeyState::PRESS && m_PlayerStatus != Status::JUMP)
	{
		m_LastDireIsRight = false;
		m_Player = m_Run;
		if (!m_LeftCol)
			Translate(m_Directon.x * -m_Speed * dt, m_Directon.y * m_Speed * dt);
		m_PlayerStatus = Status::RUN;
	}
	if (INPUT->GetKey('A') == KeyState::UP && m_PlayerStatus == Status::RUN)
	{
		m_Player = m_Idle;
		m_PlayerStatus = Status::IDLE;
	}
}

void Player::Jump()
{
	if (INPUT->GetKey(VK_SPACE) == KeyState::PRESS && m_PlayerStatus != Status::JUMP && m_JumpLate <= 0.f)
	{
		m_JumpTime = 0;
		Pos = m_Position;
		m_PlayerStatus = Status::JUMP;
	}
	if (m_PlayerStatus == Status::JUMP)
	{
		static float minus;
		m_Player = m_Jump;

		m_JumpAccel = ((-GR) / 2 * m_JumpTime * m_JumpTime) + (m_JumpPower * m_JumpTime);
		m_JumpTime += dt * 20.f;
		m_Position.y = Pos.y - m_JumpAccel;

		if (m_JumpAccel < 0.f)
		{
			minus = m_JumpAccel;
		}
		if (m_JumpAccel >= 0.f)
		{
			if (INPUT->GetKey('D') == KeyState::PRESS)
			{
				if (!m_RightCol)
					Translate(m_Speed * dt, m_Speed * dt);
				m_LastDireIsRight = true;
			}
			if (INPUT->GetKey('A') == KeyState::PRESS)
			{
				m_LastDireIsRight = false;
				if (!m_LeftCol)
					Translate(-m_Speed * dt, m_Speed * dt);
			}
		}
		if (m_JumpAccel < 0.f)
		{
			m_JumpLate = 0.1f;
			m_Player = m_Idle;
			m_PlayerStatus = Status::IDLE;
			m_Position.y += minus;
		}
	}
}

void Player::Attack()
{
	if (INPUT->GetButtonDown() && (m_PlayerStatus != Status::ATTACK && m_PlayerStatus != Status::JUMP))
	{
		m_PlayerStatus = Status::ATTACK;
		INPUT->ButtonDown(false);
	}

	if (m_PlayerStatus == Status::ATTACK)
	{
		m_Player = m_Attack;

		if (m_Player->m_CurrentFrame == m_AttackLastFrame - 1)
		{
			m_AttackLate = 0.3f;
			m_Attack->m_CurrentFrame = 0;
			m_PlayerStatus = Status::IDLE;
			m_Player = m_Idle;
		}
	}
}

void Player::Dash()
{
	if (m_DashCooldown <= 0.f && m_PlayerStatus != Status::DASH)
	{
		if (INPUT->GetKey(VK_SHIFT) == KeyState::DOWN)
		{
			if (INPUT->GetKey('D') == KeyState::PRESS)
			{
				m_LastDireIsRight = true;
				m_Player = m_Dash;
				m_PlayerStatus = Status::DASH;
			}
			if (INPUT->GetKey('A') == KeyState::PRESS)
			{
				m_LastDireIsRight = false;
				m_Player = m_Dash;
				m_PlayerStatus = Status::DASH;
			}
		}
	}

	if (m_PlayerStatus == Status::DASH)
	{
		m_DashTime -= dt;
		if (m_LastDireIsRight)
		{
			if (!m_RightCol)
				m_Position.x += 5000 * dt;
		}
		else if (!m_LastDireIsRight)
		{
			if (!m_LeftCol)
				m_Position.x -= 5000 * dt;
		}
		if (m_DashTime <= 0.f)
		{
			m_DashTime = 0.15f;
			m_DashCooldown = 15.f;
			m_Player = m_Idle;
			m_PlayerStatus = Status::IDLE;
		}
	}
}

void Player::SetDirection()
{
	Vec2 rot;
	rot.x = cos(D3DXToRadian((float)m_LandAngle));
	rot.y = sin(D3DXToRadian((float)m_LandAngle));

	m_Directon = m_Position - rot;

	D3DXVec2Normalize(&m_Directon, &rot);
}

void Player::Update(float deltaTime, float Time)
{
	m_isGround = false;
	m_RightCol = false;
	m_LeftCol = false;

	if(m_AttackLate > 0)
		m_AttackLate -= dt;
	if (m_JumpLate > 0)
		m_JumpLate -= dt;
	if (m_DashCooldown > 0)
		m_DashCooldown -= dt;

	UI::GetInst()->m_Hp = m_Hp;
	UI::GetInst()->m_MaxHp = m_MaxHp;
	UI::GetInst()->m_Mp = m_Mp;
	UI::GetInst()->m_MaxMp = m_MaxMp;
	UI::GetInst()->m_DashCooldown = m_DashCooldown;

	Camera::GetInst()->Follow(this);
	ObjMgr->CollisionCheak(this, "Ground");
	ObjMgr->CollisionCheak(this, "Wall");
	if(m_PlayerStatus != Status::JUMP)
	Gravity();
	SetDirection();
	SetLookingDirection();

	if (m_PlayerStatus != Status::DASH)
	{
		if (m_PlayerStatus != Status::ATTACK)
		{
			Run();
			Jump();
		}
		if (m_AttackLate <= 0)
			Attack();
	}

	Dash();

	SetVertex();
	m_Player->Update(deltaTime,Time);

	m_ColBox->m_Position = Vec2(m_Position.x, m_Position.y + 50);
	m_HeadCol->m_Position = Vec2(m_Position.x, m_ColBox->m_Position.y - 75);
	m_FootCol->m_Position = Vec2(m_Position.x, m_ColBox->m_Position.y + 75);
	m_Left->m_Position = Vec2(m_Position.x - m_ColBox->m_Size.x / 2, m_ColBox->m_Position.y);
	m_Right->m_Position = Vec2(m_Position.x + m_ColBox->m_Size.x / 2, m_ColBox->m_Position.y);
}

void Player::Render()
{
	m_Line->DrawLine(m_Vertex, 5);
	m_Player->Render();
	m_ColBox->Render();
	m_HeadCol->Render();
	m_FootCol->Render();
	m_Left->Render();
	m_Right->Render();
}

void Player::OnCollision(Object* other)
{
	if (other->m_Tag == "Ground")
	{
		RECT rc;
		if (IntersectRect(&rc, &m_FootCol->m_Collision, &other->m_Collision))
		{
			m_isGround = true;
		}
	}
	if (other->m_Tag == "Wall")
	{
		RECT rc;
		if (IntersectRect(&rc, &m_ColBox->m_Collision, &other->m_Collision))
		{
			if (IntersectRect(&rc, &m_Left->m_Collision, &other->m_Collision))
			{
				m_LeftCol = true;
			}
			else if (IntersectRect(&rc, &m_Right->m_Collision, &other->m_Collision))
			{
				m_RightCol = true;
			}
		}
	}
}
