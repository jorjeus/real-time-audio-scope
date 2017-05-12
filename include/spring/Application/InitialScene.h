#pragma once

#include "spring/Framework/IScene.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QPushButton>

namespace Spring
{
  class CInitialScene : public IScene
  {
		Q_OBJECT

  public:
    CInitialScene();

		void createScene() override;
		void release() override;

  private:
    void createUI();

    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *labelSampleRate;
    QLabel *labelDisplayTime;
    QSpacerItem *horizontalSpacerRight;
    QLabel *labelAppName;
    QSpinBox *spinSampleRate;
    QSpacerItem *horizontalSpacerLeft;
    QSpacerItem *verticalSpacerBottom;
    QLineEdit *editAppName;
    QLabel *labelRefreshRate;
    QPushButton *buttonOK;
    QSpacerItem *verticalSpacerTop;
    QSpinBox *spinRefreshRate;
    QDoubleSpinBox *spinDisplayTime;

  private slots:
    void mf_OnOKButton();
  };
}
