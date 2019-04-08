#include "wizard.h"

#include <QButtonGroup>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>

Wizard::Wizard(QWidget *parent) : QWizard(parent) {
  setPage(Start_Page, new StartPage);
  setPage(Page_1, new Page1);
  setPage(Page_2, new Page3);
  setPage(Page_3, new Page3);
  setPage(Page_4, new Page4);
  setPage(End_Page, new EndPage);
}

StartPage::StartPage(QWidget *parent) : QWizardPage(parent) {
  QVBoxLayout *lay = new QVBoxLayout(this);
  lay->addWidget(new QLabel("Start Page"));
  group = new QButtonGroup(this);
  for (const QString &text : {"Page1", "Page2", "Page4"}) {
    QRadioButton *radio = new QRadioButton(text);
    lay->addWidget(radio);
    group->addButton(radio);
  }
  group->buttons().first()->setChecked(true);
  lay->addStretch();
}

int StartPage::nextId() const {
  if (group->checkedButton()->text() == "Page1")
    return Wizard::Page_1;
  else if (group->checkedButton()->text() == "Page2")
    return Wizard::Page_2;
  return Wizard::Page_4;
}

Page1::Page1(QWidget *parent) : QWizardPage(parent) {
  QVBoxLayout *lay = new QVBoxLayout(this);
  lay->addWidget(new QLabel("Page1"));
}

int Page1::nextId() const { return Wizard::End_Page; }

Page2::Page2(QWidget *parent) : QWizardPage(parent) {
  QVBoxLayout *lay = new QVBoxLayout(this);
  lay->addWidget(new QLabel("Page2"));
}

int Page2::nextId() const { return Wizard::Page_3; }

Page3::Page3(QWidget *parent) : QWizardPage(parent) {
  QVBoxLayout *lay = new QVBoxLayout(this);
  lay->addWidget(new QLabel("Page3"));
}

int Page3::nextId() const { return Wizard::End_Page; }

Page4::Page4(QWidget *parent) : QWizardPage(parent) {
  QVBoxLayout *lay = new QVBoxLayout(this);
  lay->addWidget(new QLabel("Page4"));
}

int Page4::nextId() const { return Wizard::End_Page; }

EndPage::EndPage(QWidget *parent) : QWizardPage(parent) {
  QVBoxLayout *lay = new QVBoxLayout(this);
  lay->addWidget(new QLabel("End Page"));
}

int EndPage::nextId() const { return -1; }
