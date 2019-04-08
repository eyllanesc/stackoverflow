#include <QApplication>

#include <QDebug>
#include <QWizard>

#include "custompage.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QWizard w;
  CustomPage *page = new CustomPage;
  w.addPage(page);
  page->setRect(QRect(200, 100, 200, 100));
  page->setRadius(10);

  page->setHideRect(false);

  QObject::connect(page, &CustomPage::onClicked, [=](CustomPage::Position pos) {
    switch (pos) {
    case CustomPage::topLeft:
      qDebug() << "topLeft";
      break;
    case CustomPage::topRight:
      qDebug() << "topRight";
      break;
    case CustomPage::bottomLeft:
      qDebug() << "bottomLeft";
      break;
    case CustomPage::bottomRight:
      qDebug() << "bottomRight";
      break;
    }
  });
  w.show();

  return a.exec();
}
