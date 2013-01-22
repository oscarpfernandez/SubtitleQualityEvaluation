#ifndef DRAGWIDGETCOMMENT_H
#define DRAGWIDGETCOMMENT_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QDialog>
#include <QLabel>
#include <QEvent>

class DragWidgetComment : public QDialog
{
    Q_OBJECT
public:
    DragWidgetComment(QWidget *parent);
    ~DragWidgetComment();
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
