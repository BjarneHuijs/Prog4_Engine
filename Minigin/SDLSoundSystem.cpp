#include "MiniginPCH.h"
#include "SDLSoundSystem.h"

using namespace Idiot_Engine;
SDLSoundSystem::SDLSoundSystem()
	: m_pCurrentMusic{nullptr}
	, m_Muted(false)
{
	m_AudioPlaying.store(true);
	auto* self = this;
	m_AudioServiceThread = std::thread([self]() { self->Update2(); });
	/*for(uint16_t i{}; i < Mix_AllocateChannels(-1); i++)
	{
		
	}*/
}

SDLSoundSystem::~SDLSoundSystem()
{
	// Free Sounds
	for(const auto& soundPair: m_pLoadedSounds)
	{
		Mix_FreeChunk(soundPair.second);
	}

	// Free Music
	for(const auto& musicPair: m_pLoadedMusic)
	{
		Mix_FreeMusic(musicPair.second);
	}

	m_AudioPlaying.store(false);
	m_QueueCondition.notify_one();
	m_AudioServiceThread.join();
}

SoundID SDLSoundSystem::AddSound(const std::string& filePath)
{
	SoundID newId{};

	if(m_pLoadedSounds.empty())
	{
		newId = 0;
	}
	else
	{
		newId = { m_pLoadedSounds.rbegin()->first + 1 };
	}

	Mix_Chunk* sound{ Mix_LoadWAV(filePath.c_str()) };
	if(!sound)
	{
		// file not found
		std::cout << Mix_GetError() << std::endl;
		return -1;
	}else
	{
		m_pLoadedSounds.insert(std::make_pair(newId, sound));
	}

	return newId;
	
}

MusicID SDLSoundSystem::AddMusic(const std::string& filePath)
{
	MusicID newID;

	if (m_pLoadedMusic.empty())
	{
		newID = 0;
	}
	else
	{
		newID = { m_pLoadedMusic.rbegin()->first + 1 };
	}

	Mix_Music* music{ Mix_LoadMUS(filePath.c_str()) };
	if (!music)
	{
		// file not found
		return -1;
	}
	else
	{
		m_pLoadedMusic.insert(std::make_pair(newID, music));
	}

	return newID;
	
}

void SDLSoundSystem::Update(const float)
{
	
}

// TODO: Implement looping audio / Music
void SDLSoundSystem::Update2()
{
	while (m_AudioPlaying.load())
	{
		// lock
		std::unique_lock<std::mutex> lock{ m_QueueLock };
		m_QueueCondition.wait(lock, [this]() {return (!m_SoundQueue.empty() || !m_MusicQueue.empty()) || m_AudioPlaying.load() == false; });

		while(!m_SoundQueue.empty())
		{
			const QueuedSound sound = m_SoundQueue.front();
			
			m_SoundQueue.pop();
			if(!m_Muted)
			{
				PlaySound(sound.id, sound.volume);
			}
		}

		while(!m_MusicQueue.empty())
		{
			const QueuedMusic music = m_MusicQueue.front();

			m_MusicQueue.pop();
			if(!m_Muted)
			{
				PlayMusic(music.id, music.volume);
			}
		}

		// unlock / wait not necessary since it goes out of scope after the outer while loop finishes
	}
}

void SDLSoundSystem::QueueSound(const SoundID soundID, const int volume)
{
	// Empty brackets to force the lock to go out of scope => unlocks value to ensure continuation of service
	{
		std::unique_lock<std::mutex> lock{ m_QueueLock };
		m_SoundQueue.push(QueuedSound{ soundID, volume });
	}

	m_QueueCondition.notify_one();
}

void SDLSoundSystem::QueueMusic(const MusicID musicID, const int volume)
{
	// Empty brackets to force the lock to go out of scope => unlocks value to ensure continuation of service
	{
		std::unique_lock<std::mutex> lock{ m_QueueLock };
		m_MusicQueue.push(QueuedMusic{ musicID, volume });
	}

	m_QueueCondition.notify_one();
}

