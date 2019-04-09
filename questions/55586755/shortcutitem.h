#ifndef SHORTCUTITEM_H
#define SHORTCUTITEM_H

#include <QObject>

class ShortcutItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString action READ action WRITE setAction NOTIFY actionChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QString font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged )
public:
    explicit ShortcutItem(QObject *parent = nullptr);
    QString title() const;
    void setTitle(const QString &title);

    QString action() const;
    void setAction(const QString &action);

    QString icon() const;
    void setIcon(const QString &icon);

    QString font() const;
    void setFont(const QString &font);

    int size() const;
    void setSize(int size);

signals:
    void titleChanged(QString title);
    void actionChanged(QString action);
    void iconChanged(QString icon);
    void fontChanged(QString font);
    void sizeChanged(int size);
private:
    QString _title;
    QString _action;
    QString _icon;
    QString _font;
    int _size;
};
#endif // SHORTCUTITEM_H
