#pragma once
//                             Headers
/////////////////////////////////////////////////////////////////////////////
#include <QtWidgets/qmainwindow.h>
#include <Spring/Framework/IApplicationModel.h>
#include <Spring/Framework/SceneMachine.h>
#include <memory>
/////////////////////////////////////////////////////////////////////////////

namespace Spring
{
	typedef std::unique_ptr<QMainWindow> uxQWindow;

	class  Framework_EXPORT_IMPORT_API Application
	{
	public:
		static Application& getInstance()
		{
			static Application    instance; // Guaranteed to be destroyed.
			// Instantiated on first use.
			return instance;
		}

		void start(const std::string& av_szApplicationTitile, const unsigned ac_nWidth, const unsigned ac_nHeight);

		void setApplicationModel(IApplicationModel* av_xAppModel);

		~Application();

	private:
		Application();

		uxQWindow mv_xMainWindow;
		IApplicationModel* mv_pAppModel;
		CSceneMachine* m_SceneMachine;
	};

}
