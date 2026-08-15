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

    QString getFilePath();

private slots:
    void on_btn_imageSelect_clicked();

    void on_btn_exit_clicked();

    void on_btn_settings_clicked();

private:
    Ui::MainWindow *ui;

    void showSettingsMenu();

    QString filePath;

    QDockWidget* settingsDock = nullptr;
};
