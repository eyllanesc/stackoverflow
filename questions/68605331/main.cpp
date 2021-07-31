#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <QComboBox>
#include <QHBoxLayout>

class Test
{
    QString msLanguage, msRegion;
public:
    Test();
    Test(const QString &sLanguage, const QString &sRegion);
    Test(const Test &refCopy);
    ~Test();

    QString &getLanguage() const;
    QString &getRegion() const;
    void setLanguage(const QString &sLanguage);
    void setRegion(const QString &sRegion);

    Test &operator=(const Test &refCopy);
    bool operator==(const Test &refOther) const;
    bool operator!=(const Test &refOther) const;
    operator QString() const;

    QString toString() const;
};

Test::Test()
{ }

Test::Test(const QString &sLanguage, const QString &sRegion)
    :   msLanguage(sLanguage)
    ,   msRegion(sRegion)
{ }

Test::Test(const Test &refCopy)
    :   Test(refCopy.getLanguage(), refCopy.getRegion())
{ }

Test::~Test()
{ }

QString &Test::getLanguage() const
{
    return(const_cast<Test &>(*this).msLanguage);
}

QString &Test::getRegion() const
{
    return(const_cast<Test &>(*this).msRegion);
}

void Test::setLanguage(const QString &sLanguage)
{
    msLanguage = sLanguage;
}

void Test::setRegion(const QString &sRegion)
{
    msRegion = sRegion;
}

Test &Test::operator=(const Test &refCopy)
{
    setLanguage(refCopy.getLanguage());
    setRegion(refCopy.getRegion());

    return(*this);
}

bool Test::operator==(const Test &refOther) const
{
    return  (getLanguage() == refOther.getLanguage())
            &&  (getRegion() == refOther.getRegion());
}

bool Test::operator!=(const Test &refOther) const
{
    return(!operator==(refOther));
}

Test::operator QString() const
{
    return(toString());
}

QString Test::toString() const
{
    return(getLanguage() + "(" + getRegion() + ")");
}

Q_DECLARE_METATYPE(Test);

class TestModel : public QAbstractListModel
{
    QList<Test> mLstModel;
public:
    TestModel();
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QList<Test> &getModel();
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
};


TestModel::TestModel()
    :   QAbstractListModel()
{
    mLstModel.append(Test("English", "EN"));
    mLstModel.append(Test("French", "FR"));
}

QVariant TestModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);

    qDebug() << index;

    if(index.isValid())
        {
       QVariant retVal;

        retVal.setValue(const_cast<TestModel &>(*this).getModel()[index.row()]);

        return(retVal);
        }
    else
        return(QVariant());
}

QList<Test> &TestModel::getModel()
{
    return(mLstModel);
}

int TestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    qDebug() << "There are " << const_cast<TestModel &>(*this).getModel().count() << " rows";

    return(const_cast<TestModel &>(*this).getModel().count());
 }

class TestMainWindow : public QMainWindow
{
    Q_OBJECT

    QComboBox *mCboTest;
protected:
    QComboBox *getTestComboBox();
    void initControls();
    void initWindow();
public:
    TestMainWindow(QWidget *parent=nullptr);
    ~TestMainWindow();
};

QComboBox *TestMainWindow::getTestComboBox()
{
    if(mCboTest == nullptr)
    {
        mCboTest = new QComboBox(this);

        mCboTest->setModel(new TestModel());
    }

    return(mCboTest);
}

void TestMainWindow::initControls()
{
    QLayout *layout = new QHBoxLayout(this);

    layout->addWidget(getTestComboBox());

    setLayout(layout);
}

void TestMainWindow::initWindow()
{
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    initControls();
}

TestMainWindow::TestMainWindow(QWidget *parent)
    :   QMainWindow(parent)
    ,   mCboTest(nullptr)
{
    initWindow();
}

TestMainWindow::~TestMainWindow()
{ }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMetaType::registerConverter(&Test::toString);

    TestMainWindow window;
    window.show();

    return a.exec();
}

#include "main.moc"
