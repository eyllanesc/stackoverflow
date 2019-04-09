#include "shortcutitem.h"

ShortcutItem::ShortcutItem(QObject *parent) : QObject(parent)
{

}

QString ShortcutItem::title() const
{
    return _title;
}

void ShortcutItem::setTitle(const QString &title)
{
    if(_title == title) return;
    _title = title;
    Q_EMIT titleChanged(_title);
}

QString ShortcutItem::action() const
{
    return _action;
}

void ShortcutItem::setAction(const QString &action)
{
    if(_action == action) return;
    _action = action;
    Q_EMIT actionChanged(_action);
}

QString ShortcutItem::icon() const
{
    return _icon;
}

void ShortcutItem::setIcon(const QString &icon)
{
    if(_icon == icon) return;
    _icon = icon;
    Q_EMIT iconChanged(_icon);
}

QString ShortcutItem::font() const
{
    return _font;
}

void ShortcutItem::setFont(const QString &font)
{
    if(_font == font) return;
    _font = font;
    Q_EMIT fontChanged(_font);
}

int ShortcutItem::size() const
{
    return _size;
}

void ShortcutItem::setSize(int size)
{
    if(_size == size) return;
    _size = size;
    Q_EMIT sizeChanged(_size);
}
