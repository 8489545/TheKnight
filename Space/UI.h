#pragma once
class UI : public Singleton<UI>
{
	Sprite* m_BGHpBar;
	Sprite* m_HpBar;

	Sprite* m_BGMpBar;
	Sprite* m_MpBar;

	Sprite* m_DashUI;
	Sprite* m_DashBlind;

	Sprite* m_HealUI;
	Sprite* m_HealBlind;

	TextMgr* m_HpText;
	TextMgr* m_MpText;
	TextMgr* m_DashText;
	TextMgr* m_HealText;

public:
	UI();
	~UI();

	int m_MaxHp;
	int m_Hp;
	float m_HpGage;

	int m_MaxMp;
	int m_Mp;
	float m_MpGage;

	float m_DashCooldown;
	float m_HealCooldown;

	void Init();
	void Release();

	void Update();
	void Render();
};

