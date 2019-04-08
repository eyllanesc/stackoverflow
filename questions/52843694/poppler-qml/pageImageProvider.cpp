/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Anthony Granger <grangeranthony@gmail.com>
 */

#include <QDebug>
#include <QPaintDevice>
#include <QQuickImageProvider>
#include <poppler/qt5/poppler-qt5.h>

#include "pageImageProvider.h"
#include "pdfModel.h"

PageImageProvider::PageImageProvider(Poppler::Document *pdfDocument)
    : QQuickImageProvider(QQuickImageProvider::Image) {
  this->document = pdfDocument;
}

QImage PageImageProvider::requestImage(const QString &id, QSize *size,
                                       const QSize &requestedSize) {
  Q_UNUSED(size)
  float scale = 1.0;
  QString type = id.section("/", 0, 0);
  QImage result;
  QSizeF pageSize;
  QSizeF pageSizePhys;
  float res = 0;
  Poppler::Page *page;

  if (type == "page") {
    int numPage = id.section("/", 1, 1).toInt();

    DEBUG << "Page" << numPage << "requested";

    page = document->page(numPage - 1);
    if (!page)
      return result;

    pageSize = page->pageSizeF();

    pageSizePhys.setWidth(pageSize.width() / 72);
    // pageSizePhys.setHeight(pageSize.height() / 72);

    DEBUG << "Requested size :" << requestedSize.width() << ";"
          << requestedSize.height();

    // if (pageSizePhys.height() >= pageSizePhys.width())
    res = requestedSize.width() / pageSizePhys.width();
    /*else
        res = requestedSize.height() / pageSizePhys.height();*/

    DEBUG << "Size :" << pageSizePhys.width() << ";" << pageSizePhys.height();
    DEBUG << "Resolution :" << res;

    result = page->renderToImage(
        scale * res, scale * res); // For poppler the first page have the id 0
  }

  return result;
}
