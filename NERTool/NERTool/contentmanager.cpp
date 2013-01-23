#include "contentmanager.h"

ContentManager::ContentManager(QObject *parent) :
    QObject(parent)
{
    transcriptionList = new QList<BlockTRS>();
    xmlHandler = new XMLHandler();
    isTranscriptionLoaded = false;
}

ContentManager::~ContentManager()
{

}

void ContentManager::loadTranscriptionFile(QString &fileName)
{


}

void ContentManager::loadSubtitleFile(QString &fileName)
{

}


