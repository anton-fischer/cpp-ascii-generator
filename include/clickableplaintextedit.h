#pragma once

#include <QPlainTextEdit>
#include <QMouseEvent>

class ClickablePlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit ClickablePlainTextEdit(QWidget *parent = nullptr) : QPlainTextEdit(parent) {}

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};
