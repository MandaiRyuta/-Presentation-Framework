//#pragma once
//
//#include "../../../GameObjectManager/GameObjectManager.h"
//#include "../../../Entity/Entity.h"
//
//class Timer : public GameObjectManager
//{
//public:
//	Timer(int priority) : GameObjectManager(priority);
//	~Timer();
//
//public:
//	void Init() override;
//	void Update() override;
//	void Draw() override;
//	void Uninit() override;
//
//	// n‚É‚Í‚O`‚X‚Ü‚Å‚Ì”š
//	// ‚±‚ÌŠÖ”‚Í”š1•¶š‚ğ•\¦
//	void DrawNumber(int n, float x, float y);
//	void DrawNumberScore(int n, float x, float y);
//	// dig:ƒXƒRƒA‚ÌŒ…”
//	void DrawTimer(int nTime, int dig, bool bZero, float x, float y, int ver);
//	bool InitPolygon(void);
//	void UninitPolygon(void);
//	void DrawPolygon(TEXTURENUM texNum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, bool bAffine);
//	void CreateVertexAffine(int texNum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);
//	void CreateVertex(int texNum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch);
//	void SetPolygonRotation(float cx, float cy, float fangle);
//	void SetPolygonScale(float scaleX, float scaleY);
//	static Timer* Create(int Priority);
//public:
//	float g_fPolygonAngle = 0.0f;
//	float g_fRotationOffsetX = 0.0f;
//	float g_fRotationOffsetY = 0.0f;
//	float g_fScaleX = 1.0f;
//	float g_fScaleY = 1.0f;
//	float g_fScaleOFFsetX = 0.0f;
//	float g_fScaleOFFsetY = 0.0f;
//};
