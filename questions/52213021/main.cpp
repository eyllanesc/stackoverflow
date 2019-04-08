#include <QApplication>
#include <QHBoxLayout>
#include <QQuickWidget>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QWidget w;
  QHBoxLayout *lay = new QHBoxLayout{&w};
  for (const QString &url :
       {"qrc:/Curve1.qml", "qrc:/Curve2.qml", "qrc:/Curve3.qml"}) {
    QQuickWidget *widget = new QQuickWidget(QUrl(url));
    widget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    lay->addWidget(widget);
  }
  w.resize(900, 300);
  w.show();

  return a.exec();
}
