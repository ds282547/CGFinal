/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <glwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    GLWidget *glwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox;
    QPushButton *pushButtonDrawInitialDensity;
    QPushButton *pushButtonFit;
    QPushButton *pushButtonClose;
    QPushButton *createRectangle;
    QPushButton *createCircle;
    QPushButton *pushButtonClearObjs;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSlider *viscValue;
    QSlider *IDValue;
    QLabel *label_2;
    QLabel *label;
    QLabel *diffValueText;
    QLabel *label_3;
    QSlider *diffValue;
    QLabel *IVValueText;
    QLabel *viscValueText;
    QLabel *IDValueText;
    QLabel *label_4;
    QSlider *IVValue;
    QLabel *label_5;
    QPushButton *pushButtonColor;
    QWidget *widgetColor;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(750, 670);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        glwidget = new GLWidget(centralWidget);
        glwidget->setObjectName(QStringLiteral("glwidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(glwidget->sizePolicy().hasHeightForWidth());
        glwidget->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(glwidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));

        verticalLayout->addLayout(horizontalLayout_2);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);

        pushButtonDrawInitialDensity = new QPushButton(centralWidget);
        pushButtonDrawInitialDensity->setObjectName(QStringLiteral("pushButtonDrawInitialDensity"));
        pushButtonDrawInitialDensity->setCheckable(false);

        verticalLayout->addWidget(pushButtonDrawInitialDensity);

        pushButtonFit = new QPushButton(centralWidget);
        pushButtonFit->setObjectName(QStringLiteral("pushButtonFit"));
        pushButtonFit->setMinimumSize(QSize(150, 0));
        pushButtonFit->setBaseSize(QSize(0, 0));

        verticalLayout->addWidget(pushButtonFit);

        pushButtonClose = new QPushButton(centralWidget);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(pushButtonClose);

        createRectangle = new QPushButton(centralWidget);
        createRectangle->setObjectName(QStringLiteral("createRectangle"));
        createRectangle->setCheckable(true);

        verticalLayout->addWidget(createRectangle);

        createCircle = new QPushButton(centralWidget);
        createCircle->setObjectName(QStringLiteral("createCircle"));
        createCircle->setCheckable(true);

        verticalLayout->addWidget(createCircle);

        pushButtonClearObjs = new QPushButton(centralWidget);
        pushButtonClearObjs->setObjectName(QStringLiteral("pushButtonClearObjs"));

        verticalLayout->addWidget(pushButtonClearObjs);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMaximumSize(QSize(200, 16777215));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        viscValue = new QSlider(groupBox);
        viscValue->setObjectName(QStringLiteral("viscValue"));
        viscValue->setMaximum(100);
        viscValue->setPageStep(1);
        viscValue->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(viscValue, 0, 3, 1, 1);

        IDValue = new QSlider(groupBox);
        IDValue->setObjectName(QStringLiteral("IDValue"));
        IDValue->setMaximum(100);
        IDValue->setPageStep(1);
        IDValue->setValue(50);
        IDValue->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(IDValue, 4, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        diffValueText = new QLabel(groupBox);
        diffValueText->setObjectName(QStringLiteral("diffValueText"));

        gridLayout->addWidget(diffValueText, 1, 5, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 1, 1, 1);

        diffValue = new QSlider(groupBox);
        diffValue->setObjectName(QStringLiteral("diffValue"));
        diffValue->setMaximum(100);
        diffValue->setPageStep(1);
        diffValue->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(diffValue, 1, 3, 1, 1);

        IVValueText = new QLabel(groupBox);
        IVValueText->setObjectName(QStringLiteral("IVValueText"));

        gridLayout->addWidget(IVValueText, 3, 5, 1, 1);

        viscValueText = new QLabel(groupBox);
        viscValueText->setObjectName(QStringLiteral("viscValueText"));

        gridLayout->addWidget(viscValueText, 0, 5, 1, 1);

        IDValueText = new QLabel(groupBox);
        IDValueText->setObjectName(QStringLiteral("IDValueText"));

        gridLayout->addWidget(IDValueText, 4, 5, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 1, 1, 1);

        IVValue = new QSlider(groupBox);
        IVValue->setObjectName(QStringLiteral("IVValue"));
        IVValue->setMaximum(100);
        IVValue->setPageStep(1);
        IVValue->setValue(50);
        IVValue->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(IVValue, 3, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 5, 1, 1, 1);

        pushButtonColor = new QPushButton(groupBox);
        pushButtonColor->setObjectName(QStringLiteral("pushButtonColor"));
        pushButtonColor->setMaximumSize(QSize(20, 16777215));

        gridLayout->addWidget(pushButtonColor, 5, 5, 1, 1);

        widgetColor = new QWidget(groupBox);
        widgetColor->setObjectName(QStringLiteral("widgetColor"));
        widgetColor->setStyleSheet(QLatin1String("QWidget{\n"
"background-color: rgb(255, 255, 255);\n"
"}"));

        gridLayout->addWidget(widgetColor, 5, 3, 1, 1);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(pushButtonClose, SIGNAL(released()), MainWindow, SLOT(close()));

        comboBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "2018 CG Final Group14 - Fluid/Smoke Simulation", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "64x64", Q_NULLPTR)
         << QApplication::translate("MainWindow", "128x128", Q_NULLPTR)
         << QApplication::translate("MainWindow", "256x256", Q_NULLPTR)
        );
        pushButtonDrawInitialDensity->setText(QApplication::translate("MainWindow", "Clear Density", Q_NULLPTR));
        pushButtonFit->setText(QApplication::translate("MainWindow", "Fit to 512 x 512", Q_NULLPTR));
        pushButtonClose->setText(QApplication::translate("MainWindow", "Close", Q_NULLPTR));
        createRectangle->setText(QApplication::translate("MainWindow", "Create Rectangle", Q_NULLPTR));
        createCircle->setText(QApplication::translate("MainWindow", "Create Circle", Q_NULLPTR));
        pushButtonClearObjs->setText(QApplication::translate("MainWindow", "Clear Object(s)", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Parameters", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "visc", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "diff", Q_NULLPTR));
        diffValueText->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Init Vel", Q_NULLPTR));
        IVValueText->setText(QApplication::translate("MainWindow", "5.0", Q_NULLPTR));
        viscValueText->setText(QApplication::translate("MainWindow", "0.0", Q_NULLPTR));
        IDValueText->setText(QApplication::translate("MainWindow", "5.0", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Init Des", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Color", Q_NULLPTR));
        pushButtonColor->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
