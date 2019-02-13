#pragma once
#include "../SceneManager.h"

class MeshFiled;
class LosePlayer;
class Fade;
class Polygon2D;
class PolygonColorChanger;

class SceneLoseResult : public SceneManager
{
public:
	SceneLoseResult() {}
	~SceneLoseResult() {}
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
public:
	static MeshFiled* GetMeshFiled();
	static LosePlayer* GetLostPlayer();
	static Fade* GetFade();
	static Polygon2D* GetSepiaPolygon();
	static Polygon2D* GetGameOverPolygon();
	static Polygon2D* GetPressButtonPolygon();
	static bool GetSepiaFlag();
	static void SetSepiaFlag(bool _flag);
	static bool GetGameOverFlag();
	static void SetGameOverFlag(bool _flag);
private:
	static MeshFiled* LostResultMeshFiled_;
	static LosePlayer* LostResultPlayer_;
	static Fade* fade_;
	static Polygon2D* SepiaPolygon_;
	static Polygon2D* GameOverPolygon_;
	static Polygon2D* PressButtonWord_;
	static bool SepiaColorFlag_;
	static bool GameOverDrawFlag_;
};