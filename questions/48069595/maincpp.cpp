#include "maincpp.h"

MainCpp::MainCpp(QObject *parent):QObject(parent){
    Config *configPointer = Config::getInstance();
    m_someValue = configPointer->someOtherValue();
    emit someValueChanged();
}

void MainCpp::update(int var)
{
    Config *configPointer = Config::getInstance();
    QSettings settings("/some/path/to/settings/file/config.ini", QSettings::IniFormat);
    settings.setValue("GROUP_NAME/someOtherValueConfig", var);
    configPointer->m_someOtherValue = var;
    m_someValue = configPointer->someOtherValue();
    emit configPointer->someOtherValueChanged();
    emit someValueChanged();
}
