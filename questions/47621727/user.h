#ifndef USER_H
#define USER_H

#include <QString>
#include <QMetaType>

class User
{
    QString mID;
    QString mUsername;
    QString mPassword;
    QString mName;
    QString mStatus;

public:
    User(){
        User("", "", "", "", "");
    }
    User(const QString& ID,
         const QString& username,
         const QString& password,
         const QString& name ,
         const QString& status){
         mID = ID;
         mUsername = username;
         mPassword = password;
         mName = name;
         mStatus = status;
    }
    ~User(){

    }
    QString toString(){
        return mID + " " + mUsername + " " + mPassword + " " + mName +  " " + mStatus;
    }
};

Q_DECLARE_METATYPE(User)
#endif // USER_H
