#ifndef CONFIGINTERFACE_H
#define CONFIGINTERFACE_H

#include <QObject>

class ConfigInterface : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString sql READ getTag WRITE setTag NOTIFY tagChanged)
  Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY
                 descriptionChanged)
public:
  ConfigInterface(QObject *parent = Q_NULLPTR);
  ~ConfigInterface();

  QString getTag() const;
  void setTag(const QString &tag);
  QString getDescription() const;
  void setDescription(const QString &description);

signals:
  void tagChanged(QString);
  void descriptionChanged(QString);

private:
  QString _tag;
  QString _description;
  QString QueryTemplate;
  QString ConnectString;
  QString MinimumId;
};

#endif // CONFIGINTERFACE_H
