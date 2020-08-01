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

	m_Attack = new Animation();
	m_Attack->SetParent(this);
	m_Attack->Init(7, true);
	m_Attack->AddContinueFrame(L"Painting/Player/Attack/", 1, 6);

	m_Player = m_Idle;
	m_Player->SetParent(this);
	m_PlayerStatus = Status::IDLE;

	SetPosition(1920 / 2, 1080 / 2);

	m_Line = new LineMgr();
	m_Line->Init(1, true);
	m_Line->SetColor(D3DXCOLOR(255, 255, 255, 255));

	m_Speed = 500.f;

	m_BaseAngle = 0;
	m_LandAngle = 0 + m_BaseAngle;
	m_BaseAngle = 90;

	m_JumpPower = 75.f;
	m_JumpTime = 0;
	m_JumpAccel = 1.f;

	m_LastDireIsRight = true;
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
}

void Player::Run()
{
	if (INPUT->GetKey('D') == KeyState::PRESS && m_PlayerStatus != Status::JUMP)
	{
		m_LastDireIsRight = true;
		m_Player = m_Run;
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
	if (INPUT->GetKey(VK_SPACE) == KeyState::PRESS && m_PlayerStatus != Status::JUMP)
	{
		m_JumpTime = 0;
		Pos = m_Position;
		m_PlayerStatus = Status::JUMP;
	}
	if (m_PlayerStatus == Status::JUMP)
	{
		m_Player = m_Jump;

		m_JumpAccel = ((-GR) / 2 * m_JumpTime * m_JumpTime) + (m_JumpPower * m_JumpTime);
		m_JumpTime += dt * 20;
		m_Position.y = Pos.y - m_JumpAccel;

		if (INPUT->GetKey('D') == KeyState::PRESS)
		{
			Translate(m_Speed * dt, m_Speed * dt);
			m_LastDireIsRight = true;
		}
		if (INPUT->GetKey('A') == KeyState::PRESS)
		{
			m_LastDireIsRight = false;
			Translate(-m_Speed * dt,m_Speed * dt);
		}
		if (m_JumpAccel < 0.f)
		{
			m_Player = m_Idle;
			m_PlayerStatus = Status::IDLE;
		}
	}
}

void Player::Attack()
{
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
	//Camera::GetInst()->Follow(this);
	SetDirection();
	SetLookingDirection();
	Run();
	Gravity();
	Jump();

	SetVertex();
	m_Player->Update(deltaTime,Time);
}

void Player::Render()
{
	m_Line->DrawLine(m_Vertex, 5);
	m_Player->Render();
}

void Player::OnCollision(Object* other)
{
}
