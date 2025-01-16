#include <iostream>

#include "Engine/Engine.h"
#include "Level/TestLevel.h"

Engine* engine = nullptr;

BOOL CtrlHandler(DWORD fdwCtrlType) {
	switch (fdwCtrlType) {
	case CTRL_CLOSE_EVENT:
		if (engine != nullptr) {
			delete engine;
			engine = nullptr;
		}
		// 정리 작업 수행
		return TRUE;
	default:
		return FALSE;
	}
}

int main()
{
	CheckMemoryLeak();

	engine = new Engine();

	engine->LoadLevel(new TestLevel());
	engine->Run();

	if (engine != nullptr) {
		delete engine;
		engine = nullptr;
	}
 }