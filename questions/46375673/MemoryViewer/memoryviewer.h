#ifndef MEMORYVIEWER_H
#define MEMORYVIEWER_H

#include <QAbstractScrollArea>
#include <QBuffer>

class MemoryViewer : public QAbstractScrollArea
{
    Q_OBJECT
public:
    MemoryViewer(QWidget *parent = 0);
    ~MemoryViewer();

    void setData(const QByteArray &ba);
    bool setData(QIODevice &device);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

private:
    void adjustContent();
    void init();

    int addressWidth();
    int hexWidth();
    int asciiWidth();

    QByteArray data(qint64 pos=0, qint64 count=-1);

    int nBlockAddress;
    int mBytesPerLine;

    int pxWidth;
    int pxHeight;

    qint64 startPos;
    qint64 endPos;

    int nRowsVisible;

    QBuffer buffer;
    QIODevice *ioDevice;
    qint64 size;

    QByteArray dataVisible;
    QByteArray dataHex;
};

#endif // MEMORYVIEWER_H
