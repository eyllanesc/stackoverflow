#include "logdialog.h"
#include "ui_logdialog.h"

#include <QTimer>

logdialog::logdialog(const QString &filename, QWidget *parent) :
    QDialog(parent),
    uilog(new Ui::logdialog)
{
    uilog->setupUi(this);
    initializeQTimer();
    fillLogInfoChronically(filename);
}

logdialog::~logdialog()
{
    m_logFileStream.close();
    delete uilog;
}

void logdialog::fillloginfo()
{
    std::string line;
    m_logFileStream.clear();
    while (getline(m_logFileStream,line)){
        uilog->textBrowser->append(QString::fromStdString(line));
    }
}

void logdialog::initializeQTimer()
{
    m_Timer = NULL;

    //create the timer object
    m_Timer = new QTimer(this);

    QObject::connect(m_Timer,SIGNAL(timeout()), this,SLOT(fillLogInfoChronicallySlot()));

}

void logdialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)

    m_Timer->stop();

    if ( m_logFileStream.is_open()){
        m_logFileStream.close();
    }
}

void logdialog::fillLogInfoChronically(const QString &logFilePath)
{
    uilog->textBrowser->clear();

    //m_LastLinePos = 0;

    m_logFilePath = logFilePath;

    std::string m_logFilePathStr= m_logFilePath.toStdString();
    m_logFileStream.open(m_logFilePathStr.c_str());

    if (m_logFileStream.is_open()){

        fillloginfo();

        m_Timer->start(1000);
    }

}

void logdialog::fillLogInfoChronicallySlot()
{
    fillloginfo();
}
