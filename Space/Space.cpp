#include"stdafx.h"
#include"Castle.h"

#pragma warning(disable:26495)

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
#if _DEBUG
	AllocConsole();
	FILE* stream;
	freopen_s(&stream, "CONOUT$", "wt", stdout);

#endif
	App::GetInst()->Init(1920, 1080, 1);
	SceneDirector::GetInst()->ChangeScene(new Castle());
	App::GetInst()->Run();
	return 0;
}