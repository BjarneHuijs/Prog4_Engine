#pragma once
#include "Structs.h"
namespace Idiot_Engine
{
    class AudioSystem
    {
    public:
        virtual ~AudioSystem() = default;
        //virtual bool OnEvent(const Event& event) = 0;

        virtual SoundID AddSound(const std::string& filePath) = 0;
        virtual MusicID AddMusic(const std::string& filePath) = 0;

        virtual void Update(const float deltaTime) = 0;

        virtual void QueueSound(const SoundID soundID, const int volume = 100) = 0;
		virtual void QueueMusic(const MusicID musicID, const int volume = 100) = 0;

        virtual void PauseMusic() = 0;
        virtual void PauseSound(const SoundID soundID) = 0;

        virtual void RewindMusic() = 0;
        //virtual void SetMusicStartTime(double time) = 0;

        virtual void SetSoundVolume(const SoundID soundID, const int volume) = 0;
        virtual void SetMusicVolume(const int volume) = 0;

        virtual void ToggleMute() = 0;
    	
        [[nodiscard]] virtual bool IsMusicPlaying() const = 0;
        [[nodiscard]] virtual bool IsSoundPlaying(const SoundID soundID) const = 0;

        [[nodiscard]] virtual int GetSoundVolume(const SoundID soundID) const = 0;
        [[nodiscard]] virtual int GetMusicVolume() const = 0;

    private:
        virtual void PlaySound(const SoundID soundID, const int volume = 100) = 0;
        virtual void PlayMusic(const MusicID soundID, const int volume = 100) = 0;
    };
}