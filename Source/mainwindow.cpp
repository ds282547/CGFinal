#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //signals

    qDebug() << ui->centralWidget->sizeHint();
    qDebug() << ui->centralWidget->size();
    glw = ui->glwidget;
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButtonFit_released()
{
    QSize tempMinSize = glw->minimumSize();
    glw->setMinimumSize(QSize(512,512));
    resize( ui->centralWidget->minimumSizeHint());
    glw->setMinimumSize(tempMinSize);
}


void MainWindow::on_pushButtonDrawInitialDensity_released()
{
    glw->clearDensity();
}

void MainWindow::on_pushButtonDrawInitialDensity_toggled(bool checked)
{


}




void MainWindow::on_viscValue_valueChanged(int value)
{
    float factor = (float)value/10;
    float visc = 1/pow(10,10-factor);
    glw->setVisc( visc);

    ui->viscValueText->setText(QString::number(factor));
}

void MainWindow::on_diffValue_valueChanged(int value)
{
    float factor = (float)value/10;
    float diff = 1/pow(10,10-factor);
    glw->setDiff( diff);

    ui->diffValueText->setText(QString::number(factor));
}



void MainWindow::on_createRectangle_clicked()
{
}

void MainWindow::on_createCircle_clicked()
{
}

void MainWindow::on_createRectangle_toggled(bool checked)
{
    if(checked){
        ui->createCircle->setChecked(false);
        glw->mode = GLWidget::Mode::rectangleMode;
    }else{
        glw->mode = GLWidget::Mode::Simulating;
    }
}

void MainWindow::on_createCircle_toggled(bool checked)
{
    if(checked){
        ui->createRectangle->setChecked(false);
        glw->mode = GLWidget::Mode::circleMode;
    }else{
        glw->mode = GLWidget::Mode::Simulating;
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    int w = (64 << index);
    glw->regenGird(w,w);
    ui->createCircle->setChecked(false);
    ui->createRectangle->setChecked(false);
}

void MainWindow::on_IVValue_valueChanged(int value)
{
    float factor = (float)value/10;
    float IV = factor*90+100;
    glw->initialVel = IV;

    ui->IVValueText->setText(QString::number(factor));
}

void MainWindow::on_IDValue_valueChanged(int value)
{
    float factor = (float)value/10;
    float ID = factor*1.5+0.5;
    glw->initialDes = ID;

    ui->IDValueText->setText(QString::number(factor));
}

void MainWindow::on_pushButtonClearObjs_released()
{
    glw->clearBarrier();
    ui->createCircle->setChecked(false);
    ui->createRectangle->setChecked(false);
}

void MainWindow::on_pushButtonColor_released()
{
    QColor color = QColorDialog::getColor();
    QString stst = QString("QWidget{\nbackground-color: rgb(%1, %2, %3);\n}").arg(color.red()).arg(color.green()).arg(color.blue());
    ui->widgetColor->setStyleSheet(stst);
    glw->color = color;
}
