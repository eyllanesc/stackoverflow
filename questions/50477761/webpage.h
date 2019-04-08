#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QIcon>
#include <QWebEngineFullScreenRequest>
#include <QWebEngineView>
class QTabWidget;
class MainWindow;

class WebPage : public QWebEngineView {
  Q_OBJECT
public:
  WebPage(QTabWidget *parent);
public slots:
  void changeTitle(const QString &title);
  void changeIcon(QIcon icon);
  void changeUrl(QUrl url);
  void setFullScreen(QWebEngineFullScreenRequest request);

private:
  QTabWidget *tabs;
  MainWindow *mainWindow;
};

#endif // WEBPAGE_H
