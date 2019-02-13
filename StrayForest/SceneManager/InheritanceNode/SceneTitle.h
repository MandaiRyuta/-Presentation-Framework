#pragma once
#include "../SceneManager.h"
#include "../../System/InheritanceNode/Fade/Fade.h"
#include "../../System/Polygon2D.h"
class Fade;

class SceneTitle : public SceneManager
{
public:
	SceneTitle() {}
	~SceneTitle() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	static Polygon2D* GetTitleStartBar();
	static Fade* GetFade();
private:
	static Polygon2D* TitleStartBar_;
	static Fade* fade_;
};