#include "includes.h"
#include "AudioManager.h"
#include "Sound.h"
#include "Utils.h"
#include "ResourceManager.h"

AudioManager *AudioManager::s_Instance;

static const float kSpeedOfSound = X3DAUDIO_SPEED_OF_SOUND;
static const int k3DAudioCalculationFlags = X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER | X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_REVERB;

AudioManager& AudioManager::GetInstance()
{
	return *s_Instance;
}

AudioManager::AudioManager() :song(-1)
{
	// Init XAudio2
	auto result = XAudio2Create(&m_XAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	Assert(result);
	s_Instance = this;

#if _DEBUG
	XAUDIO2_DEBUG_CONFIGURATION debugConfig;
	ZeroMemory(&debugConfig, sizeof(XAUDIO2_DEBUG_CONFIGURATION));

	debugConfig.TraceMask = XAUDIO2_LOG_WARNINGS | XAUDIO2_LOG_DETAIL;
	debugConfig.BreakMask = XAUDIO2_LOG_ERRORS;
	debugConfig.LogFileline = TRUE;
	debugConfig.LogFunctionName = TRUE;
	debugConfig.LogThreadID = TRUE;
	debugConfig.LogTiming = TRUE;

	m_XAudio2->SetDebugConfiguration(&debugConfig);
#endif

	result = m_XAudio2->CreateMasteringVoice(&m_MasteringVoice);
	Assert(result);

	// Init X3DAudio

	DWORD channelMask;
	XAUDIO2_DEVICE_DETAILS deviceDetails;
	result = m_XAudio2->GetDeviceDetails(0, &deviceDetails);
	Assert(result);

	channelMask = deviceDetails.OutputFormat.dwChannelMask;

	m_MasteringVoice->GetVoiceDetails(&m_VoiceDetails);

	songs = RM::ListFiles(L"Resources\\Music\\");
	e = GameObservers::Register(GAME_EVENT_ENEMY_BULLET_CREATE, e::bind(&AudioManager::PlayEnemyFire, this, e::placeholders::_1));
	p = GameObservers::Register(GAME_EVENT_PLAYER_BULLET_CREATE, e::bind(&AudioManager::PlayPlayerFire, this, e::placeholders::_1));
	bl = MenuObservers::Register(0, e::bind(&AudioManager::PlayBlip, this));
}

AudioManager::~AudioManager()
{
	m_CachedSounds.clear();

	if (m_MasteringVoice != nullptr)
	{
		m_MasteringVoice->DestroyVoice();
	}
}

IXAudio2SourceVoice* AudioManager::CreateSourceVoice(const WAVEFORMATEX* waveFormat, IXAudio2VoiceCallback* voiceCallback)
{
	HRESULT result;
	IXAudio2SourceVoice* sourceVoice;

	result = m_XAudio2->CreateSourceVoice(&sourceVoice, waveFormat, XAUDIO2_VOICE_USEFILTER, XAUDIO2_DEFAULT_FREQ_RATIO, voiceCallback);

	Assert(result);
	return sourceVoice;
}

Sound& AudioManager::GetCachedSound(const e::wstring& path, bool music)
{
	auto& sound = s_Instance->m_CachedSounds.find(path);

	if (sound == s_Instance->m_CachedSounds.end())
	{
		s_Instance->m_CachedSounds.emplace(path, Sound(path, music));
		sound = s_Instance->m_CachedSounds.find(path);
	}

	return sound->second;
}

void AudioManager::PlayNextSong()
{
	auto &a = GetInstance();
	a.song++;
	if (a.song >= (int)a.songs.size())
		a.song = a.songs.size() - 1;
	if (a.song != -1)
		a.GetCachedSound(a.songs[a.song], true).Play(1.0f);
}

void AudioManager::PlayPlayerFire(e::shared_ptr<GameEntity>)
{
	GetCachedSound(L"Resources\\Sounds\\player.wav", false).Play(1.0f);
}

void AudioManager::PlayEnemyFire(e::shared_ptr<GameEntity>)
{
	GetCachedSound(L"Resources\\Sounds\\enemy.wav", false).Play(1.0f);
}

void AudioManager::PlayBlip()
{
	GetCachedSound(L"Resources\\Sounds\\blip.wav", false).Play(1.0f);
}