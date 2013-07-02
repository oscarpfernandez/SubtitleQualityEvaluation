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
    setFixedSize(sizeHint().width(),520);
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
    imageLabel->setPixmap(QPixmap(":/resources/pics/splash3.png"));

    QPalette pal;
    QColor bgColor("black");
    QColor fgColor("white");
    pal.setColor(QPalette::Base, bgColor);
    pal.setColor(QPalette::Text, fgColor);

    button = new QPushButton(this);
    button->setText("Ok");
    button->setMaximumWidth(90);
    connect(button, SIGNAL(clicked()), this, SLOT(closeDialog()));

    buttonCredits = new QPushButton(this);
    buttonCredits->setText("Credits");
    buttonCredits->setMaximumWidth(90);
    connect(buttonCredits, SIGNAL(clicked()), this, SLOT(showCredits()));

    buttonHBoxLayout->addWidget(button);
    buttonHBoxLayout->addWidget(buttonCredits);

    QString textToShow = QString();
    textToShow.append("<p>NER Evaluation Tool</p>");
    textToShow.append("</p>");
    textToShow.append("<p>Copyright 2013 - All rights reserved.</p>");
    textToShow.append("</p>");
    textToShow.append("<p>Universidad Autònoma de Barcelona</p></DIV>");

    textEdit = new QTextEdit(this);
    textEdit->setHtml(textToShow);
    textEdit->setReadOnly(true);
    textEdit->setCurrentFont(QFont("Verdana",10, QFont::Bold));
    textEdit->setAlignment(Qt::AlignRight);
    textEdit->setPalette(pal);

    QString credits;
    credits.append("\nSoftware developed by:\n\n");
    credits.append("Oscar Lopes <oscar.pino.lopes@gmail.com>\n");
    credits.append("CaiaC Research - http://caiac.uab.cat\n");
    credits.append("\nJuan Martinez <juan.martinez@speedchill.com>\n");
    credits.append("SwissTXT - http://www.swisstxt.ch\n");
    credits.append("\nJavier Serrano <javier.serrano@uab.cat>\n");
    credits.append("CaiaC Research - http://caiac.uab.cat\n");


    creditsLabel = new QLabel;
    creditsLabel->setPixmap(QPixmap(":/resources/pics/caiac_uab.png"));

    creditsTextEdit = new QTextEdit(this);
    creditsTextEdit->setText(credits);
    creditsTextEdit->setReadOnly(true);
    creditsTextEdit->setPalette(pal);
    creditsTextEdit->setCurrentFont(QFont("Courier",16, QFont::Bold));
    creditsTextEdit->setMaximumHeight(250);

    creditsLayout = new QVBoxLayout;
    creditsLayout->addWidget(creditsLabel);
    creditsLayout->addWidget(creditsTextEdit);

    creditsDiag = new QDialog(this);
    creditsDiag->setLayout(creditsLayout);
    creditsDiag->setMinimumSize(creditsDiag->sizeHint());
    creditsDiag->setMaximumSize(creditsDiag->sizeHint());

    mainVBoxLayout->addWidget(imageLabel);
    mainVBoxLayout->addWidget(textEdit);
    mainVBoxLayout->addLayout(buttonHBoxLayout);


    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::black);
    setPalette(palette);
}

void About::closeDialog()
{
    this->close();
}

void About::showCredits()
{
    creditsDiag->show();
}
