#include "../include/mainwindow.h"
#include "../include/converter.h"
#include "../include/settings.h"
#include "../include/settingsdock.h"
#include "../include/clickablelabel.h"
#include "../include/clickableplaintextedit.h"

#include "./ui_mainwindow.h"

#include <QClipboard>
#include <QFileDialog>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showStatusBarMessage("Ascii-Art-Generator v1.0", 0);

    ui->txt_output->setVisible(false);

    connect(ui->lbl_image, &ClickableLabel::clicked, this, &MainWindow::selectImage);
    connect(ui->txt_output, &ClickablePlainTextEdit::clicked, this, &MainWindow::copyAscii);
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
        "Image Files (*.jpg *.jpeg *.png *.bmp *.tiff *.gif)"
    );

    if (filePath.isEmpty()) return;

    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists() || !fileInfo.isReadable())
    {
        qDebug() << "Failed to load file from filepath";
        showStatusBarMessage("Invalid file selected, please try another file", 3000);
        return;
    }

    this->filePath = filePath;
    ui->lbl_imagePath->setText(filePath);

    QPixmap pixmap(filePath);
    if (pixmap.isNull())
    {
        qDebug() << "Failed to create pixmap from filepath";
        showStatusBarMessage("Unable to parse image, please try another file", 3000);
        return;
    }

    ui->lbl_image->setPixmap(
        pixmap.scaled(
            ui->lbl_image->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        )
    );

    showStatusBarMessage("Successfully loaded file: " + filePath, 3000);

    convertImage();
}

void MainWindow::convertImage()
{
    // show text edit on first convert
    if (!ui->txt_output->isVisible())
    {
        ui->lbl_output->setVisible(false);
        ui->txt_output->setVisible(true);
    }

    // evaluate settings
    QString chars = Settings::instance().getChars();
    unsigned int width = Settings::instance().getWidth();
    unsigned int height = Settings::instance().getHeight(); // TODO this is ignored as of now

    if (Settings::instance().getInvert())
    {
        std::reverse(chars.begin(), chars.end());
    }

    // actually convert
    Converter converter;
    QString result = converter.convert(filePath, width, chars);

    ui->txt_output->setPlainText(result);
}

void MainWindow::copyAscii()
{
    QString ascii = ui->txt_output->toPlainText();
    if (!ascii.isEmpty())
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(ascii);
        showStatusBarMessage("Ascii copied to clipboard!", 3000);
    }
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

void MainWindow::showStatusBarMessage(QString message, unsigned int timeout) const {
    ui->statusbar->showMessage(message, timeout);

    QTimer::singleShot(timeout, this, [this, message]() {
        ui->statusbar->showMessage("Ascii-Art-Generator v1.0");
        qDebug() << "Showing status bar message: " << message;
    });
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
