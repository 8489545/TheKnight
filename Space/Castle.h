#pragma once
class Castle : public Scene
{
	Sprite* m_BG;
public:
	Castle();
	~Castle();

	void Init();
	void Release();

	void Update(float deltaTime, float Time);
	void Render();
};

