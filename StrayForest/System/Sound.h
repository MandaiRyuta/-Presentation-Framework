#pragma once
#include <Windows.h>
#include <XAudio2.h>
#include <XAudio2fx.h>
#include "../Entity/Entity.h"

class EffectSound {
public:
	enum SOUND_LABEL {
		SOUND_ENEMYMAGIC01,
		SOUND_ENEMYMAGIC02,
		SOUND_ENEMYMAGIC03,
		SOUND_PLAYERATTACK,
		//SOUND_PLAYERRUN,
		//SOUND_PLAYERWALK,
		SOUND_PLAYERMAGIC,
		SOUND_POSE,
		SOUND_SELECT,
		SOUND_TITLE1,
		SOUND_TITLE2,
		SOUND_CHUTORIAL,
		SOUND_GAME,
		SOUND_LOSE,
		SOUND_WIN,
		SOUND_NONE,
	};
public:
	EffectSound() {}
	~EffectSound() {}
public:
	HRESULT InitSound(HWND hWnd);
	Entity::EffectSoundParameter InitEffectSound();
	void UninitSound();
	HRESULT SetEffectSound(SOUND_LABEL label, Entity::EffectSoundParameter Effectinfo);
	HRESULT PlaySound(SOUND_LABEL label);
	HRESULT SoundVolume(SOUND_LABEL label, float Volume);
	HRESULT DirectionSound(SOUND_LABEL label, float LeftVolume, float RightVolume);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
private:
	IXAudio2* m_pXAudio2_; // nullptr
	IXAudio2MasteringVoice* m_pMasteringVoice_; // nullptr
	IXAudio2SourceVoice* m_apSourceVoice_[SOUND_LABEL::SOUND_NONE]; //{}
	BYTE* m_apDataAudio_[SOUND_LABEL::SOUND_NONE]; //{}
	DWORD m_aSizeAudio_[SOUND_LABEL::SOUND_NONE]; //{}
	IUnknown* m_pXAPO_;// nullptr
	XAUDIO2_EFFECT_DESCRIPTOR m_descriptor_;
	XAUDIO2_EFFECT_CHAIN m_chain_;

	typedef struct {
		char* pFilename;
		int nCntLoop;
	}SOUNDPARAM;

	SOUNDPARAM m_aParam[SOUND_LABEL::SOUND_NONE] = {
		{ "Resource/Sound/MD Enemymagic1.wav",0 },
		{ "Resource/Sound/MD enemymagic2.wav",0 },
		{ "Resource/Sound/MD enemymagic3.wav",0 },
		{ "Resource/Sound/PlayerAttack.wav",0 },
		//{ "Resource/Sound/PlayerRun.wav", 0 },
		//{ "Resource/Sound/PlayerWalk.wav", 0 },
		{ "Resource/Sound/MD playmagic.wav", 0},
		{ "Resource/Sound/MD pose.wav",0 },
		{ "Resource/Sound/MD Select.wav",0 },
		{ "Resource/Sound/MD title1.wav",1 },
		{ "Resource/Sound/MD title2.wav",1 },
		{ "Resource/Sound/MD trail.wav",1 },
		{ "Resource/Sound/MD Battle.wav",1 },
		{ "Resource/Sound/MD lose.wav",1 },
		{ "Resource/Sound/MD win.wav",1 },

	};
};