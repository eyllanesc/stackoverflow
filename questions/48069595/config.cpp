#include "config.h"

Config* Config::instance = 0;

Config::Config(QObject *parent):QObject(parent){
    m_File = "/some/path/to/settings/file/config.ini";
    loadSettings();
}

Config *Config::getInstance(){
    if (instance == 0)
        instance = new Config;
    return instance;
}

void Config::loadSettings(){
    QSettings settings(m_File, QSettings::IniFormat);
    settings.beginGroup("GROUP_NAME");
    m_someOtherValue = settings.value("someOtherValueConfig", "").toInt();
    settings.endGroup();
}
