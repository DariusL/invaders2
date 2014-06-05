#pragma once

#include "includes.h"

class Sound
{
private:
	struct Voice
	{
		IXAudio2SourceVoice* sourceVoice;
		volatile bool isPlaying;

		Voice(IXAudio2SourceVoice* sourceVoice, bool isPlaying) :
			sourceVoice(sourceVoice), isPlaying(isPlaying) {}

		Voice(Voice&& other) :
			sourceVoice(other.sourceVoice),
			isPlaying(other.isPlaying)
		{
			other.sourceVoice = nullptr;
			other.isPlaying = false;
		}

	private:
		Voice(const Voice& other);
	};

	class SoundCallbacks : public IXAudio2VoiceCallback
	{
	private:
		Sound* m_Sound;

		virtual void __stdcall OnVoiceProcessingPassStart(UINT32 bytesRequired) { }
		virtual void __stdcall OnVoiceProcessingPassEnd() { }
		virtual void __stdcall OnStreamEnd() { }

		virtual void __stdcall OnBufferStart(void* pBufferContext) { }
		virtual void __stdcall OnBufferEnd(void* pBufferContext)
		{
			auto index = reinterpret_cast<size_t>(pBufferContext);
			m_Sound->m_Voices[index].isPlaying = false;
		}

		virtual void __stdcall OnLoopEnd(void* pBufferContext) { }
		virtual void __stdcall OnVoiceError(void* pBufferContext, HRESULT error) { __debugbreak(); }

	public:
		SoundCallbacks(Sound* sound) : m_Sound(sound) { }
		virtual ~SoundCallbacks() { }
	};

	e::unique_ptr<char[]> m_SoundDataBuffer;
	XAUDIO2_BUFFER m_AudioBuffer;
	WAVEFORMATEXTENSIBLE m_WaveFormat;

	e::vector<Voice> m_Voices;
	SoundCallbacks m_SoundCallbacks;

	size_t GetNotPlayingVoiceIndex();
	size_t CreateVoice();
	Voice& GetVoiceForPlayback();
	void PlayImpl(Voice& voiceToPlay);

	friend class SoundCallbacks;
	Sound(const Sound& other);

public:
	Sound(const e::wstring& waveFilePath, bool loopForever);
	Sound(Sound&& other);
	~Sound();

	void Play(float vol);
};