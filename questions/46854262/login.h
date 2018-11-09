#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>

#include <QDebug>

class Login : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
public:
    explicit Login(QObject *parent = nullptr):QObject(parent){

    }
    Q_INVOKABLE void test(){
        qDebug()<<mUsername<<mPassword;
    }

    QString username() const{
        return mUsername;
    }

    void setUsername(const QString &username){
        if(mUsername == username)
            return;
        mUsername = username;
        emit usernameChanged(mUsername);
    }


    QString password() const{
    return mPassword;
    }

    void setPassword(const QString &password)
    {
        if(mPassword == password)
            return;
        mPassword = password;
        emit passwordChanged(mPassword);
    }

signals:
    void usernameChanged(QString username);
    void passwordChanged(QString password);
private:
    QString mUsername;
    QString mPassword;
};


#endif // LOGIN_H
