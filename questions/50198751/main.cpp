#include <QApplication>
#include <QPrintDialog>
#include <QPrinter>
#include <QPushButton>
#include <QSqlTableModel>
#include <QTableView>
#include <QTextDocument>
#include <QVBoxLayout>

#include "connection.h"
#include "transposeproxymodel.h"

#include <QDebug>

static void print_tableview(QTableView *view) {
  const QString format("<td>%1</td>");
  QString html;
  QAbstractItemModel *md = view->model();
  html = "<html><body><table border=\"0\">";

  html += "<td></td>";
  for (int column = 0; column < md->columnCount(); column++) {
    QString data =
        md->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
    html += format.arg(data);
  }
  for (int row = 0; row < md->rowCount(); row++) {
    html += "<tr>";
    QString data =
        md->headerData(row, Qt::Vertical, Qt::DisplayRole).toString();
    html += format.arg(data);
    for (int column = 0; column < md->columnCount(); column++) {
      QString data = md->index(row, column).data(Qt::DisplayRole).toString();
      html += format.arg(data);
    }
    html += "</tr>";
  }
  html += "</table></body></html>";

  QPrinter printer;
  QPrintDialog *dialog = new QPrintDialog(&printer);
  if (dialog->exec() == QDialog::Accepted) {
    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);
  }
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  if (!createConnection())
    return -1;

  QSqlTableModel model;
  model.setTable("person");
  model.select();

  TransposeProxyModel proxy;
  proxy.setSourceModel(&model);

  QWidget w;
  QVBoxLayout lay(&w);
  QTableView view;
  view.setModel(&proxy);
  QPushButton btn("Print TableView");
  QObject::connect(&btn, &QPushButton::clicked,
                   std::bind(print_tableview, &view));

  lay.addWidget(&btn);
  lay.addWidget(&view);
  w.show();

  return a.exec();
}
