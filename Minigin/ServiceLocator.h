#pragma once
#include "MiniginPCH.h"
#include <type_traits>
#include "AudioSystem.h"
#include "NullSoundSystem.h"

namespace Idiot_Engine
{

	class ServiceLocator final
	{

	public:
		//static void RegisterSoundService(AudioSystem* service) { m_pSoundService = service == nullptr ? m_pNullSoundService : service; }

		//static AudioSystem& GetSoundService() { return *m_pSoundService; }



		static void Cleanup();

		[[nodiscard]] inline static AudioSystem* GetAudio()
		{
			if (m_pSoundService)
				return m_pSoundService;

			//Logger::LogWarning("GetAudio returned NullAudioService\n");
			return m_pNullSoundService;
		}

		template<typename ServiceType>
		inline static void RegisterAudioService(ServiceType* pService)
		{
			if constexpr (std::is_base_of_v<AudioSystem, ServiceType>)
			{
				if (pService != nullptr && !std::is_same_v<ServiceType, NullSoundSystem>)
				{
					m_pSoundService = pService;
				}
			}
			else
				static_assert(false, "The input pointer was not an AudioSystem");
		}

	private:
		ServiceLocator() = default;

		inline static AudioSystem* m_pSoundService{};
		inline static AudioSystem* m_pNullSoundService{ new NullSoundSystem{} };
	};

	inline void ServiceLocator::Cleanup()
	{
		Safe_Delete(m_pSoundService);
		Safe_Delete(m_pNullSoundService);
	}
}
