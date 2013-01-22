#include "dragwidgetcomment.h"

/*******************************************************************************
 * Comment Dialog class editor...
 * A "nested" class for comment editing of each dragwidget...
 ******************************************************************************/
DragWidgetComment::DragWidgetComment(QWidget *parent) : QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    label = new QLabel(this);
    label->setText("Comment");
    editText = new QTextEdit(this);
    saveButton = new QPushButton(this);
    saveButton->setText(QString("Save"));
    saveButton->setBaseSize(QSize(50, saveButton->sizeHint().height()));
    mainVBoxLay = new QVBoxLayout(this);

    mainVBoxLay->addWidget(label);
    mainVBoxLay->addWidget(editText);
    mainVBoxLay->addWidget(saveButton);

    setWindowTitle(QString("Edition Comment"));

    setLayout(mainVBoxLay);
    setWindowModality(Qt::WindowModal);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveCommentSlot()));
}

DragWidgetComment::~DragWidgetComment()
{

}

void DragWidgetComment::setEditComment(QString &text)
{

}

QString DragWidgetComment::getComment()
{
    return editText->toPlainText();
}

void DragWidgetComment::saveCommentSlot(){
    QString et = editText->toPlainText();
    emit saveComment(et);
    this->close();
}
