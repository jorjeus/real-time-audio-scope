#pragma once

#include "spring/Framework/IScene.h"

#include <QtWidgets/QPushButton>

#include "../third_party/QCustomPlot/qcustomplot.h"
#include "spring/Application/MonoInput.h"
#include <QAudioInput>

namespace Spring
{
  class CBaseScene : public IScene
  {
      Q_OBJECT

  public:
    CBaseScene();
	~CBaseScene();

		void createScene() override;
		void release() override;

  private:
    QWidget *centralWidget;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonBack;
    QCustomPlot *plot;
	QTimer		*timer;
	bool		isPlotStarted;
	QAudioInput *audioInput;
	MonoInput *inputDevice;
	QVector<double> xAxis;

  private slots:
    void mf_ReturnToInitialScene();
	void mf_PlotInput();
	void mf_CleanPlot();
	void mf_StartTimer();
	void mf_StopTimer();
  };
}
