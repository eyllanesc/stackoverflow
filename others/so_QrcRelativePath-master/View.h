#pragma once


#include <QMainWindow>

#include <QVBoxLayout>
#include <QWebEngineView>

#include <memory>

namespace Ui
{

class View
{
public:
    void setupUi(QMainWindow *aMainWindow)
    {
        aMainWindow->setFixedSize(520, 700);

        centralwidget = new QWidget(aMainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));

        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
    
        webview = new QWebEngineView();
        webview->setObjectName("webview");

        verticalLayout->addWidget(webview);

        aMainWindow->setCentralWidget(centralwidget);
    }

    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWebEngineView *webview;
};

} // namespace Ui

class View : public QMainWindow
{
    Q_OBJECT

public:
    View() :
            mUi(new Ui::View)
    {
        mUi->setupUi(this);
        mUi->webview->load(QUrl("qrc:/home.html"));
    }

    ~View()
    {}

private:
    std::unique_ptr<Ui::View> mUi;
};
