#include "nertableassessment.h"

/*******************************************************************************
 * Comment Dialog class editor...
 * A "nested" class for comment editing of each dragwidget...
 ******************************************************************************/
NERTableAssessment::NERTableAssessment(QWidget *parent) : QDialog(parent)
{
    label = new QLabel(this);
    label->setText("Assessment Comments");
    editText = new QTextEdit(this);
    saveButton = new QPushButton(this);
    saveButton->setText(QString("Ok"));
    saveButton->resize(50,saveButton->sizeHint().height());
    saveButton->setBaseSize(QSize(50, saveButton->sizeHint().height()));
    mainVBoxLay = new QVBoxLayout(this);

    mainVBoxLay->addWidget(label);
    mainVBoxLay->addWidget(editText);
    mainVBoxLay->addWidget(saveButton);

    setWindowTitle(QString("Assessment Comment"));

    setLayout(mainVBoxLay);
    setWindowModality(Qt::WindowModal);

    resize(600, 300);
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move( screen.center() - this->rect().center() );

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveCommentSlot()));
}

NERTableAssessment::~NERTableAssessment()
{

}

void NERTableAssessment::setEditComment(QString &text)
{
    editText->setText(text);

}

QString NERTableAssessment::getEditComment()
{
    return editText->toHtml();
}


void NERTableAssessment::saveCommentSlot(){
    close();
}
