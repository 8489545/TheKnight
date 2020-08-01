#include "stdafx.h"
#include "MainScene.h"
#include"Player.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	ObjMgr->AddObject(new Player(), "Player");

	UI::GetInst()->Init();
}

void MainScene::Release()
{
}

void MainScene::Update(float deltaTime, float time)
{
}

void MainScene::Render()
{
}
