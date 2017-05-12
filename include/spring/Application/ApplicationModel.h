#pragma once

#include "spring\Framework\IApplicationModel.h"
#include "global.h"

namespace Spring
{
  class Application_EXPORT_IMPORT_API CApplicationModel : public IApplicationModel
  {
  public:
    CApplicationModel();

		void defineScene() override;
		void defineInitialScene() override;
		void defineTransientData() override;

  private:
    std::unique_ptr<IScene> m_uxInitialScene;
    std::unique_ptr<IScene> m_uxBaseScene;
  };
}
