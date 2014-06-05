#include "includes.h"
#include "AudioManager.h"
#include "Sound.h"
#include "Utils.h"

e::unique_ptr<AudioManager> AudioManager::s_Instance;

static const float kSpeedOfSound = X3DAUDIO_SPEED_OF_SOUND;
static const int k3DAudioCalculationFlags = X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER | X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_REVERB;

void AudioManager::Initialize()
{
	using namespace e;
	AssertBool(s_Instance == nullptr, L"audio manager already inited");
	s_Instance = e::unique_ptr<AudioManager>(new AudioManager());
}

AudioManager& AudioManager::GetInstance()
{
	return *s_Instance;
}

AudioManager::AudioManager()
{
	// Init XAudio2

	auto result = XAudio2Create(&m_XAudio2);
	Assert(result);

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

Sound& AudioManager::GetCachedSound(const e::wstring& path, bool loopForever)
{
	SoundCacheKey key(path, loopForever);
	auto& sound = s_Instance->m_CachedSounds.find(key);

	if (sound == s_Instance->m_CachedSounds.end())
	{
		s_Instance->m_CachedSounds.emplace(key, Sound(path, loopForever));
		sound = s_Instance->m_CachedSounds.find(key);
	}

	return sound->second;
}