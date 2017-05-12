#include <qapplication.h>
#include "spring\Application\ApplicationModel.h"
#include "spring\Framework\Application.h"

int main(int argc, char **argv)
{
  QApplication qtApp(argc, argv);

  Spring::CApplicationModel appModel;

  auto& appInstance = Spring::Application::getInstance();

  appInstance.setApplicationModel(&appModel);
  appInstance.start( "SpringApp", 500, 500);

  qtApp.exec();

	return 0;
}