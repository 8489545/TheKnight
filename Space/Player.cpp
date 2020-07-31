#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_Sprite = Sprite::Create(L"Painting/Player/Attack/1.png");
	m_Sprite->SetParent(this);
	SetPosition(1920 / 2, 1080 / 2);

	m_Line = new LineMgr();
	m_Line->Init(1, true);
	m_Line->SetColor(D3DXCOLOR(255, 255, 255, 255));
}

Player::~Player()
{
}

void Player::Update(float deltaTime, float Time)
{
	SetVertex();
}

void Player::Render()
{
	m_Sprite->Render();
	m_Line->DrawLine(m_Vertex, 5);
}

void Player::OnCollision(Object* other)
{
}
