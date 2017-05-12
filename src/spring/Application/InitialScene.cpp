#include "spring/Application/InitialScene.h"

#include <QtWidgets/QLineEdit>
#include <qapplication.h>

namespace Spring
{
  CInitialScene::CInitialScene()
    : IScene( std::string("InitialScene"))
  {
  }

  void CInitialScene::createScene()
  {
    createUI();

    const std::string appName = boost::any_cast<std::string>(m_TransientDataCollection.find("ApplicationName")->second);
    editAppName->setText(QString(appName.c_str()));
    const unsigned int sampleRate = boost::any_cast<unsigned int>(m_TransientDataCollection.find("SampleRate")->second);
    spinSampleRate->setValue(sampleRate);
    const double displayTime = boost::any_cast<double>(m_TransientDataCollection.find("DisplayTime")->second);
    spinDisplayTime->setValue(displayTime);
    const unsigned int refreshRate = boost::any_cast<unsigned>(m_TransientDataCollection.find("RefreshRate")->second);
    spinRefreshRate->setValue(refreshRate);

    QObject::connect(buttonOK, SIGNAL(released()), this, SLOT(mf_OnOKButton()));
  }

  void CInitialScene::release()
  {
    delete centralWidget;
    centralWidget = nullptr;
  }

  void CInitialScene::createUI()
  {
    const std::unique_ptr<QMainWindow>& uxMainWindow = uGetWindow();

    centralWidget = new QWidget(uxMainWindow.get());
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    gridLayout_3 = new QGridLayout(centralWidget);
    gridLayout_3->setSpacing(6);
    gridLayout_3->setContentsMargins(11, 11, 11, 11);
    gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
    gridLayout_2 = new QGridLayout();
    gridLayout_2->setSpacing(6);
    gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
    gridLayout_2->setHorizontalSpacing(6);
    labelSampleRate = new QLabel(centralWidget);
    labelSampleRate->setObjectName(QStringLiteral("labelSampleRate"));

    gridLayout_2->addWidget(labelSampleRate, 2, 1, 1, 1);

    labelDisplayTime = new QLabel(centralWidget);
    labelDisplayTime->setObjectName(QStringLiteral("labelDisplayTime"));

    gridLayout_2->addWidget(labelDisplayTime, 3, 1, 1, 1);

    horizontalSpacerRight = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    gridLayout_2->addItem(horizontalSpacerRight, 2, 3, 1, 1);

    labelAppName = new QLabel(centralWidget);
    labelAppName->setObjectName(QStringLiteral("labelAppName"));

    gridLayout_2->addWidget(labelAppName, 1, 1, 1, 1);

    spinSampleRate = new QSpinBox(centralWidget);
    spinSampleRate->setObjectName(QStringLiteral("spinSampleRate"));
    spinSampleRate->setMaximum(102400);

    gridLayout_2->addWidget(spinSampleRate, 2, 2, 1, 1);

    horizontalSpacerLeft = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout_2->addItem(horizontalSpacerLeft, 2, 0, 1, 1);

    verticalSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_2->addItem(verticalSpacerBottom, 5, 2, 1, 1);

    editAppName = new QLineEdit(centralWidget);
    editAppName->setObjectName(QStringLiteral("editAppName"));

    gridLayout_2->addWidget(editAppName, 1, 2, 1, 1);

    labelRefreshRate = new QLabel(centralWidget);
    labelRefreshRate->setObjectName(QStringLiteral("labelRefreshRate"));

    gridLayout_2->addWidget(labelRefreshRate, 4, 1, 1, 1);

    buttonOK = new QPushButton(centralWidget);
    buttonOK->setObjectName(QStringLiteral("buttonOK"));

    gridLayout_2->addWidget(buttonOK, 5, 3, 1, 1);

    verticalSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout_2->addItem(verticalSpacerTop, 0, 2, 1, 1);

    spinRefreshRate = new QSpinBox(centralWidget);
    spinRefreshRate->setObjectName(QStringLiteral("spinRefreshRate"));

    gridLayout_2->addWidget(spinRefreshRate, 4, 2, 1, 1);

    spinDisplayTime = new QDoubleSpinBox(centralWidget);
    spinDisplayTime->setObjectName(QStringLiteral("spinDisplayTime"));

    gridLayout_2->addWidget(spinDisplayTime, 3, 2, 1, 1);

    gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

    uxMainWindow->setCentralWidget(centralWidget);

    //retranslateUi(uxMainWindow.egt();
    uxMainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
    labelSampleRate->setText(QApplication::translate("MainWindow", "Sample Rate:", Q_NULLPTR));
    labelDisplayTime->setText(QApplication::translate("MainWindow", "Display Time:", Q_NULLPTR));
    labelAppName->setText(QApplication::translate("MainWindow", "Application Name:", Q_NULLPTR));
    labelRefreshRate->setText(QApplication::translate("MainWindow", "Refresh Rate:", Q_NULLPTR));
    buttonOK->setText(QApplication::translate("MainWindow", "OK", Q_NULLPTR));

    //QMetaObject::connectSlotsByName(MainWindow);
  }

  void CInitialScene::mf_OnOKButton()
  {
    std::string newAppName = editAppName->text().toStdString();
    m_TransientDataCollection.erase("ApplicationName");
    m_TransientDataCollection.emplace("ApplicationName", newAppName);
    //m_TransientDataCollection["ApplicationName"] = newAppName;

    const unsigned int newSampleRate = spinSampleRate->value();
    m_TransientDataCollection.erase("SampleRate");
    m_TransientDataCollection.emplace("SampleRate", newSampleRate);
    //m_TransientDataCollection["SampleRate"] = newSampleRate;

    const double newDisplayTime = spinDisplayTime->value();
    m_TransientDataCollection.erase("DisplayTime");
    m_TransientDataCollection.emplace("DisplayTime", newDisplayTime);
    //m_TransientDataCollection["DisplayTime"] = newDisplayTime;

    const unsigned newRefreshRate = spinRefreshRate->value();
    m_TransientDataCollection.erase("RefreshRate");
    m_TransientDataCollection.emplace("RefreshRate", newRefreshRate);
    //m_TransientDataCollection["RefreshRate"] = newRefreshRate;
     
    emit SceneChange("BaseScene");
  }

}
