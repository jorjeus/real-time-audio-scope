//                             Headers
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include <qobject.h>
#include <Spring/Framework/global.h>
#include "IScene.h"
/////////////////////////////////////////////////////////////////////////////

namespace Spring
{
	class Framework_EXPORT_IMPORT_API CSceneMachine : public QObject
	{
		Q_OBJECT

	public:
		CSceneMachine(std::map<const std::string, IScene*> a_SceneCollection, std::map<const std::string, const boost::any> a_TransientData
					 , std::unique_ptr<QMainWindow>& av_xMainWindow, const std::string ac_sInitialScene);

		~CSceneMachine();

		typedef std::shared_ptr<CSceneMachine> s_ptr;
		typedef std::unique_ptr<CSceneMachine> u_ptr;
	private:


		std::map<const std::string, IScene*>  m_SceneCollection;
		std::map<const std::string, const boost::any> m_TransientDataCollection;
		std::unique_ptr<QMainWindow> mv_xMainWindow;
		const std::string mc_sInitialScene;

		std::string mv_sCurrentScene;

		void getActiveScene(const std::string& ac_sSceneName);

		private slots:
		void setActiveScene(const std::string& ac_sSceneName);
		void release() const;

	};


}