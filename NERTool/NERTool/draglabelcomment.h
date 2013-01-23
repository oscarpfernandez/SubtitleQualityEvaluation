#ifndef DRAGWIDGETCOMMENT_H
#define DRAGWIDGETCOMMENT_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QDialog>
#include <QLabel>
#include <QEvent>
#include <QApplication>
#include <QDesktopWidget>

class DragLabelComment : public QDialog
{
    Q_OBJECT
public:
    DragLabelComment(QWidget *parent);
    ~DragLabelComment();
    void setEditComment(QString &text);
    QString getEditComment();

private:
    QVBoxLayout *mainVBoxLay;
    QLabel *label;
    QTextEdit *editText;
    QPushButton *saveButton;

public slots:
    void saveCommentSlot();

};

#endif // DRAGWIDGETCOMMENT_H
