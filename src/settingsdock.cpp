#include "../include/settingsdock.h"
#include "../include/settings.h"

#include "./ui_settingsdock.h"

SettingsDock::SettingsDock(MainWindow *parent)
    : QDockWidget(parent)
    , ui(new Ui::SettingsDock)
{
    ui->setupUi(this);

    // restore previous settings
    ui->input_chars->setText(Settings::instance().getChars());
    ui->slider_width->setValue(Settings::instance().getWidth());
    ui->slider_height->setValue(Settings::instance().getHeight());
}

SettingsDock::~SettingsDock()
{
    delete ui;
}

void SettingsDock::regenerateAscii()
{
    MainWindow* mainWindow = qobject_cast<MainWindow*>(parent());
    if (!mainWindow)
    {
        qDebug() << "Parent mainWindow not found, not regenerating ascii!";
        return;
    }
    if (mainWindow->getFilePath().isEmpty()) {
        qDebug() << "No image selected yet, not regenerating ascii!";
        return;
    }

    mainWindow->convertImage();
    qDebug() << "Regenerated ascii";
}

void SettingsDock::on_input_chars_textChanged(const QString &chars)
{
    Settings::instance().setChars(chars);
    regenerateAscii();
}

void SettingsDock::on_slider_width_sliderMoved(int width)
{
    Settings::instance().setWidth(width);
    regenerateAscii();
}

void SettingsDock::on_slider_height_sliderMoved(int height)
{
    Settings::instance().setHeight(height);
    regenerateAscii();
}

void SettingsDock::on_cbx_invert_clicked()
{
    Settings::instance().setInvert(ui->cbx_invert->isChecked());
    regenerateAscii();
}

