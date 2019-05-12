#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QTranslator>
#include <QGuiApplication>
#include <QQmlEngine>

class Translator : public QObject
{
    Q_OBJECT

public:
    explicit Translator(QQmlEngine &engine, QObject *parent = nullptr);

signals:
    void languageChanged();

public slots:
    void setLanguage(const QString &language);

private:
    QQmlEngine &m_engine;
    QTranslator m_trans_fr;
};
#endif // TRANSLATOR_H
