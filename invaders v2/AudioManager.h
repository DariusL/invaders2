#pragma once

#include "SoundCacheKey.h"
#include "includes.h"

class Sound;
class AudioManager
{
private:
	e::ComPtr<IXAudio2> m_XAudio2;
	IXAudio2MasteringVoice* m_MasteringVoice;
	XAUDIO2_VOICE_DETAILS m_VoiceDetails;

	e::unordered_map<SoundCacheKey, Sound> m_CachedSounds;
	static e::unique_ptr<AudioManager> s_Instance;

	AudioManager();
	AudioManager(const AudioManager& other);

public:
	~AudioManager();

	static void Initialize();
	static AudioManager& GetInstance();

	IXAudio2SourceVoice* CreateSourceVoice(const WAVEFORMATEX* waveFormat, IXAudio2VoiceCallback* voiceCallback);

	static Sound& GetCachedSound(const e::wstring& path, bool loopForever);
};