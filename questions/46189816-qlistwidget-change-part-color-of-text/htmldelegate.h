#ifndef HTMLDELEGATE_H
#define HTMLDELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>
#include <QTextDocument>

class HtmlDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const
    {
        QStyleOptionViewItem options = option;
        initStyleOption(&options, index);

        painter->save();

        QTextDocument doc;
        doc.setHtml(options.text);

        options.text = "";
        options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

        painter->translate(options.rect.left(), options.rect.top());
        QRect clip(0, 0, options.rect.width(), options.rect.height());
        doc.drawContents(painter, clip);
        painter->restore();
    }

    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
    {
        QStyleOptionViewItem options = option;
        initStyleOption(&options, index);

        QTextDocument doc;
        doc.setHtml(options.text);
        doc.setTextWidth(options.rect.width());
        return QSize(doc.idealWidth(), doc.size().height());
    }
};

#endif // HTMLDELEGATE_H
