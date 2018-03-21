#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSpinBox>
#include <QSlider>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /** Settings **/
    void on_PhongButton_toggled(bool checked);
    void on_NormalButton_toggled(bool checked);
    void on_GouraudButton_toggled(bool checked);

    void on_blueSlider_valueChanged(int value);
    void on_greenSlider_valueChanged(int value);
    void on_redSlider_valueChanged(int value);
    void on_pushButton_clicked();
    void on_spinX_valueChanged(int arg1);
    void on_spinY_valueChanged(int arg1);
    void on_spinZ_valueChanged(int arg1);
    void on_RotationDialViewX_sliderMoved(int position);
    void on_RotationDialViewY_sliderMoved(int position);
    void on_ResetView_clicked();
    void on_pushButton_2_clicked();
    void on_InitPosX_valueChanged(double arg1);
    void on_InitPosY_valueChanged(double arg1);
    void on_InitPosZ_valueChanged(double arg1);

    /** Object Manipulation **/
    void on_ResetRotationButton_clicked(bool checked);
    void on_RotationDialX_sliderMoved(int value);
    void on_RotationDialY_sliderMoved(int value);
    void on_RotationDialZ_sliderMoved(int value);
    void on_ZoomSlider_valueChanged(int value);
    void on_ResetZoomButton_clicked();
    void on_ScaleSlider_sliderMoved(int position);
    void on_Gravitation_valueChanged(double arg1);
    void on_Rotation_valueChanged(double arg1);
    void on_MatKd_valueChanged(double arg1);
    void on_MatKs_valueChanged(double arg1);
    void on_MatExp_valueChanged(double arg1);

    void on_objectSelector_activated(int index);
    void selectedObjectChanged();

    void onUpdate();

    void on_Restitution_valueChanged(double arg1);

private:
    void setNewValue(QSpinBox* widget, int value);
    void setNewValue(QDoubleSpinBox* widget, float value);
    void setNewValue(QSlider* slider, int value);
};

#endif // MAINWINDOW_H
