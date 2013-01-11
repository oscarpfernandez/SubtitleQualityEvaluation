#ifndef NERCOMMON_H
#define NERCOMMON_H

/*
 * Struct to hold each line contained on the TRS XML file.
 */
#ifndef BLOCK_TRS
#define BLOCK_TRS
struct BlockTRS
{
private:
    QString speaker;
    QString syncTime;
    QString text;
public:
    BlockTRS& setSpeaker(QString s){speaker=s; return *this;}
    BlockTRS& setSyncTime(QString t){syncTime=t; return *this;}
    BlockTRS& setText(QString txt){text=txt; return *this;}
    QString getSpeaker(){return speaker;}
    QString getSyncTime(){return syncTime;}
    QString getText(){return text;}
    QString toString(){
        return QString("\tBlock -> ")
                .append(speaker).append(" - ")
                .append(syncTime).append("\n\t")
                .append(text.trimmed());
    }
};
#endif

#endif // NERCOMMON_H
