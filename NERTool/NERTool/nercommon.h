#ifndef NERCOMMON_H
#define NERCOMMON_H

#include <qstring.h>

const QString NER_APP_NAME = "NER Tool";
const int SUBTITLE_CHECK_INTERVAL = 50;
const int SUBTITLE_CLEAN_TIMEOUT = 2500;

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

#ifndef SPEAKER
#define SPEAKER
struct Speaker
{
private:
    QString sId;
    QString sName;
    QString sType;
public:
    Speaker& setId(const QString &id){sId = id; return *this;}
    Speaker& setName(const QString &name){ sName=name; return *this;}
    Speaker& setType(const QString &type){ sType=type; return *this;}
    QString getId(){return sId;}
    QString getName(){return sName;}
    QString getType(){return sType;}
};
#endif

/*******************************************************************************
 * Structure to hold the NER Model statistic data per table.
 ******************************************************************************/
#ifndef NER_STATS_DATA
#define NER_STATS_DATA
struct NERStatsData
{
private:
    int     NCount;
    double  nerValue;
    double  editionErrors;
    double  recognitionErrors;
    double  delayAcumulated;
    int     delayCount;
public:
    int getNCount(){return NCount;}
    NERStatsData& setNCount(int n){
        NCount=n;
        return *this;}
    double getNerValue(){return nerValue;}
    NERStatsData& setNerValue(double ner){
        nerValue=ner;
        return *this;}
    double getEditionErrors(){return editionErrors;}
    NERStatsData& setEditionErrors(double er){
        editionErrors=er;
        return *this;}
    double getRecognitionErrors(){return recognitionErrors;}
    NERStatsData& setRecognitionErrors(double re){
        recognitionErrors=re;
        return *this;}
    double getDelayAcumulated(){return delayAcumulated;}
    NERStatsData& setDelayAcumulated(double delay){
        delayAcumulated=delay;
        return *this;}
    int getDelayCount(){return delayCount;}
    NERStatsData& setDelayCount(int dc){
        delayCount=dc;
        return *this;}
};
#endif

/******************************************************************************
 * Debug setup
 *****************************************************************************/
class NullDebug
{
public:
    template <typename T>
    NullDebug& operator<<(const T&) { return *this; }
};

inline NullDebug nullDebug() { return NullDebug(); }

#define DEBUG_ENABLED //Comment this to disable debug information...

#ifdef DEBUG_ENABLED
#   define ENGINE_DEBUG qDebug() //business as usual...
#else
#   define ENGINE_DEBUG nullDebug() //dummy debug...
#endif

/*** End of debug setup *******************************************************/

#endif // NERCOMMON_H
