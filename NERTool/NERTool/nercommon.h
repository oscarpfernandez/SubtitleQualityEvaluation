#ifndef NERCOMMON_H
#define NERCOMMON_H

#include <qstring.h>
#include <QDebug>
#include <QDate>

const QString NER_APP_NAME = "NER Tool";
const int SUBTITLE_CHECK_INTERVAL = 50;
const int SUBTITLE_CLEAN_TIMEOUT = 2500;

#ifndef LICENCE_DATA
#define LICENCE_DATA
struct LicenceData
{
public:
    QString user;
    QString org;
    QString mac;
    QDate startDate;
    QDate finishDate;
};
#endif

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
    int     N_words;
    int     N_ponctuation;
    int     N_transitions;
    double  nerValue;
    double  editionErrors;
    int     editionErrors_w000;
    int     editionErrors_w025;
    int     editionErrors_w050;
    int     editionErrors_w100;
    double  recognitionErrors;
    int     recognitionErrors_w000;
    int     recognitionErrors_w025;
    int     recognitionErrors_w050;
    int     recognitionErrors_w100;
    double  correctEditions;
    int     correctEditions_w000;
    int     correctEditions_w025;
    int     correctEditions_w050;
    int     correctEditions_w100;
    double  avgDelay;
    int     editionErrorInsertions;
    int     editionErrorDeletions;
    int     editionErrorSubstitutions;
    int     recogErrorInsertions;
    int     recogErrorDeletions;
    int     recogErrorSubstitutions;

public:
    int getNCount(){
        return N_words + N_ponctuation + N_transitions;}
    NERStatsData& setNCount(int n){
        NCount=n;
        return *this;}
    NERStatsData& setN_words(int n){
        N_words=n;
        return *this;}
    int getN_words(){
        return N_words;}
    NERStatsData& setN_ponctuation(int n){
        N_ponctuation=n;
        return *this;}
    int getN_ponctuation(){
        return N_ponctuation;}
    NERStatsData& setN_transitions(int n){
        N_transitions=n;
        return *this;}
    int getN_transitions(){
        return N_transitions;}
    double getNerValue(){return nerValue;}
    NERStatsData& setNerValue(double ner){
        nerValue=ner;
        return *this;}
    //Edition Errors
    double getEditionErrors(){
        return editionErrors;}
    NERStatsData& setEditionErrors(double er){
        editionErrors=er;
        return *this;}
    NERStatsData& incEditionErrors_w000(){
        editionErrors_w000++;
        return *this;}
    int getEditionErrors_w000(){
        return editionErrors_w000;}
    NERStatsData& incEditionErrors_w025(){
        editionErrors_w025++;
        return *this;}
    int getEditionErrors_w025(){
        return editionErrors_w025;}
    NERStatsData& incEditionErrors_w050(){
        editionErrors_w050++;
        return *this;}
    int getEditionErrors_w050(){
        return editionErrors_w050;}
    NERStatsData& incEditionErrors_w100(){
        editionErrors_w100++;
        return *this;}
    int getEditionErrors_w100(){
        return editionErrors_w100;}

    //Recognition Errors
    double getRecognitionErrors(){
        return recognitionErrors;}
    NERStatsData& setRecognitionErrors(double re){
        recognitionErrors=re;
        return *this;}
    NERStatsData& incRecognitionErrors_w000(){
        recognitionErrors_w000++;
        return *this;}
    int getRecognitionErrors_w000(){
        return recognitionErrors_w000;}
    NERStatsData& incRecognitionErrors_w025(){
        recognitionErrors_w025++;
        return *this;}
    int getRecognitionErrors_w025(){
        return recognitionErrors_w025;}
    NERStatsData& incRecognitionErrors_w050(){
        recognitionErrors_w050++;
        return *this;}
    int getRecognitionErrors_w050(){
        return recognitionErrors_w050;}
    NERStatsData& incRecognitionErrors_w100(){
        recognitionErrors_w100++;
        return *this;}
    int getRecognitionErrors_w100(){
        return recognitionErrors_w100;}

    //Correct Editions
    double getCorrectEditions(){
        return correctEditions;}
    NERStatsData& setCorrectEditions(double ce){
        correctEditions=ce;
        return *this;}

    //Delay
    double getAvgDelay(){return avgDelay;}
    NERStatsData& setAvgDelay(double delay){
        avgDelay=delay;
        return *this;}
    //Insertions
    int getEdErrorInsertions(){
        return editionErrorInsertions;}
    NERStatsData& incEdErrorInsertions(){
        editionErrorInsertions++;
        return *this;}
    int getRecogErrorInsertions(){
        return recogErrorInsertions;}
    NERStatsData& incRecogErrorInsertions(){
        recogErrorInsertions++;
        return *this;}

    //Deletions
    int getEdErrorDeletions(){
        return editionErrorDeletions;}
    NERStatsData& incEdErrorDeletions(){
        editionErrorDeletions++;
        return *this;}

    int getRecogErrorDeletions(){
        return recogErrorDeletions;}
    NERStatsData& incRecogErrorDeletions(){
        recogErrorDeletions++;
        return *this;}

    //Substitutions
    int getEdErrorSubstitutions(){
        return editionErrorSubstitutions;}
    NERStatsData& incEdErrorSubstitutions(){
        editionErrorSubstitutions++;
        return *this;}

    int getRecogErrorSubstitutions(){
        return recogErrorSubstitutions;}
    NERStatsData& incRecogErrorSubstitutions(){
        recogErrorSubstitutions++;
        return *this;}

    void resetDataToZero(){
        NCount = 0;
        N_words = 0;
        N_ponctuation = 0;
        N_transitions = 0;
        nerValue = 0;
        editionErrors = 0;
        editionErrors_w000 = 0;
        editionErrors_w025 = 0;
        editionErrors_w050 = 0;
        editionErrors_w100 = 0;
        recognitionErrors = 0;
        recognitionErrors_w000 = 0;
        recognitionErrors_w025 = 0;
        recognitionErrors_w050 = 0;
        recognitionErrors_w100 = 0;
        correctEditions = 0;
        correctEditions_w000 = 0;
        correctEditions_w025 = 0;
        correctEditions_w050 = 0;
        correctEditions_w100 = 0;
        avgDelay = 0;
        editionErrorInsertions = 0;
        editionErrorDeletions = 0;
        editionErrorSubstitutions = 0;
        recogErrorInsertions = 0;
        recogErrorDeletions = 0;
        recogErrorSubstitutions = 0;
    }
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
