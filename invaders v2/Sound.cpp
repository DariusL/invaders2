#include "includes.h"
#include "AudioManager.h"
#include "RiffFile.h"
#include "Sound.h"
#include "Utils.h"

Sound::Sound(const e::wstring& waveFilePath, bool loopForever) :
m_SoundCallbacks(this)
{
	using namespace e;
	auto waveFile = RiffFile::Create(waveFilePath);
	AssertBool(waveFile.GetFormat() == RiffFourCC::WAVE, L"not wav");

	ZeroMemory(&m_WaveFormat, sizeof(m_WaveFormat));
	ZeroMemory(&m_AudioBuffer, sizeof(m_AudioBuffer));

	const auto& formatChunk = waveFile.GetChunk(RiffFourCC::FMT);
	AssertBool(sizeof(m_WaveFormat) >= formatChunk.GetSize(), L"dunno");
	memcpy(&m_WaveFormat, formatChunk.GetData(), formatChunk.GetSize());

	auto& dataChunk = waveFile.GetChunk(RiffFourCC::DATA);
	m_SoundDataBuffer = std::move(dataChunk.GetDataBuffer());

	m_AudioBuffer.AudioBytes = dataChunk.GetSize();
	m_AudioBuffer.pAudioData = (byte*)m_SoundDataBuffer.get();
	m_AudioBuffer.Flags = XAUDIO2_END_OF_STREAM;
	m_AudioBuffer.LoopCount = loopForever ? XAUDIO2_LOOP_INFINITE : 0;
}

Sound::Sound(Sound&& other) :
m_SoundDataBuffer(std::move(other.m_SoundDataBuffer)),
m_AudioBuffer(other.m_AudioBuffer),
m_WaveFormat(other.m_WaveFormat),
m_Voices(std::move(other.m_Voices)),
m_SoundCallbacks(this)
{
	other.m_AudioBuffer.pAudioData = nullptr;
	other.m_AudioBuffer.pContext = nullptr;
}

Sound::~Sound()
{
	for (auto& voice : m_Voices)
	{
		voice.sourceVoice->DestroyVoice();
	}
}

size_t Sound::GetNotPlayingVoiceIndex()
{
	auto voiceCount = m_Voices.size();

	for (size_t i = 0u; i < voiceCount; i++)
	{
		if (!m_Voices[i].isPlaying)
		{
			return i;
		}
	}

	// All voices are playing
	return CreateVoice();
}

size_t Sound::CreateVoice()
{
	auto sourceVoice = AudioManager::GetInstance().CreateSourceVoice(reinterpret_cast<WAVEFORMATEX*>(&m_WaveFormat), &m_SoundCallbacks);

	m_Voices.emplace_back(sourceVoice, false);
	return m_Voices.size() - 1;
}

Sound::Voice& Sound::GetVoiceForPlayback()
{
	HRESULT result;

	auto i = GetNotPlayingVoiceIndex();
	auto& voice = m_Voices[i];

	m_AudioBuffer.pContext = reinterpret_cast<void*>(i);
	result = voice.sourceVoice->SubmitSourceBuffer(&m_AudioBuffer);
	Assert(result);

	return voice;
}

void Sound::PlayImpl(Voice& voiceToPlay)
{
	voiceToPlay.isPlaying = true;
	auto result = voiceToPlay.sourceVoice->Start();
	Assert(result);
}

void Sound::Play(float vol)
{
	auto &voice = GetVoiceForPlayback();
	voice.sourceVoice->SetVolume(vol);
	PlayImpl(voice);
}