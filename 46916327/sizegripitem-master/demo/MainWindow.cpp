/*
 * Copyright (c) 2011 Cesar L. B. Silveira
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SizeGripItem.h"

namespace
{
    class RectResizer : public SizeGripItem::Resizer
    {
        public:
            virtual void operator()(QGraphicsItem* item, const QRectF& rect)
            {
                QGraphicsRectItem* rectItem =
                    dynamic_cast<QGraphicsRectItem*>(item);

                if (rectItem)
                {
                    rectItem->setRect(rect);
                }
            }
    };

    class EllipseResizer : public SizeGripItem::Resizer
    {
        public:
            virtual void operator()(QGraphicsItem* item, const QRectF& rect)
            {
                QGraphicsEllipseItem* ellipseItem =
                    dynamic_cast<QGraphicsEllipseItem*>(item);

                if (ellipseItem)
                {
                    ellipseItem->setRect(rect);
                }
            }
    };
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;

    QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(0, 0, 320, 240));
    rectItem->setBrush(Qt::red);
    rectItem->setPen(Qt::NoPen);
    rectItem->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(rectItem);

    QGraphicsEllipseItem* ellipseItem =
        new QGraphicsEllipseItem(QRectF(0, 0, 200, 200));
    ellipseItem->setBrush(Qt::blue);
    ellipseItem->setPen(Qt::NoPen);
    ellipseItem->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(ellipseItem);

    SizeGripItem* rectSizeGripItem =
        new SizeGripItem(new RectResizer, rectItem);
    SizeGripItem* ellipseSizeGripItem =
        new SizeGripItem(new EllipseResizer, ellipseItem);

    QGraphicsView* graphicsView = new QGraphicsView(this);
    graphicsView->setScene(scene);

    setCentralWidget(graphicsView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
