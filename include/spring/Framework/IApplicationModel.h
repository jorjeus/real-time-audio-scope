#pragma once
#include <Spring/Framework/IScene.h>
#include <Spring/Framework/global.h>

namespace Spring
{

	class Framework_EXPORT_IMPORT_API IApplicationModel
	{
	public:

		virtual void defineScene() = 0;

		virtual void defineInitialScene() = 0;

		virtual void defineTransientData() = 0;

		virtual const std::string& sGetInitialSceneName()
		{
			return mv_szInitialScene;
		}

		std::map<const std::string, IScene*> getScenes() const
		{
			return m_Scenes;
		}

		std::map<const std::string, const boost::any> getTransientData() const
		{
			return m_TransientData;
		}

		IScene* getInitialScene() const
		{
			return m_Scenes.find(mv_szInitialScene)->second;
		}

		virtual ~IApplicationModel()
		{
			;
		}

	protected:
		std::string mv_szInitialScene;

		std::map<const std::string, IScene*> m_Scenes;
		std::map<const std::string, const boost::any> m_TransientData;
	};

}
