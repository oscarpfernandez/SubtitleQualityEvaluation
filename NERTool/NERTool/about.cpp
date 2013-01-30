#include "about.h"

/******************************************************************************
 * This class implements the traditional "about" dialog with some informations
 * about the application: versions, build dates, framework used and copyright
 * warning.
 ******************************************************************************/

About::About(QWidget *parent) : QDialog(parent)
{
    QString windowText = QString("About ");
    windowText.append(APP_NAME);
    windowText.append(" (v.");
    windowText.append(APP_VERSION);
    windowText.append(")");

    setWindowTitle(windowText);
    setWindowOpacity(0.95);
    setWindowModality(Qt::ApplicationModal);

    createElements();

    setLayout(mainVBoxLayout);
    setFixedSize(sizeHint().width(),500);
}

About::~About()
{
    delete textEdit;
    delete imageLabel;
    delete buttonHBoxLayout;
    delete mainVBoxLayout;
}

/******************************************************************************
 * Creates all the elements shown on the about dialog.
 ******************************************************************************/
void About::createElements()
{
    mainVBoxLayout = new QVBoxLayout;
    buttonHBoxLayout = new QHBoxLayout;

    imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap(":/resources/pics/splash.png"));

    QPalette pal;
    QColor bgColor("black");
    QColor fgColor("white");
    pal.setColor(QPalette::Base, bgColor);
    pal.setColor(QPalette::Text, fgColor);

    QPushButton *button = new QPushButton();
    button->setText("Ok");
    button->setMaximumWidth(90);
    connect(button, SIGNAL(clicked()), this, SLOT(closeDialog()));

    buttonHBoxLayout->addWidget(button);

    QString textToShow = QString();
    textToShow.append("<p>NER Evaluation Tool</p>");
    textToShow.append("</p>");
    textToShow.append("<p>Copyright 2013 - All rights reserved.</p>");
    textToShow.append("</p>");
    textToShow.append("<p>Universidad Autonoma de Barcelona</p></DIV>");

    textEdit = new QTextEdit(this);
    textEdit->setHtml(textToShow);
    textEdit->setReadOnly(true);
    textEdit->setCurrentFont(QFont("Verdana",10, QFont::Bold));
    textEdit->setAlignment(Qt::AlignRight);
    textEdit->setPalette(pal);
    mainVBoxLayout->addWidget(imageLabel);
    mainVBoxLayout->addWidget(textEdit);
    mainVBoxLayout->addLayout(buttonHBoxLayout);
}

void About::closeDialog()
{
    this->close();
}
