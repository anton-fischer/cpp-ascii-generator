#include "../include/clickableplaintextedit.h"

void ClickablePlainTextEdit::mousePressEvent(QMouseEvent *event) {
    emit clicked();
    QPlainTextEdit::mousePressEvent(event);
}
