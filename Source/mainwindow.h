#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include "glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:



private slots:




    void on_pushButtonFit_released();

    void on_pushButtonDrawInitialDensity_released();

    void on_pushButtonDrawInitialDensity_toggled(bool checked);


    void on_viscValue_valueChanged(int value);

    void on_diffValue_valueChanged(int value);



    void on_createRectangle_clicked();

    void on_createCircle_clicked();

    void on_createRectangle_toggled(bool checked);

    void on_createCircle_toggled(bool checked);

    void on_comboBox_currentIndexChanged(int index);

    void on_IVValue_valueChanged(int value);

    void on_IDValue_valueChanged(int value);

    void on_pushButtonClearObjs_released();

    void on_pushButtonColor_released();

private:
    Ui::MainWindow *ui;
    GLWidget *glw;

};

#endif // MAINWINDOW_H
