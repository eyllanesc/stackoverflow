#ifndef INTERFACAGEQML_H
#define INTERFACAGEQML_H

#include <QObject>
#include <QQmlEngine>



class interfacageQML : public QObject
{
    Q_OBJECT
    static interfacageQML* instance;
    explicit interfacageQML(QObject *parent = nullptr);
public:
    static interfacageQML *getInstance();
    ~interfacageQML();
    Q_INVOKABLE void mouseClick();

signals:
    void clicked();
};
#endif // INTERFACAGEQML_H
