#include "stdafx.h"
#include "Castle.h"
#include"Player.h"
#include"Monster1.h"

Castle::Castle()
{
}

Castle::~Castle()
{
}

void Castle::Init()
{
	m_BG = Sprite::Create(L"Painting/Map/CastleBG.png");
	m_BG->SetPosition(1920 / 2, m_BG->m_Size.y / 2);

	ObjMgr->AddObject(new Player(), "Player");
	ObjMgr->AddObject(new Monster1(Vec2(960,1700)), "Monster");

	UI::GetInst()->Init();

	MapLimit::GetInst()->CreateMap(VERTICAL, 20, Vec2(-1920 / 2 - 700, m_BG->m_Size.y + 300));
	MapLimit::GetInst()->CreateMap(VERTICAL, 20, Vec2(3840 - 240, m_BG->m_Size.y + 310));
	MapLimit::GetInst()->CreateMap(HORIZONTAL, 20, Vec2(-1920 / 2 + 100, m_BG->m_Size.y - 50));
}

void Castle::Release()
{
}

void Castle::Update(float deltaTime, float Time)
{
}

void Castle::Render()
{
	m_BG->Render();
}