// currently not handling channels manually (might do this later if i want to check if certain sound is playing)
void SDLSoundSystem::PlaySound(const SoundID soundID, const int volume)
{
	
	if(m_pLoadedSounds.find(soundID) != m_pLoadedSounds.end())
	{
		Mix_Chunk* sound{ m_pLoadedSounds.at(soundID) };
		Mix_VolumeChunk(sound, volume);
		if(Mix_PlayChannel(-1, sound, 0) == -1) 
		{
			// something went wrong

		}
		
		// playing sound
	}
}

void SDLSoundSystem::PlayMusic(const MusicID musicID, const int volume)
{
	if (m_pLoadedMusic.find(musicID) != m_pLoadedMusic.end())
	{
		Mix_Music* music{ m_pLoadedMusic.at(musicID) };
		Mix_VolumeMusic(volume);
		if (Mix_PlayMusic(music, 0) == -1)
		{
			// something went wrong

		}

		m_pCurrentMusic = music;
		// playing music
	}
}

void SDLSoundSystem::PauseMusic()
{
	Mix_PauseMusic();
	m_pCurrentMusic = nullptr;
}

void SDLSoundSystem::PauseSound(const SoundID soundID)
{
	for (int channel{}; channel < MIX_CHANNELS; channel++) 
	{
		const auto target{ m_pLoadedSounds.at(soundID) };
		if(Mix_GetChunk(channel) == target)
			Mix_Pause(channel);
	}
}

void SDLSoundSystem::RewindMusic()
{
	Mix_RewindMusic();
}

//void SDLSoundSystem::SetMusicStartTime(double time)
//{
//	switch(Mix_GetMusicType(m_pCurrentMusic))
//	{
//	case MUS_OGG:
//	case MUS_MOD:
//		if(Mix_SetMusicPosition(time) == -1)
//		{
//			// failed
//			bool error = true;
//		}
//		
//		break;
//	case MUS_MP3:
//		RewindMusic();
//		if(Mix_SetMusicPosition(time) == -1)
//		{
//			// failed
//			bool error = true;
//		}
//
//		break;
//	default:
//		// unsupported type
//		bool error = true;
//		break;
//	}
//	
//}

void SDLSoundSystem::SetSoundVolume(const SoundID soundID, const int volume)
{
	if(m_pLoadedSounds.find(soundID) != m_pLoadedSounds.cend())
	{
		Mix_VolumeChunk(m_pLoadedSounds.at(soundID), VolumeToSDL(volume));
	}
	else
	{
		// error

	}
}

void SDLSoundSystem::SetMusicVolume(const int volume)
{
	Mix_VolumeMusic(VolumeToSDL(volume));
}

void SDLSoundSystem::ToggleMute()
{
	m_Muted = !m_Muted;
}

bool SDLSoundSystem::IsMusicPlaying() const
{
	return Mix_PlayingMusic() == 1;
}

bool SDLSoundSystem::IsSoundPlaying(const SoundID soundID) const
{
	for (int channel{}; channel < MIX_CHANNELS; channel++)
	{
		const auto target{ m_pLoadedSounds.at(soundID) };
		if (Mix_GetChunk(channel) == target) 
		{
			return Mix_Playing(channel) == 1;
		}
		else 
		{
			// sound not playing on this channel

		}
	}
	return false;
}

int SDLSoundSystem::GetSoundVolume(const SoundID soundID) const
{
	if(m_pLoadedSounds.find(soundID) != m_pLoadedSounds.cend())
	{
		// -1 in volume returns current volume
		return SDLVolumeToInt(Mix_VolumeChunk(m_pLoadedSounds.find(soundID)->second, -1));
	}
	else
	{
		// sound not found
	}
	return 0;
}

int SDLSoundSystem::GetMusicVolume() const
{
	// -1 in volume returns current volume
	return SDLVolumeToInt(Mix_VolumeMusic(-1));
}

// sdl volume conversions and related reference sources were given by Rhidian | credit goes to him
int SDLSoundSystem::VolumeToSDL(const int volume) const
{
	return ((volume * MIX_MAX_VOLUME) / 100);

	//NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
	// Reference: https://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
}

int SDLSoundSystem::SDLVolumeToInt(const int sdlVolume) const
{
	return ((sdlVolume * 100) / MIX_MAX_VOLUME);

	//NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
	// Reference: https://stackoverflow.com/questions/929103/convert-a-number-range-to-another-range-maintaining-ratio
}
