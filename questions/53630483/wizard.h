#ifndef WIZARD_H
#define WIZARD_H

#include <QWizard>

class QButtonGroup;

class Wizard : public QWizard {
  Q_OBJECT
public:
  enum { Start_Page, Page_1, Page_2, Page_3, Page_4, End_Page };
  Wizard(QWidget *parent = nullptr);
};

class StartPage : public QWizardPage {
  Q_OBJECT
public:
  StartPage(QWidget *parent = nullptr);
  int nextId() const override;

private:
  QButtonGroup *group;
};

class Page1 : public QWizardPage {
  Q_OBJECT
public:
  Page1(QWidget *parent = nullptr);
  int nextId() const override;
};

class Page2 : public QWizardPage {
  Q_OBJECT
public:
  Page2(QWidget *parent = nullptr);
  int nextId() const override;
};

class Page3 : public QWizardPage {
  Q_OBJECT
public:
  Page3(QWidget *parent = nullptr);
  int nextId() const override;
};

class Page4 : public QWizardPage {
  Q_OBJECT
public:
  Page4(QWidget *parent = nullptr);
  int nextId() const override;
};

class EndPage : public QWizardPage {
  Q_OBJECT
public:
  EndPage(QWidget *parent = nullptr);
  int nextId() const override;
};
#endif // WIZARD_H
