#pragma once
class UI : public Singleton<UI>
{
	Sprite* m_BGHpBar;
	Sprite* m_HpBar;

	TextMgr* m_HpText;
public:
	UI();
	~UI();

	int m_MaxHp;
	int m_Hp;
	float m_HpGage;

	void Init();
	void Release();

	void Update();
	void Render();
};

