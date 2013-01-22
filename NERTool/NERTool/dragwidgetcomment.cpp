#include "dragwidgetcomment.h"

/*******************************************************************************
 * Comment Dialog class editor...
 * A "nested" class for comment editing of each dragwidget...
 ******************************************************************************/
DragWidgetComment::DragWidgetComment(QWidget *parent) : QDialog(parent)
{
    label = new QLabel(this);
    label->setText("Comment");
    editText = new QTextEdit(this);
    saveButton = new QPushButton(this);
    saveButton->setText(QString("Save"));
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

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveCommentSlot()));
}

DragWidgetComment::~DragWidgetComment()
{

}

void DragWidgetComment::setEditComment(QString &text)
{
    editText->setText(text);

}

QString DragWidgetComment::getEditComment()
{
    return editText->toPlainText();
}


void DragWidgetComment::saveCommentSlot(){
    QString et = editText->toPlainText();
    setEditComment(et);
    close();
}
