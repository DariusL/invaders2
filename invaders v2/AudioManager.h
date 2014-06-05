#pragma once

#include "SoundCacheKey.h"
#include "includes.h"
#include "GameEntity.h"
#include "Observers.h"

class Sound;
class AudioManager
{
private:
	e::ComPtr<IXAudio2> m_XAudio2;
	IXAudio2MasteringVoice* m_MasteringVoice;
	XAUDIO2_VOICE_DETAILS m_VoiceDetails;

	e::unordered_map<e::wstring, Sound> m_CachedSounds;
	static AudioManager *s_Instance;

	AudioManager(const AudioManager& other);
	static Sound& GetCachedSound(const e::wstring& path, bool music);

	void PlayPlayerFire(e::shared_ptr<GameEntity>);
	void PlayEnemyFire(e::shared_ptr<GameEntity>);
	void PlayBlip();

	e::vector<e::wstring> songs;
	int song;
	e::wstring playerFire;
	e::wstring enemyFire;
	GameObservers::ObserverScopeRef e, p;
	MenuObservers::ObserverScopeRef bl;
public:
	AudioManager();
	~AudioManager();

	static AudioManager& GetInstance();

	IXAudio2SourceVoice* CreateSourceVoice(const WAVEFORMATEX* waveFormat, IXAudio2VoiceCallback* voiceCallback);
	static void PlayNextSong();
};