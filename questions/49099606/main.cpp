
#include <QApplication>
#include <QComboBox>
#include <QFormLayout>
#include <QScrollArea>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QStringList keys;
  QList<int> status;
  for (int i = 0; i < 100; i++) {
    keys << QString("key %1").arg(i);
    status << i % 4;
  }

  QWidget *wdg = new QWidget;
  QScrollArea *scroll = new QScrollArea;

  QWidget *content_widget = new QWidget;

  QFormLayout *formLayout = new QFormLayout(content_widget);

  QStringList items{"Present", "Present and Voting", "Absent",
                    "Absent from Commitee"};

  for (int x = 0; x < keys.size(); x++) {

    QComboBox *combo = new QComboBox;
    combo->addItems(items);
    combo->setProperty("MyIndex", x);
    combo->setCurrentIndex(status[x]);
    formLayout->addRow(keys.at(x), combo);
    // connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(roll(int)));
  }

  scroll->setWidget(content_widget);
  wdg->setLayout(new QVBoxLayout);
  wdg->layout()->addWidget(scroll);
  wdg->show();

  return a.exec();
}
