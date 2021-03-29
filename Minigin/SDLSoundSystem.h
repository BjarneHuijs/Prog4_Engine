#pragma once
#include <map>
#include <thread>
#include <queue>
#include <mutex>

#include "AudioSystem.h"

namespace Idiot_Engine
{
	class SDLSoundSystem : public AudioSystem
	{
	public:
		SDLSoundSystem();
		virtual ~SDLSoundSystem();

		//virtual bool OnEvent(const Event& event) override;

		virtual SoundID AddSound(const std::string& filePath) override;
		virtual MusicID AddMusic(const std::string& filePath) override;

		virtual void Update(const float deltaTime) override;
		void Update2();

		void QueueSound(const SoundID soundID, const int volume = 100) override;
		void QueueMusic(const MusicID musicID, const int volume = 100) override;

		void PauseMusic() override;
		void PauseSound(const SoundID soundID) override;

		void RewindMusic() override;
		//void SetMusicStartTime(double time) override;

		void SetSoundVolume(const SoundID soundID, const int volume) override;
		void SetMusicVolume(const int volume) override;

		void ToggleMute() override;
		
		[[nodiscard]] bool IsMusicPlaying() const override;
		[[nodiscard]] bool IsSoundPlaying(const SoundID soundID) const override;

		[[nodiscard]] int GetSoundVolume(const SoundID soundID) const override;
		[[nodiscard]] int GetMusicVolume() const override;
	private:
		std::map<SoundID, Mix_Chunk*> m_pLoadedSounds{};
		std::map<MusicID, Mix_Music*> m_pLoadedMusic{};

		Mix_Music* m_pCurrentMusic = nullptr;
		bool m_Muted;
		std::atomic<bool> m_AudioPlaying;
		std::thread m_AudioServiceThread;

		std::queue<QueuedSound> m_SoundQueue{};
		std::queue<QueuedMusic> m_MusicQueue{};

		std::mutex m_QueueLock;
		std::condition_variable m_QueueCondition;

		void PlaySound(const SoundID soundID, const int volume = 100) override;
		void PlayMusic(const MusicID musicID, const int volume = 100) override;

		[[nodiscard]] int VolumeToSDL(const int volume) const;
		[[nodiscard]] int SDLVolumeToInt(const int sdlVolume) const;
		
	};
}
