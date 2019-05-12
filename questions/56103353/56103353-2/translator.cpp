#include "translator.h"

Translator::Translator(QQmlEngine &engine, QObject *parent) : QObject(parent),
    m_engine(engine)
{
}

void Translator::setLanguage(const QString &language)
{
    if (language == QString("fr"))
    {
        m_trans_fr.load("WipeoutViewer_fr.qm");
        qApp->installTranslator(&m_trans_fr);
    }
    else if (language == QString("en"))
    {
        qApp->removeTranslator(&m_trans_fr);
    }

    m_engine.retranslate();

    emit languageChanged();
}
