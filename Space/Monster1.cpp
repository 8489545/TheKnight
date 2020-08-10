#include "stdafx.h"
#include "Monster1.h"

Monster1::Monster1(Vec2 Pos)
{
	m_Attack = new Animation();
	m_Attack->Init(3, true);
	m_Attack->AddContinueFrame(L"Painting/Monster/Monster1/Attack/", 1, 8);
	m_Attack->SetParent(this);

	m_Idle = new Animation();
	m_Idle->Init(3, true);
	m_Idle->AddContinueFrame(L"Painting/Monster/Monster1/Idle/", 1, 4);
	m_Idle->SetParent(this);

	m_Monster = m_Idle;
	m_Status = Status::IDLE;
	m_Monster->SetParent(this);

	m_ColBox = Sprite::Create(L"Painting/Monster/Monster1/ColBox.png");
	m_RightBox = Sprite::Create(L"Painting/Monster/Monster1/Side.png");
	m_LeftBox = Sprite::Create(L"Painting/Monster/Monster1/Side.png");
	m_Foot = Sprite::Create(L"Painting/Monster/Monster1/Foot.png");

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
	m_ColBox->SetPosition(m_Position.x, (m_Position.y + m_Size.y / 2) - m_ColBox->m_Size.y/ 2);
	m_RightBox->SetPosition(m_Position.x + m_ColBox->m_Size.x / 2, m_ColBox->m_Position.y);
	m_LeftBox->SetPosition(m_Position.x - m_ColBox->m_Size.x / 2, m_ColBox->m_Position.y);
	m_Foot->SetPosition(m_Position.x, (m_ColBox->m_Position.y + m_ColBox->m_Size.y / 2) - m_Foot->m_Size.y / 2);

	SetVertex();
	m_Monster->Update(deltaTime, Time);
}

void Monster1::Render()
{
	m_Line->DrawLine(m_Vertex, 5);
	m_Monster->Render();

	m_ColBox->Render();
	m_RightBox->Render();
	m_LeftBox->Render();
	m_Foot->Render();
}

void Monster1::OnCollision(Object* other)
{
}
