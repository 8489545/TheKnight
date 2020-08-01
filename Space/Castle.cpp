#include "stdafx.h"
#include "Castle.h"
#include"Player.h"

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

	UI::GetInst()->Init();
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
