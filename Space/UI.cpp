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

	m_DashUI = Sprite::Create(L"Painting/UI/DashUI.png");
	m_DashUI->SetPosition(1500, 950);
	m_DashBlind = Sprite::Create(L"Painting/UI/Blind.png");
	m_DashBlind->SetPosition(1500, 957);

	m_HealUI = Sprite::Create(L"Painting/UI/HealUI.png");
	m_HealUI->SetPosition(1650, 950);
	m_HealBlind = Sprite::Create(L"Painting/UI/Blind.png");
	m_HealBlind->SetPosition(1650, 957);

	m_HpText = new TextMgr();
	m_HpText->Init(40, false, false, "Arial");
	m_HpText->SetColor(255, 255, 255, 255);

	m_MpText = new TextMgr();
	m_MpText->Init(20, false, false, "Arial");
	m_MpText->SetColor(255, 255, 255, 255);

	m_DashText = new TextMgr();
	m_DashText->Init(72, false, false, "Arial");
	m_DashText->SetColor(255, 255, 255, 255);

	m_HealText = new TextMgr();
	m_HealText->Init(72, false, false, "Arial");
	m_HealText->SetColor(255, 255, 255, 255);

	ObjMgr->AddObject(m_BGHpBar, "UI");
	ObjMgr->AddObject(m_HpBar, "UI");

	ObjMgr->AddObject(m_BGMpBar, "UI");
	ObjMgr->AddObject(m_MpBar, "UI");

	ObjMgr->AddObject(m_DashUI, "UI");
	ObjMgr->AddObject(m_DashBlind, "UI");

	ObjMgr->AddObject(m_HealUI, "UI");
	ObjMgr->AddObject(m_HealBlind, "UI");
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

	m_DashText->print(std::to_string((int)m_DashCooldown),m_DashBlind->m_Position.x - 30,m_DashBlind->m_Position.y - 50);

	m_DashText->print(std::to_string((int)m_HealCooldown), m_HealBlind->m_Position.x - 30, m_HealBlind->m_Position.y - 50);

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
