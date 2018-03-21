#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "math.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->objectSelector->setModel(ui->mainView->listmodel());
    connect(ui->mainView, SIGNAL(objectsChanged()), this, SLOT(onUpdate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --- Functions that listen for widget events
// forewards to the mainview

void MainWindow::on_ResetRotationButton_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->RotationDialX->setValue(0);
    ui->RotationDialY->setValue(0);
    ui->RotationDialZ->setValue(0);
    ui->mainView->setRotation(0, 0, 0);
}

void MainWindow::on_RotationDialX_sliderMoved(int value)
{
    ui->mainView->setRotation(value,
                              ui->RotationDialY->value(),
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialY_sliderMoved(int value)
{
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              value,
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialZ_sliderMoved(int value)
{
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              ui->RotationDialY->value(),
                              value);
}


void MainWindow::on_ResetZoomButton_clicked()
{
    ui->ZoomSlider->setValue(100);
}

void MainWindow::on_ZoomSlider_valueChanged(int value)
{
    ui->mainView->setDistance((float) value / 10.f);
    ui->mainView->setViewRotation(ui->RotationDialViewX->value(), ui->RotationDialViewY->value());
}

void MainWindow::on_PhongButton_toggled(bool checked)
{
    if (checked)
    {
        ui->mainView->setShadingMode(MainView::PHONG);
        ui->mainView->update();
    }
}

void MainWindow::on_NormalButton_toggled(bool checked)
{
    if (checked)
    {
        ui->mainView->setShadingMode(MainView::NORMAL);
        ui->mainView->update();
    }
}

void MainWindow::on_GouraudButton_toggled(bool checked)
{
    if (checked)
    {
        ui->mainView->setShadingMode(MainView::GOURAUD);
        ui->mainView->update();
    }
}

void MainWindow::on_blueSlider_valueChanged(int value)
{
      ui->mainView->setColor(ui->redSlider->value(), ui->greenSlider->value(), value);
}

void MainWindow::on_greenSlider_valueChanged(int value)
{
    ui->mainView->setColor(ui->redSlider->value(), value, ui->blueSlider->value());

}

void MainWindow::on_redSlider_valueChanged(int value)
{
    ui->mainView->setColor(value, ui->greenSlider->value(), ui->blueSlider->value());
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("PNG (*.png)"));
    if (!fileName.isEmpty())
        ui->mainView->loadFile(fileName);
}

void MainWindow::on_spinX_valueChanged(int arg1)
{
    ui->mainView->setLightPosition(arg1, ui->spinY->value(), ui->spinZ->value());
}

void MainWindow::on_spinY_valueChanged(int arg1)
{
    ui->mainView->setLightPosition(ui->spinX->value(), arg1,  ui->spinZ->value());
}

void MainWindow::on_spinZ_valueChanged(int arg1)
{
    ui->mainView->setLightPosition(ui->spinX->value(), ui->spinY->value(), arg1);
}

void MainWindow::on_RotationDialViewX_sliderMoved(int position)
{
    ui->mainView->setViewRotation(position, ui->RotationDialViewY->value());
}

void MainWindow::on_RotationDialViewY_sliderMoved(int position)
{
    ui->mainView->setViewRotation(ui->RotationDialViewX->value(), position);
}

void MainWindow::on_ResetView_clicked()
{
    ui->mainView->setViewRotation(0, 0);
    ui->RotationDialViewX->setValue(0);
    ui->RotationDialViewY->setValue(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->mainView->resetScene();
}

void MainWindow::on_objectSelector_activated(int index)
{
    ui->mainView->setSelectedObject(index);
    selectedObjectChanged();
}


void MainWindow::on_InitPosX_valueChanged(double arg1)
{
    if(ui->mainView->selectedObject()){
        QVector3D newpos = ui->mainView->selectedObject()->getOriginalPosition();
        newpos.setX(arg1);
        ui->mainView->selectedObject()->setOriginalPosition(newpos);
    }
}

void MainWindow::on_InitPosY_valueChanged(double arg1)
{
    if(ui->mainView->selectedObject()){
        QVector3D newpos = ui->mainView->selectedObject()->getOriginalPosition();
        newpos.setY(arg1);
        ui->mainView->selectedObject()->setOriginalPosition(newpos);
    }
}

void MainWindow::on_InitPosZ_valueChanged(double arg1)
{
    if(ui->mainView->selectedObject()){
        QVector3D newpos = ui->mainView->selectedObject()->getOriginalPosition();
        newpos.setZ(arg1);
        ui->mainView->selectedObject()->setOriginalPosition(newpos);
    }
}

void MainWindow::on_ScaleSlider_sliderMoved(int position)
{
    if (ui->mainView->selectedObject())
        ui->mainView->selectedObject()->setScale((float) position / 10.0f);
}

void MainWindow::on_Gravitation_valueChanged(double arg1)
{
    if (ui->mainView->selectedObject())
        ui->mainView->selectedObject()->setGravitation(arg1);
}

void MainWindow::on_Rotation_valueChanged(double arg1)
{
    if (ui->mainView->selectedObject())
        ui->mainView->selectedObject()->setRotationSpeed(arg1);
}

void MainWindow::on_MatKd_valueChanged(double arg1)
{
    if (ui->mainView->selectedObject()){
        Material m = ui->mainView->selectedObject()->getMaterial();
        m.kd = arg1;
        ui->mainView->selectedObject()->setMaterial(m);
    }
}

void MainWindow::on_MatKs_valueChanged(double arg1)
{
    if (ui->mainView->selectedObject()){
        Material m = ui->mainView->selectedObject()->getMaterial();
        m.ks = arg1;
        ui->mainView->selectedObject()->setMaterial(m);
    }
}

void MainWindow::on_MatExp_valueChanged(double arg1)
{
    if (ui->mainView->selectedObject()){
        Material m = ui->mainView->selectedObject()->getMaterial();
        m.n = arg1;
        ui->mainView->selectedObject()->setMaterial(m);
    }
}


void MainWindow::on_Restitution_valueChanged(double arg1)
{
    if (ui->mainView->selectedObject()){
        ui->mainView->selectedObject()->setRestitution(arg1);
    }
}


void MainWindow::setNewValue(QDoubleSpinBox *widget, float value)
{
    if (!widget->hasFocus())
        widget->setValue(value);
}

void MainWindow::setNewValue(QSpinBox *widget, int value)
{
    if (!widget->hasFocus())
        widget->setValue(value);
}

void MainWindow::setNewValue(QSlider *slider, int value)
{
    if (!slider->hasFocus())
        slider->setValue(value);
}

void MainWindow::onUpdate()
{
    if (ui->mainView->selectedObject()){
        ui->RotationDialX->setValue(ui->mainView->selectedObject()->getRotationVector().x());
        ui->RotationDialY->setValue(ui->mainView->selectedObject()->getRotationVector().y());
        ui->RotationDialZ->setValue(ui->mainView->selectedObject()->getRotationVector().z());
        ui->ScaleSlider->setValue(ui->mainView->selectedObject()->getScale() * 10);

        setNewValue(ui->InitPosX, ui->mainView->selectedObject()->getOriginalPosition().x());
        setNewValue(ui->InitPosY, ui->mainView->selectedObject()->getOriginalPosition().y());
        setNewValue(ui->InitPosZ, ui->mainView->selectedObject()->getOriginalPosition().z());
        setNewValue(ui->Rotation, ui->mainView->selectedObject()->getRotationSpeed());
        setNewValue(ui->Gravitation, ui->mainView->selectedObject()->getGravitation());
        setNewValue(ui->MatKd, ui->mainView->selectedObject()->getMaterial().kd);
        setNewValue(ui->MatKs, ui->mainView->selectedObject()->getMaterial().ks);
        setNewValue(ui->MatExp, ui->mainView->selectedObject()->getMaterial().n);
        setNewValue(ui->Restitution, ui->mainView->selectedObject()->getRestitution());
    }
    ui->ZoomSlider->setValue(ui->mainView->distance() * 10);
    ui->RotationDialViewX->setValue(ui->mainView->viewRotX());
    ui->RotationDialViewY->setValue(ui->mainView->viewRotY());
}

void MainWindow::selectedObjectChanged(){
    onUpdate();
}
