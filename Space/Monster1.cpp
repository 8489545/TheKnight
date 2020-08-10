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

	m_Run = new Animation();
	m_Run->Init(3, true);
	m_Run->AddContinueFrame(L"Painting/Monster/Monster1/Run/", 1, 8);
	m_Run->SetParent(this);

	m_Hit = new Animation();
	m_Hit->Init(3, true);
	m_Hit->AddContinueFrame(L"Painting/Monster/Monster1/Hit/", 1, 4);
	m_Hit->SetParent(this);

	m_Death = new Animation();
	m_Death->Init(3, true);
	m_Death->AddContinueFrame(L"Painting/Monster/Monster1/Death/", 1, 4);
	m_Death->SetParent(this);

	m_Monster = m_Idle;
	m_Status = Status::IDLE;
	m_Monster->SetParent(this);

	m_ColBox = Sprite::Create(L"Painting/Monster/Monster1/ColBox.png");
	m_RightBox = Sprite::Create(L"Painting/Monster/Monster1/Side.png");
	m_LeftBox = Sprite::Create(L"Painting/Monster/Monster1/Side.png");
	m_Foot = Sprite::Create(L"Painting/Monster/Monster1/Foot.png");
	m_AttackBox = Sprite::Create(L"Painting/Monster/Monster1/AttackBox.png");

	m_Position = Pos;

	m_Line = new LineMgr();
	m_Line->Init(1, true);
	m_Line->SetColor(D3DXCOLOR(255, 255, 255, 255));

	m_Sight = Sprite::Create(L"Painting/UI/Sight.png");

	ObjMgr->AddObject(m_Sight, "MonsterSight");

	m_Layer = 2;
	vy = 0;
	m_isGround = false;
	m_isRight = true;
	m_isAggro = false;

	m_Speed = 100.f;

	m_MoveTime = -1.5f;
}

Monster1::~Monster1()
{
}

void Monster1::Gravity()
{
	vy += GR * dt;

	if (!m_isGround)
	{
		m_Position.y += vy;
	}
	else
		vy = 0.f;
}

void Monster1::Update(float deltaTime, float Time)
{
	m_isGround = false;
	m_RightCol = false;
	m_LeftCol = false;

	m_ColBox->SetPosition(m_Position.x, (m_Position.y + m_Size.y / 2) - m_ColBox->m_Size.y/ 2);
	m_RightBox->SetPosition(m_Position.x + m_ColBox->m_Size.x / 2, m_ColBox->m_Position.y);
	m_LeftBox->SetPosition(m_Position.x - m_ColBox->m_Size.x / 2, m_ColBox->m_Position.y);
	m_Foot->SetPosition(m_Position.x, (m_ColBox->m_Position.y + m_ColBox->m_Size.y / 2) - m_Foot->m_Size.y / 2);

	if(m_isRight)
		m_AttackBox->SetPosition(m_Position.x + 80, (m_Position.y + m_Size.y / 2) - m_ColBox->m_Size.y / 2);
	else if(!m_isRight)
		m_AttackBox->SetPosition(m_Position.x - 80, (m_Position.y + m_Size.y / 2) - m_ColBox->m_Size.y / 2);
	m_Sight->m_Position = m_ColBox->m_Position;

	m_MoveTime += dt;

	if (!m_isRight)
		m_Scale.x = -1;
	else
		m_Scale.x = 1;

	ObjMgr->CollisionCheak(this, "Ground");
	ObjMgr->CollisionCheak(this, "Wall");
	ObjMgr->CollisionCheak(m_Sight, "Player");

	if (m_Sight->m_isCollision)
	{
		m_isAggro = true;
	}
	else
	{
		m_isAggro = false;
	}

	if (m_MoveTime >= 7.f)
	{
		m_MoveDist = rand()% 2;
		m_MoveTime = -7.f;
	}
	if (m_MoveTime > 0.f && !m_isAggro)
	{
		m_Status = Status::RUN;
		m_Monster = m_Run;

		if (m_MoveDist == 0)
		{
			if (m_RightCol)
				m_MoveDist = 1;

			m_isRight = true;
			m_Position.x += m_Speed * dt;
		}
		else if (m_MoveDist == 1)
		{
			if (m_LeftCol)
				m_MoveDist = 0;

			m_isRight = false;
			m_Position.x -= m_Speed * dt;
		}
	}
	else
	{
		m_Status = Status::IDLE;
		m_Monster = m_Idle;
	}

	Gravity();

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
	m_AttackBox->Render();
}

void Monster1::OnCollision(Object* other)
{
	if (other->m_Tag == "Ground")
	{
		RECT rc;
		if (IntersectRect(&rc, &m_Foot->m_Collision, &other->m_Collision))
		{
			m_isGround = true;
		}
	}
	if (other->m_Tag == "Wall")
	{
		RECT rc;
		if (IntersectRect(&rc, &m_ColBox->m_Collision, &other->m_Collision))
		{
			if (IntersectRect(&rc, &m_LeftBox->m_Collision, &other->m_Collision))
			{
				m_LeftCol = true;
			}
			else if (IntersectRect(&rc, &m_RightBox->m_Collision, &other->m_Collision))
			{
				m_RightCol = true;
			}
		}
	}
}
