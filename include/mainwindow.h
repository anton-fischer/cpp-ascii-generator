#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void selectImage();
    void convertImage();
    void copyAscii();

    QString getFilePath();

private slots:
    void on_btn_imageSelect_clicked();

    void on_btn_exit_clicked();

    void on_btn_settings_clicked();

private:
    Ui::MainWindow *ui;

    void showSettingsMenu();
    void showStatusBarMessage(QString message, unsigned int timeout) const;

    QString filePath;
    QDockWidget* settingsDock = nullptr;
};
