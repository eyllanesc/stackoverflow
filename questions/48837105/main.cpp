#include <QApplication>
#include <QResizeEvent>
#include <QTextBrowser>

class TextBrowser : public QTextBrowser {
protected:
  void resizeEvent(QResizeEvent *event) {
    QTextBrowser::resizeEvent(event);
    // some criteria to obtain the new font size
    qreal size = 0.1 * event->size().width();
    QTextCursor cursor = textCursor();
    selectAll();
    setFontPointSize(size);
    setTextCursor(cursor);
  }
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TextBrowser w;
  w.append("Hello");
  w.show();

  return a.exec();
}
