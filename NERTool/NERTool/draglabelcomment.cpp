#include "draglabelcomment.h"

/*******************************************************************************
 * Comment Dialog class editor...
 * A "nested" class for comment editing of each dragwidget...
 ******************************************************************************/
DragLabelComment::DragLabelComment(QWidget *parent) : QDialog(parent)
{
    label = new QLabel(this);
    label->setText("Comment");
    editText = new QTextEdit(this);
    saveButton = new QPushButton(this);
    saveButton->setText(QString("Ok"));
    saveButton->resize(50,saveButton->sizeHint().height());
    saveButton->setBaseSize(QSize(50, saveButton->sizeHint().height()));
    mainVBoxLay = new QVBoxLayout(this);

    mainVBoxLay->addWidget(label);
    mainVBoxLay->addWidget(editText);
    mainVBoxLay->addWidget(saveButton);

    setWindowTitle(QString("Edition Comment"));

    setLayout(mainVBoxLay);
    setWindowModality(Qt::WindowModal);

    resize(400, 200);
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->move( screen.center() - this->rect().center() );

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveCommentSlot()));
}

DragLabelComment::~DragLabelComment()
{

}

void DragLabelComment::setEditComment(QString &text)
{
    editText->setText(text);

}

QString DragLabelComment::getEditComment()
{
    return editText->toPlainText();
}


void DragLabelComment::saveCommentSlot(){
    close();
}
