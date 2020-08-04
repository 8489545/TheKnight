#include "stdafx.h"
#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Init()
{
	m_BGHpBar = Sprite::Create(L"Painting/UI/BGHpBar.png");
	m_BGHpBar->SetPosition(m_BGHpBar->m_Size.x / 2 + 10, 950);

	m_HpBar = Sprite::Create(L"Painting/UI/HpBar.png");
	m_HpBar->SetPosition(m_BGHpBar->m_Size.x / 2 + 10, 950);

	m_BGMpBar = Sprite::Create(L"Painting/UI/BGMpBar.png");
	m_BGMpBar->SetPosition(m_BGMpBar->m_Size.x / 2 + 10, 985);

	m_MpBar = Sprite::Create(L"Painting/UI/MpBar.png");
	m_MpBar->SetPosition(m_BGMpBar->m_Size.x / 2 + 10, 985);

	m_HpText = new TextMgr();
	m_HpText->Init(40, false, false, "Arial");
	m_HpText->SetColor(255, 255, 255, 255);

	m_MpText = new TextMgr();
	m_MpText->Init(20, false, false, "Arial");
	m_MpText->SetColor(255, 255, 255, 255);

	ObjMgr->AddObject(m_BGHpBar, "UI");
	ObjMgr->AddObject(m_HpBar, "UI");

	ObjMgr->AddObject(m_BGMpBar, "UI");
	ObjMgr->AddObject(m_MpBar, "UI");
}

void UI::Release()
{
}

void UI::Update()
{
}

void UI::Render()
{
	if (m_Hp <= 0)
		m_Hp = 0;

	Renderer::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	m_HpText->print(std::to_string(m_Hp) + "/" + std::to_string(m_MaxHp) + "(" + 
		std::to_string(m_Hp * m_MaxHp / m_MaxHp) + "%)", 400, 925);

	m_MpText->print(std::to_string(m_Mp) + "/" + std::to_string(m_MaxMp) + "(" +
		std::to_string(m_Mp * m_MaxMp / m_MaxMp) + "%)", 400, m_BGMpBar->m_Position.y - 10);
	Renderer::GetInst()->GetSprite()->End();
	m_HpGage = m_HpBar->m_Size.x / m_MaxHp;

	int Hp = m_MaxHp - m_Hp;

	if (m_Hp >= 0)
	{
		SetRect(&m_HpBar->m_Collision, m_HpBar->m_Position.x - m_HpBar->m_Size.x / 2, m_HpBar->m_Position.y - m_HpBar->m_Size.y / 2,
			m_HpBar->m_Position.x + m_HpBar->m_Size.x / 2, m_HpBar->m_Position.y + m_HpBar->m_Size.y / 2);

		m_HpBar->m_Rect.right = m_HpBar->m_Size.x - (Hp * m_HpGage);
	}

	if (m_Mp <= 0)
		m_Mp = 0;

	m_MpGage = m_MpBar->m_Size.x / m_MaxMp;

	int Mp = m_MaxMp - m_Mp;

	if (m_Mp >= 0)
	{
		SetRect(&m_MpBar->m_Collision, m_MpBar->m_Position.x - m_MpBar->m_Size.x / 2, m_MpBar->m_Position.y - m_MpBar->m_Size.y / 2,
			m_MpBar->m_Position.x + m_MpBar->m_Size.x / 2, m_MpBar->m_Position.y + m_MpBar->m_Size.y / 2);

		m_MpBar->m_Rect.right = m_MpBar->m_Size.x - (Mp * m_MpGage);
	}
}
