#include "userinfo.h"

static const int _regUserInfo = qRegisterMetaType<UserInfo>("UserInfo");

UserInfo::UserInfo() : UserInfo("User") {}

UserInfo::UserInfo(const QString &title)
    : UserInfo(title, "Comment", QTime(0, 0, 0, 0),
               QImage(":/resources/icon.png")) {}

UserInfo::UserInfo(const QString &title, const QString &subtitle,
                   const QTime &time, const QImage &icon)
    : title(title), subtitle(subtitle), time(time), avatar(icon) {}

QImage UserInfo::getAvatar() const { return avatar; }

void UserInfo::setAvatar(const QImage &value) { avatar = value; }

QTime UserInfo::getTime() const { return time; }

void UserInfo::setTime(const QTime &value) { time = value; }

QString UserInfo::getSubtitle() const { return subtitle; }

void UserInfo::setSubtitle(const QString &value) { subtitle = value; }

QString UserInfo::getTitle() const { return title; }

void UserInfo::setTitle(const QString &value) { title = value; }

UserInfo::UserInfo(const UserInfo &) = default;
UserInfo::~UserInfo() = default;
