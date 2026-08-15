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

private slots:
    void on_input_chars_textChanged(const QString &arg1);

    void on_slider_width_sliderMoved(int position);

    void on_slider_height_sliderMoved(int position);

private:
    Ui::SettingsDock *ui;

    void regenerateAscii();
};
