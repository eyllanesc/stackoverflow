#include <QtQuickWidgets>

class Widget : public QWidget {
  Q_OBJECT
public:
  Widget(QWidget *parent = nullptr)
      : QWidget(parent), m_widget(new QQuickWidget) {
    m_widget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    QPushButton *button1 = new QPushButton("show 1");
    QPushButton *button2 = new QPushButton("show 2");

    QHBoxLayout *lay = new QHBoxLayout(this);
    QVBoxLayout *vlay = new QVBoxLayout;
    vlay->addWidget(button1);
    vlay->addWidget(button2);
    lay->addLayout(vlay);
    lay->addWidget(m_widget);

    connect(button1, &QPushButton::clicked, this, &Widget::show1);
    connect(button2, &QPushButton::clicked, this, &Widget::show2);
    show1();
  }
private slots:
  void show1() { m_widget->setSource(QUrl("qrc:/main1.qml")); }
  void show2() { m_widget->setSource(QUrl("qrc:/main2.qml")); }

private:
  QQuickWidget *m_widget;
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget w;
  w.show();
  return a.exec();
}

#include "main.moc"
