#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include <QPrinter>
#include <QTextDocument>
#include <QTextEdit>

#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  int id = QFontDatabase::addApplicationFont(":/barcode.ttf");
  qDebug() << "font" << QFontDatabase::applicationFontFamilies(id)[0];
  QString serialNumber = "ABC123";
  QString messageBody;
  messageBody += "<p style='font-size: large;'><b>Serial Number:</b> " +
                 serialNumber + "</p>";
  messageBody += "<p style='font-size: large;'><b>Serial Number:</b>  <span "
                 "id=\"barcode\">" +
                 serialNumber + "</span></p>";

  QTextDocument document;
  QFile file(":/style.css");
  file.open(QFile::ReadOnly | QFile::Text);
  document.setDefaultStyleSheet(file.readAll());
  document.setHtml(messageBody);

  QPrinter printer(QPrinter::PrinterResolution);
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setOutputFileName("test.pdf");

  document.print(&printer);

  return 0;
}
