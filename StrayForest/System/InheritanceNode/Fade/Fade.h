#pragma once
#include "../../../GameObjectManager/GameObjectManager.h"
#include "../../../Entity/Entity.h"

struct FADE_VERTEX
{
	float x, y, z;
	DWORD color;
};

class Fade : public GameObjectManager
{
public:
	Fade() : GameObjectManager(2) {}
	~Fade() {}
public:
	void Init() override;
	void Uninit() override;
	void Draw() override;
	void Update() override;

	void BlackFadeIn();
	void BlackFadeOut();
	void WhiteFadeIn();
	void WhiteFadeOut();
	bool GetFadeFlag();
	void FadeSetNumber(int fade);
public:
	static Fade* Create();
private:
	int FadeIn;
	int FadeOut;
	int FadeSet_;
	bool BlackFadeInFlag_;
	bool BlackFadeOutFlag_;
	bool WhiteFadeInFlag_;
	bool WhiteFadeOutFlag_;
};