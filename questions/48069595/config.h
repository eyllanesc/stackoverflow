#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>

class Config : public QObject
{
    static Config* instance;
    Q_OBJECT
    Q_PROPERTY(int someOtherValue READ someOtherValue NOTIFY someOtherValueChanged)
    explicit Config(QObject *parent = nullptr);

public:
    static Config *getInstance();
    int someOtherValue(){return m_someOtherValue;}
    void setSomeOtherValue(int someOtherValue);
    void loadSettings();

signals:
    void someOtherValueChanged();

public:
    int      m_someOtherValue;
    QString  m_File;

};

#endif // CONFIG_H
