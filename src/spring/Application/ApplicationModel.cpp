#include "spring\Application\ApplicationModel.h"
#include "spring\Application\InitialScene.h"
#include "spring\Application\BaseScene.h"
#include <cassert>

namespace Spring
{
  CApplicationModel::CApplicationModel()
  {
    m_uxInitialScene = std::make_unique<CInitialScene>();
  }

  void CApplicationModel::defineScene()
  {
    m_Scenes.insert(std::make_pair(m_uxInitialScene->sGetSceneName(), m_uxInitialScene.get()));

    assert(m_uxBaseScene == nullptr);
    m_uxBaseScene = std::make_unique<CBaseScene>();
    m_Scenes.insert(std::make_pair(m_uxBaseScene->sGetSceneName(), m_uxBaseScene.get()));
  }

  void CApplicationModel::defineInitialScene()
  {
    mv_szInitialScene = m_uxInitialScene->sGetSceneName();
  }

  void CApplicationModel::defineTransientData()
  {
    const std::string applicationName = "Undefined";
    m_TransientData.emplace("ApplicationName", applicationName);

    const unsigned int sampleRate = 25600;
    m_TransientData.emplace("SampleRate", sampleRate);

    const double displayTime = 0.1;
    m_TransientData.emplace("DisplayTime", displayTime);

    const unsigned int refreshRate = 1;
    m_TransientData.emplace("RefreshRate", refreshRate);
  }

}
