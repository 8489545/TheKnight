#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_Idle = new Animation();
	m_Idle->SetParent(this);
	m_Idle->Init(7, true);
	m_Idle->AddContinueFrame(L"Painting/Player/Idle/", 1, 11);

	m_RRun = new Animation();
	m_RRun->SetParent(this);
	m_RRun->Init(7, true);
	m_RRun->AddContinueFrame(L"Painting/Player/RRun/", 1, 8);

	m_LRun = new Animation();
	m_LRun->SetParent(this);
	m_LRun->Init(7, true);
	m_LRun->AddContinueFrame(L"Painting/Player/LRun/", 1, 8);

	m_Jump = new Animation();
	m_Jump->SetParent(this);
	m_Jump->Init(7, true);
	m_Jump->AddContinueFrame(L"Painting/Player/Jump/", 1, 4);

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
}

Player::~Player()
{
}

void Player::Run()
{
	if (INPUT->GetKey('D') == KeyState::PRESS && m_PlayerStatus != Status::JUMP)
	{
		m_Player = m_RRun;
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
		m_Player = m_LRun;
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
	if (m_Scale.x == -1)
		m_Scale.x *= -1;
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
		}

		if (INPUT->GetKey('A') == KeyState::PRESS)
		{
			if(m_Scale.x == 1)
				m_Scale.x *= -1;

			Translate(-m_Speed * dt,m_Speed * dt);
		}
		else
		{
		}
		if (m_JumpAccel < 0.f)
		{
			m_Player = m_Idle;
			m_PlayerStatus = Status::IDLE;
		}
	}
}

void Player::Gravity()
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
