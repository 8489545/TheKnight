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
}

Player::~Player()
{
}

void Player::Run()
{
	if (INPUT->GetKey(VK_RIGHT) == KeyState::PRESS)
	{
		m_Player = m_RRun;
		Translate(m_Directon.x * m_Speed * dt, m_Directon.y * -m_Speed * dt);
		m_PlayerStatus = Status::RUN;
	}
	if (INPUT->GetKey(VK_RIGHT) == KeyState::UP)
	{
		m_Player = m_Idle;
		m_PlayerStatus = Status::IDLE;
	}

	if (INPUT->GetKey(VK_LEFT) == KeyState::PRESS)
	{
		m_Player = m_LRun;
		Translate(m_Directon.x * -m_Speed * dt, m_Directon.y * m_Speed * dt);
		m_PlayerStatus = Status::RUN;
	}
	if (INPUT->GetKey(VK_LEFT) == KeyState::UP)
	{
		m_Player = m_Idle;
		m_PlayerStatus = Status::IDLE;
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
	SetDirection();
	Run();

	SetVertex();
	m_Player->Update(deltaTime,Time);
}

void Player::Render()
{
	m_Player->Render();
	m_Line->DrawLine(m_Vertex, 5);
}

void Player::OnCollision(Object* other)
{
}
