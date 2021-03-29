#pragma once
#include "AudioSystem.h"
namespace Idiot_Engine
{
	class NullSoundSystem final: public AudioSystem
	{
	public:
		NullSoundSystem() = default;
		
		SoundID AddSound(const std::string&) override { return NULL; };
		MusicID AddMusic(const std::string&) override { return NULL; };

		void Update(const float) override {};

		void PauseMusic() override {};
		void PauseSound(const SoundID) override {};

		void RewindMusic() override {};
		//void SetMusicStartTime(double time) override {};

		void SetSoundVolume(const SoundID, const int) override {};
		void SetMusicVolume(const int) override {};

		void ToggleMute() override{};
		
		[[nodiscard]] bool IsMusicPlaying() const override { return false; };
		[[nodiscard]] bool IsSoundPlaying(const SoundID) const override { return false; };

		[[nodiscard]] int GetSoundVolume(const SoundID) const override { return 0; };
		[[nodiscard]] int GetMusicVolume() const override { return 0; }
		
		void QueueSound(const SoundID, const int) override{};
		void QueueMusic(const MusicID, const int) override{};

	private:
		void PlaySound(const SoundID, const int) override {};
		void PlayMusic(const MusicID, const int) override {};
	};
}
