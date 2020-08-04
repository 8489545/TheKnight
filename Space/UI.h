#pragma once
class UI : public Singleton<UI>
{
	Sprite* m_BGHpBar;
	Sprite* m_HpBar;

	TextMgr* m_HpText;

	Sprite* m_BGMpBar;
	Sprite* m_MpBar;

	TextMgr* m_MpText;
public:
	UI();
	~UI();

	int m_MaxHp;
	int m_Hp;
	float m_HpGage;

	int m_MaxMp;
	int m_Mp;
	float m_MpGage;

	void Init();
	void Release();

	void Update();
	void Render();
};

