#include <spring/Framework/Application.h>
#include <qtimer.h>
#include <memory>


namespace Spring
{
  Application::Application(): mv_pAppModel(nullptr), m_SceneMachine(nullptr)
	{
		;
	}

	void Application::start(const std::string& av_szApplicationTitile, const unsigned ac_nWidth, const unsigned ac_nHeight)
  {
    mv_xMainWindow = std::make_unique<QMainWindow>();
    mv_xMainWindow->setWindowTitle(QString::fromUtf8(av_szApplicationTitile.c_str()));
    mv_xMainWindow->resize(ac_nWidth, ac_nHeight);

   
	m_SceneMachine = new CSceneMachine(mv_pAppModel->getScenes(), mv_pAppModel->getTransientData(), mv_xMainWindow, mv_pAppModel->sGetInitialSceneName());

  }

  void Application::setApplicationModel(IApplicationModel* av_xAppModel)
  {
    mv_pAppModel = std::move(av_xAppModel);
    mv_pAppModel->defineScene();
    mv_pAppModel->defineTransientData();
    mv_pAppModel->defineInitialScene();
  }

  Application::~Application()
  {
    mv_pAppModel = nullptr;
	delete m_SceneMachine;
  }
}
