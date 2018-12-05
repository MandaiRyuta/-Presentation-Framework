#pragma once
#include <Windows.h>
#include <XAudio2.h>
#include <XAudio2fx.h>
#include "../Entity/Entity.h"

class EffectSound {
public:
	enum SOUND_LABEL {
		SOUND_ATTACK,
		SOUND_NONE,
	};
public:
	EffectSound(SOUND_LABEL LabelName) : m_SoundName_(LabelName) {}
	~EffectSound() {}
public:
	static HRESULT InitSound(HWND hWnd);
	static Entity::EffectSoundParameter InitEffectSound();
	static void UninitSound();
	static HRESULT SetEffectSound(SOUND_LABEL label, Entity::EffectSoundParameter Effectinfo);
	static HRESULT PlaySound(SOUND_LABEL label);
	static HRESULT SoundVolume(SOUND_LABEL label, float Volume);
	static HRESULT DirectionSound(SOUND_LABEL label, float LeftVolume, float RightVolume);
	static void StopSound(SOUND_LABEL label);
	static void StopSound(void);
	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
private:
	SOUND_LABEL m_SoundName_;
	static IXAudio2* m_pXAudio2_; // nullptr
	static IXAudio2MasteringVoice* m_pMasteringVoice_; // nullptr
	static IXAudio2SourceVoice* m_apSourceVoice_[SOUND_LABEL::SOUND_NONE]; //{}
	static BYTE* m_apDataAudio_[SOUND_LABEL::SOUND_NONE]; //{}
	static DWORD m_aSizeAudio_[SOUND_LABEL::SOUND_NONE]; //{}
	static IUnknown* m_pXAPO_;// nullptr
	static XAUDIO2_EFFECT_DESCRIPTOR m_descriptor_;
	static XAUDIO2_EFFECT_CHAIN m_chain_;

	typedef struct {
		char* pFilename;
		int nCntLoop;
	}SOUNDPARAM;

	static SOUNDPARAM m_aParam[SOUND_LABEL::SOUND_NONE];
};