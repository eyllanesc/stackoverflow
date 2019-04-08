#ifndef USERINFO_H
#define USERINFO_H

#include <QImage>
#include <QString>
#include <QTime>

class UserInfo {
public:
  UserInfo();
  UserInfo(const UserInfo &);
  ~UserInfo();

  QString getTitle() const;
  QString getSubtitle() const;
  QTime getTime() const;
  QImage getAvatar() const;

  void setTitle(const QString &value);
  void setSubtitle(const QString &value);
  void setTime(const QTime &value);
  void setAvatar(const QImage &value);

private:
  UserInfo(const QString &title);
  UserInfo(const QString &title, const QString &subtitle, const QTime &time,
           const QImage &icon);

  QString title;
  QString subtitle;
  QTime time;
  QImage avatar;
};

Q_DECLARE_METATYPE(UserInfo)

#endif // USERINFO_H
