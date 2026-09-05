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

    ui->cbx_invert->setChecked(Settings::instance().getInvert());
    ui->cbx_lock_ratio->setChecked(Settings::instance().getLockRatio());
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

void SettingsDock::onImageLoaded()
{
    const QSignalBlocker blockerWidth(ui->slider_width);
    ui->slider_width->setValue(Settings::instance().getWidth());

    const QSignalBlocker blockerHeight(ui->slider_height);
    ui->slider_height->setValue(Settings::instance().getHeight());
}

void SettingsDock::on_input_chars_textChanged(const QString &chars)
{
    if (chars.size() > 0)
    {
        Settings::instance().setChars(chars);
        regenerateAscii();
    }
    else
    {
        ui->input_chars->setText(Settings::instance().getChars());
    }
}

void SettingsDock::on_slider_width_valueChanged(int width)
{
    if (Settings::instance().getLockRatio())
    {
        // block signal to avoid recursive calls
        const QSignalBlocker blocker(ui->slider_height);
        const int difference = width - Settings::instance().getWidth();
        const int height = Settings::instance().getHeight();

        ui->slider_height->setValue(height + difference);
        Settings::instance().setHeight(ui->slider_height->value());
    }
    Settings::instance().setWidth(width);
    regenerateAscii();
}

void SettingsDock::on_slider_height_valueChanged(int height)
{
    if (Settings::instance().getLockRatio())
    {
        // block signal to avoid recursive calls
        const QSignalBlocker blocker(ui->slider_width);
        const int difference = height - Settings::instance().getHeight();
        const int width = Settings::instance().getWidth();

        ui->slider_width->setValue(width + difference);
        Settings::instance().setWidth(ui->slider_width->value());
    }
    Settings::instance().setHeight(height);
    regenerateAscii();
}

void SettingsDock::on_cbx_invert_clicked()
{
    Settings::instance().setInvert(ui->cbx_invert->isChecked());
    regenerateAscii();
}

void SettingsDock::on_cbx_lock_ratio_clicked()
{
    Settings::instance().setLockRatio(ui->cbx_lock_ratio->isChecked());
}
