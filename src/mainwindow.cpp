#include "../include/mainwindow.h"
#include "../include/converter.h"
#include "../include/settings.h"
#include "../include/settingsdock.h"

#include "./ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectImage()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Choose Image File",
        "",
        "Image Files (*jpg *jpeg *png *bmp *tiff *gif)"
    );

    if (!filePath.isEmpty())
    {
        this->filePath = filePath;

        ui->lbl_imageSelect->setText(filePath);

        QPixmap pixmap(filePath);

        ui->lbl_image->setPixmap(
            pixmap.scaled(
                ui->lbl_image->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
            )
        );

        convertImage();
    }
}

void MainWindow::convertImage()
{
    const QString chars = Settings::instance().getChars();
    const unsigned int width = Settings::instance().getWidth();
    const unsigned int height = Settings::instance().getHeight(); // TODO this is ignored as of now

    Converter converter;
    QString result = converter.convert(filePath, width, chars);

    ui->txt_output->setPlainText(result);
}

void MainWindow::showSettingsMenu()
{
    if (!settingsDock)
    {
        settingsDock = new SettingsDock(this);
        addDockWidget(Qt::RightDockWidgetArea, settingsDock);
    }

    settingsDock->show();
    settingsDock->raise();
}

QString MainWindow::getFilePath()
{
    return this->filePath;
}

void MainWindow::on_btn_imageSelect_clicked()
{
    selectImage();
}

void MainWindow::on_btn_settings_clicked()
{
    showSettingsMenu();
}

void MainWindow::on_btn_exit_clicked()
{
    this->close();
}
