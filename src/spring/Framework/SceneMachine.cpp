#include <Spring/Framework/SceneMachine.h>
#include <qcoreapplication.h>
#include <assert.h>

namespace Spring
{
	CSceneMachine::CSceneMachine(std::map<const std::string, IScene*> a_SceneCollection, std::map<const std::string, const boost::any> a_TransientData
		, std::unique_ptr<QMainWindow>& av_xMainWindow, const std::string ac_sInitialScene) :

		 m_SceneCollection(a_SceneCollection)
		, m_TransientDataCollection(a_TransientData)
		, mv_xMainWindow(std::move(av_xMainWindow))
		, mc_sInitialScene(ac_sInitialScene)
		, mv_sCurrentScene("")
	{
		assert(m_SceneCollection.size() != 0);

		for (const auto& Scene : m_SceneCollection) {
			QObject::connect(Scene.second, SIGNAL(SceneChange(const std::string&)),
				this, SLOT(setActiveScene(const std::string &)));
		}

		getActiveScene(mc_sInitialScene);

		QCoreApplication* app = QCoreApplication::instance();
		connect(app, SIGNAL(aboutToQuit()), this, SLOT(release()));
	}


	void CSceneMachine::setActiveScene(const std::string & ac_sSceneName)
	{
		getActiveScene(ac_sSceneName);
	}

	void CSceneMachine::getActiveScene(const std::string & ac_sSceneName)
	{
		if (mv_sCurrentScene != ac_sSceneName) {

			IScene* currentScene = nullptr;
			if (mv_sCurrentScene != "") {

				const auto& it = m_SceneCollection.find(mv_sCurrentScene);
				currentScene = it->second;

				mv_xMainWindow = std::move(currentScene->uGetWindow());
				m_TransientDataCollection =currentScene->uGetTransientData();
			}

			const auto& nextScene = m_SceneCollection.find(ac_sSceneName)->second;
			if (nextScene != nullptr) {
				if (currentScene != nullptr)
					currentScene->release();

				nextScene->setWindow(mv_xMainWindow);
				nextScene->setTransientData(m_TransientDataCollection);
				nextScene->createScene();
				nextScene->drawScene();
				nextScene->show();
				mv_sCurrentScene = ac_sSceneName;
			}
		}
	}

	void CSceneMachine::release() const
	{
		const auto& currentScene = m_SceneCollection.find(mv_sCurrentScene)->second;
		if (currentScene != nullptr)
			currentScene->release();
	}

	CSceneMachine::~CSceneMachine()
	{
		;
	}

}
