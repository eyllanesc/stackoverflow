#include "memoryviewer.h"

#include <QPainter>
#include <QScrollBar>

MemoryViewer::MemoryViewer(QWidget *parent):QAbstractScrollArea(parent)
{
    ioDevice = new QBuffer(this);
    init();
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &MemoryViewer::adjustContent);
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &MemoryViewer::adjustContent);
}

MemoryViewer::~MemoryViewer()
{

}


void MemoryViewer::init()
{
    nBlockAddress = 2;
    mBytesPerLine = 16;

    pxWidth = fontMetrics().width(QChar('0'));
    pxHeight = fontMetrics().height();

}

int MemoryViewer::addressWidth()
{
    return  (nBlockAddress*4+ nBlockAddress -1)*pxWidth;
}

int MemoryViewer::hexWidth()
{
    return (mBytesPerLine*3+1)*pxWidth;
}

int MemoryViewer::asciiWidth()
{
    return (mBytesPerLine*2 +1)*pxWidth;
}

QByteArray MemoryViewer::data(qint64 pos, qint64 count)
{
    QByteArray buffer;

    if (pos >= size)
        return buffer;

    if (count < 0)
        count = size;
    else
        if ((pos + count) > size)
            count = size - pos;

    if(ioDevice->open(QIODevice::ReadOnly)){
        ioDevice->seek(pos);
        buffer = ioDevice->read(count);
        ioDevice->close();
    }
    return buffer;
}

void MemoryViewer::setData(const QByteArray &ba)
{
    buffer.setData(ba);
    setData(buffer);

}

bool MemoryViewer::setData(QIODevice &device)
{
    ioDevice = &device;
    bool ok = ioDevice->open(QIODevice::ReadOnly);
    if(ok){
        size = ioDevice->size();
        ioDevice->close();
    }
    else{
        QBuffer *buf = new QBuffer(this);
        ioDevice = buf;
    }
    init();
    adjustContent();
    return ok;
}

void MemoryViewer::resizeEvent(QResizeEvent *)
{
    adjustContent();
}


void MemoryViewer::paintEvent(QPaintEvent *)
{
    QPainter painter(viewport());

    int offsetX = horizontalScrollBar()->value();

    int y = pxHeight;
    QString address;

    painter.setPen(viewport()->palette().color(QPalette::WindowText));

    for(int row = 0; row <= dataVisible.size()/mBytesPerLine;  row++){
        QString str = QString("%1").arg(startPos + mBytesPerLine*row, nBlockAddress*4, 16, QChar('0')).toUpper();
        int i = 0;
        address = "";
        while(i < nBlockAddress){
            address += str.mid(i*4, 4) + ":";
            i++;
        }
        address.remove(address.size()-1, 1);

        painter.drawText(pxWidth/2 -offsetX , y, address);
        y+=pxHeight;
    }

    int x;
    int lx = addressWidth() +pxWidth;
    painter.drawLine(lx-offsetX, 0, lx-offsetX, height());
    lx += pxWidth/2;
    y = pxHeight;

    //hex data
    x = lx-offsetX+3*pxWidth;
    int w = 3*pxWidth;
    for(int col =0; col < mBytesPerLine/2; col++){
        painter.fillRect(x-pxWidth/2, 0, w, height(), viewport()->palette().color(QPalette::AlternateBase));
        x+= 6*pxWidth;
    }

    int bPos = 0;
    for(int row=0; row < nRowsVisible; row++){
        x = lx-offsetX;
        for(int col =0; (col < mBytesPerLine) && (bPos < dataHex.size()) ; col++){
            QString str = dataHex.mid(bPos*2,2).toUpper();
            painter.drawText(x, y, str);
            x += 3*pxWidth;
            bPos += 1;
        }
        y+= pxHeight;
    }

    lx = addressWidth() + hexWidth();
    painter.drawLine(lx-offsetX, 0, lx-offsetX, height());

    lx += pxWidth/2;

    bPos = 0;
    y = pxHeight ;
    int ch;
    for(int row=0; row < nRowsVisible; row++){
        x = lx-offsetX;
        for(int col =0; (col < mBytesPerLine) && (bPos < dataVisible.size()) ; col++){
            ch  = (uchar)dataVisible.at(bPos);
            if ( ch < 0x20 )
                ch = '.';
            painter.drawText(x, y, QChar(ch));
            x += 2*pxWidth;
            bPos += 1;
        }
        y+= pxHeight;
    }
}

void MemoryViewer::adjustContent()
{
    int w = addressWidth() + hexWidth() + asciiWidth();
    horizontalScrollBar()->setRange(0, w - viewport()->width());
    horizontalScrollBar()->setPageStep(viewport()->width());

    nRowsVisible = viewport()->height()/pxHeight;
    int val = verticalScrollBar()->value();
    startPos = (qint64)val*mBytesPerLine;
    endPos = startPos + nRowsVisible*mBytesPerLine -1;

    int lineCount = size/mBytesPerLine;
    verticalScrollBar()->setRange(0,  lineCount-nRowsVisible);
    verticalScrollBar()->setPageStep(nRowsVisible);

    if(endPos >= size){
        endPos = size-1;
    }
    dataVisible = data(startPos, endPos-startPos + mBytesPerLine +1);
    dataHex = dataVisible.toHex();
    viewport()->update();
}
