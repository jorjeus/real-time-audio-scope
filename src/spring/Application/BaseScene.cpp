#include "spring/Application/BaseScene.h"

#include <QtWidgets/QGridLayout>
#include <qapplication.h>

namespace Spring
{
	CBaseScene::CBaseScene()
		: IScene(std::string("BaseScene")),
		isPlotStarted (false)
  {
		timer = new QTimer(this);
		QObject::connect(timer, SIGNAL(timeout()), this, SLOT(mf_PlotInput()));
  }

  void CBaseScene::createScene()
  {
    QMainWindow* pMainWindow = uGetWindow().get();

    centralWidget = new QWidget(pMainWindow);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    QGridLayout *gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    QSpacerItem *horizontalSpacerButtons = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(horizontalSpacerButtons, 3, 0, 1, 1);

    pushButtonStart = new QPushButton(centralWidget);
    pushButtonStart->setObjectName(QStringLiteral("pushButtonStart"));

    gridLayout->addWidget(pushButtonStart, 3, 1, 1, 1);

    plot = new QCustomPlot(centralWidget);
    plot->setObjectName(QStringLiteral("plot"));
    gridLayout->addWidget(plot, 2, 0, 1, 4);

    pushButtonStop = new QPushButton(centralWidget);
    pushButtonStop->setObjectName(QStringLiteral("pushButtonStop"));

    gridLayout->addWidget(pushButtonStop, 3, 2, 1, 1);

    pushButtonBack = new QPushButton(centralWidget);
    pushButtonBack->setObjectName(QStringLiteral("pushButtonBack"));

    gridLayout->addWidget(pushButtonBack, 3, 3, 1, 1);

    pMainWindow->setCentralWidget(centralWidget);

    pMainWindow->setWindowTitle(QApplication::translate("DisplayWindow", "DisplayWindow", Q_NULLPTR));
    pushButtonStart->setText(QApplication::translate("DisplayWindow", "&Start", Q_NULLPTR));
    pushButtonStop->setText(QApplication::translate("DisplayWindow", "Sto&p", Q_NULLPTR));
    pushButtonBack->setText(QApplication::translate("DisplayWindow", "&Back", Q_NULLPTR));

    QObject::connect(pushButtonBack, SIGNAL(released()), this, SLOT(mf_ReturnToInitialScene()));

	QObject::connect(pushButtonStart, SIGNAL(released()), this, SLOT(mf_StartTimer()));

	QObject::connect(pushButtonStop, SIGNAL(released()), this, SLOT(mf_StopTimer()));

	plot->addGraph();

	unsigned sampleRate = boost::any_cast<unsigned>(m_TransientDataCollection.find("SampleRate")->second);
	double displayTime = boost::any_cast<double>(m_TransientDataCollection.find("DisplayTime")->second);
	
	inputDevice = new MonoInput(displayTime, sampleRate);
	inputDevice->open(QIODevice::WriteOnly);

	xAxis.clear();
	for (int i = 0; i < displayTime*sampleRate; i++)
	{
		xAxis.push_back((double)i * 1.0/sampleRate);
	}
  }

  void CBaseScene::release()
  {
    delete centralWidget;
    centralWidget = nullptr;
    // the rest of the member qt controls are now dangling pointers; let's clear them out
    pushButtonStart = nullptr;
    pushButtonStop = nullptr;
	pushButtonBack = nullptr;
    plot = nullptr;

	delete inputDevice;
	inputDevice = nullptr;
  }

  CBaseScene::~CBaseScene()
  {
	  delete timer;
	  timer = nullptr;
  }

  void CBaseScene::mf_ReturnToInitialScene()
  {
    emit SceneChange("InitialScene");
  }
	
  void CBaseScene::mf_PlotInput()
  {
	  QVector<double> yAxis = inputDevice->vecGetData();

	  xAxis.resize(yAxis.size());
	  plot->graph(0)->setData(xAxis, yAxis);
	  plot->rescaleAxes(true);
	  plot->replot();
  }

  void CBaseScene::mf_CleanPlot()
  {
	  plot->graph(0)->data()->clear();
	  plot->replot();
  }

  void CBaseScene::mf_StartTimer()
  {
	  if (!isPlotStarted)
	  {
		  audioInput = new QAudioInput(inputDevice->getAudioFormat());
		  audioInput->start(inputDevice);
		  unsigned refreshRate = boost::any_cast<unsigned>(m_TransientDataCollection.find("RefreshRate")->second);
		  timer->start(1000 / refreshRate);
		  isPlotStarted = true;
		  pushButtonBack->setEnabled(false);
	  }
  }

  void CBaseScene::mf_StopTimer()
  {
	  if (isPlotStarted)
	  {
		  timer->stop();
		  isPlotStarted = false;
		  mf_CleanPlot();
		  audioInput->stop();
		  delete audioInput;
		  audioInput = nullptr;
		  pushButtonBack->setEnabled(true);
	  }
  }
}
