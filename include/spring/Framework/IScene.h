#pragma once
#include <memory>
#include <QtWidgets/qmainwindow.h>
#include <Spring/Framework/global.h>
#include <boost/any.hpp>

namespace Spring
{
	class Framework_EXPORT_IMPORT_API IScene : public QObject
	{
		Q_OBJECT

			signals :
		void SceneChange(const std::string& ac_szSceneName);

	public:
		explicit IScene(const std::string& ac_szSceneName) : mc_szSceneName(ac_szSceneName)
		{
			;
		}

		virtual void createScene() = 0;

		virtual void drawScene()
		{
			QMetaObject::connectSlotsByName(m_uMainWindow.get());
		}

		virtual void release() = 0;

		virtual void setWindow(std::unique_ptr<QMainWindow>& av_xMainWindow)
		{
			m_uMainWindow = std::move(av_xMainWindow);
		}

		virtual std::unique_ptr<QMainWindow>& uGetWindow()
		{
			return m_uMainWindow;
		}

		virtual void setTransientData(std::map<const std::string, const boost::any>& ac_xTransientData)
		{
			m_TransientDataCollection = std::move(ac_xTransientData);
		}


		virtual std::map<const std::string, const boost::any> uGetTransientData()
		{
			return m_TransientDataCollection;
		}

		void show() const
		{
			m_uMainWindow->show();
		}

		virtual ~IScene()
		{
			;
		}

		virtual std::string sGetSceneName()
		{
			return mc_szSceneName;
		}

		typedef std::shared_ptr<IScene> s_ptr;
		typedef std::unique_ptr<IScene> u_ptr;

	protected:
		std::unique_ptr<QMainWindow> m_uMainWindow;
		std::map<const std::string, const boost::any> m_TransientDataCollection;

	private:
		const std::string mc_szSceneName;

	};


}
