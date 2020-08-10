#include "stdafx.h"
#include "Monster1.h"

Monster1::Monster1(Vec2 Pos)
{
	m_Attack = new Animation();
	m_Attack->Init(3, true);
	m_Attack->AddContinueFrame(L"Painting/Monster/Monster1/Attack/", 1, 8);
	m_Attack->SetParent(this);

	m_Monster = m_Attack;
	m_Monster->SetParent(this);

	m_Position = Pos;

	m_Line = new LineMgr();
	m_Line->Init(1, true);
	m_Line->SetColor(D3DXCOLOR(255, 255, 255, 255));

	m_Layer = 2;
}

Monster1::~Monster1()
{
}

void Monster1::Update(float deltaTime, float Time)
{
	SetVertex();
	m_Monster->Update(deltaTime, Time);
}

void Monster1::Render()
{
	m_Line->DrawLine(m_Vertex, 5);
	m_Monster->Render();
}

void Monster1::OnCollision(Object* other)
{
}
