#include "../include/mainwindow.h"
#include "../include/converter.h"

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
        ui->btn_convert->setDisabled(false);

        QPixmap pixmap(filePath);

        ui->lbl_image->setPixmap(
            pixmap.scaled(
                ui->lbl_image->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
            )
        );
    }
}

void MainWindow::convertImage()
{
    Converter converter;
    const QString& result = converter.convert(filePath, 50);

    ui->txt_output->setPlainText(result);
}

void MainWindow::on_btn_imageSelect_clicked()
{
    selectImage();
}

void MainWindow::on_btn_convert_clicked()
{
    convertImage();
}

void MainWindow::on_btn_exit_clicked()
{
    this->close();
}
