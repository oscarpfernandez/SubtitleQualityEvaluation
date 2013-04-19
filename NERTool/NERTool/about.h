#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QDate>
#include <QTime>
#include <QPushButton>
#include <QPalette>
#include "constants.h"

class About : public QDialog
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = 0);
    ~About();

private:
    void createElements();
    QVBoxLayout *mainVBoxLayout;
    QHBoxLayout *buttonHBoxLayout;
    QLabel      *imageLabel;
    QTextEdit   *textEdit;
    QTextEdit   *creditsTextEdit;
    QPushButton *button;
    QPushButton *buttonCredits;
    QDialog     *creditsDiag;
    QVBoxLayout *creditsLayout;
    QLabel      *creditsLabel;

private slots:
    void closeDialog();
    void showCredits();
};

#endif // ABOUT_H
