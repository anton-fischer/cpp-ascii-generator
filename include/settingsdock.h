#pragma once

#include <QDockWidget>

#include "../include/mainwindow.h"

namespace Ui {
class SettingsDock;
}

class SettingsDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit SettingsDock(MainWindow *parent = nullptr);
    ~SettingsDock();

public slots:
    void onImageLoaded();

private slots:

    void on_input_chars_textChanged(const QString &chars);

    void on_slider_width_valueChanged(int width);

    void on_slider_height_valueChanged(int height);

    void on_cbx_invert_clicked();

    void on_cbx_lock_ratio_clicked();

private:
    Ui::SettingsDock *ui;

    void regenerateAscii();
};
