#ifndef NERTABLEASSESSMENT_H
#define NERTABLEASSESSMENT_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QDialog>
#include <QLabel>
#include <QEvent>
#include <QApplication>
#include <QDesktopWidget>

class NERTableAssessment : public QDialog
{
    Q_OBJECT
public:
    NERTableAssessment(QWidget *parent);
    ~NERTableAssessment();
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

#endif // NERTABLEASSESSMENT_H
