#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <QtXml>
#include <QUrl>
#include <QFileDialog>
#include <QDebug>

struct unit{
    QString name;
    QString parent;
    QString level;
    QVariantList subNodes;

    bool operator==(unit o) const {
          return (name == o.name &&
                  parent== o.parent &&
                  level == o.level &&
                  subNodes == o.subNodes);
    }
};

class Data:public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr);
    QVector<unit> items() const;
    bool setItemAt(int index, const unit &item);
    void appendItem();
    void removeItem(const QString props);
signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

private:
    QVector<unit> menu;
};

#endif // Data_H
