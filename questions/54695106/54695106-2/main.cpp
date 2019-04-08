#include <QtQuickWidgets>

class Widget : public QWidget {
  Q_OBJECT
public:
  Widget(QWidget *parent = nullptr)
      : QWidget(parent), m_stacked_widget(new QStackedWidget) {
    for (const QString &url : {"qrc:/main1.qml", "qrc:/main2.qml"}) {
      QQuickWidget *widget = new QQuickWidget;
      widget->setResizeMode(QQuickWidget::SizeRootObjectToView);
      widget->setSource(QUrl(url));
      m_stacked_widget->addWidget(widget);
    }
    QPushButton *button1 = new QPushButton("show 1");
    QPushButton *button2 = new QPushButton("show 2");

    QHBoxLayout *lay = new QHBoxLayout(this);
    QVBoxLayout *vlay = new QVBoxLayout;
    vlay->addWidget(button1);
    vlay->addWidget(button2);
    lay->addLayout(vlay);
    lay->addWidget(m_stacked_widget);

    connect(button1, &QPushButton::clicked, this, &Widget::show1);
    connect(button2, &QPushButton::clicked, this, &Widget::show2);
    show1();
  }
private slots:
  void show1() { m_stacked_widget->setCurrentIndex(0); }
  void show2() { m_stacked_widget->setCurrentIndex(1); }

private:
  QStackedWidget *m_stacked_widget;
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget w;
  w.show();
  return a.exec();
}

#include "main.moc"
