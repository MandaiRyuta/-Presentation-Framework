#pragma once
#include <Windows.h>
#include <XAudio2.h>
#include <XAudio2fx.h>
#include "../Entity/Entity.h"

class EffectSound {
public:
	enum SOUND_LABEL {
		SOUND_SELECT01,
		SOUND_TITLE,
		//SOUND_CHUTORIAL,
		//SOUND_GAME,
		//SOUND_WINRESULT,
		//SOUND_LOSERESULT,
		//SOUND_PLAYER_ATTACK,
		//SOUND_PLAYER_MAGIC,
		//SOUND_ENEMY_ATTACK,
		//SOUND_ENEMY_MAGIC,
		//SOUND_SELECT01,
		//SOUND_SELECT02,
		//SOUND_PAUSE_SOUND,
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
		{ "Resource/Sound/Button02.wav",0 },
		{ "Resource/Sound/TitleBGM.wav",1 },
	};
};