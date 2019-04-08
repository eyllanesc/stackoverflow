#include "filtro.h"
#include "modello.h"
#include <QDebug>

Filtro::Filtro(QObject *parent)
    : QSortFilterProxyModel(parent), m_showOnlyUserRic(false), m_oggettiFilt(0),
      m_string("") {
  setFilterRole(modello::RicettaUtente);
  setSortRole(modello::NomeRicetta);
  setDynamicSortFilter(true);
  sort(0);
}

Filtro::~Filtro() {}

void Filtro::setStringaFiltro(QString string) {
  this->setFilterCaseSensitivity(
      Qt::CaseInsensitive); // lo rendo case insensitive
  this->setFilterFixedString(string);
}

QString Filtro::string() const { return m_string; }

void Filtro::setstring(QString string) {
  if (m_string == string)
    return;

  m_string = string;
  emit stringChanged();
  invalidateFilter(); // fa rivalutare il filtro e quindi entra di nuovo in
                      // filterAcceptsRows()
}

bool Filtro::showOnlyUserRic() const { return m_showOnlyUserRic; }

void Filtro::setshowOnlyUserRic(bool showOnlyUserRic) {
  if (m_showOnlyUserRic == showOnlyUserRic)
    return;

  m_showOnlyUserRic = showOnlyUserRic;
  emit showOnlyUserRicChanged();

  invalidateFilter(); // fa rivalutare il filtro e quindi entra di nuovo in
                      // filterAcceptsRows()
}

bool Filtro::filterAcceptsRow(int source_row,
                              const QModelIndex &source_parent) const {
  QRegExp regEx("*" + string() + "*");
  regEx.setPatternSyntax(QRegExp::Wildcard);
  regEx.setCaseSensitivity(Qt::CaseInsensitive);

  if (showOnlyUserRic() == true) {
    // se devo visualizzare solo
    QModelIndex ricUtente = sourceModel()->index(
        source_row, 0,
        source_parent); // vado a leggere singolarmente ogni riga del modello
    QString stringaConfronto =
        sourceModel()->data(ricUtente, modello::NomeRicetta).toString();

    if (sourceModel()->data(ricUtente, modello::RicettaUtente) == true &&
        stringaConfronto.contains(regEx) == true) {
      // se è ricetta utente
      return true;
    } else {

      return false;
    }

  } else {

    QModelIndex ricUtente = sourceModel()->index(
        source_row, 0,
        source_parent); // vado a leggere singolarmente ogni riga del modello
    QString stringaConfronto =
        sourceModel()->data(ricUtente, modello::NomeRicetta).toString();
    if (stringaConfronto.contains(regEx))
      return true;
    //        if(sourceModel()->data(ricUtente,modello::NomeRicetta)== string()
    //        )  //confronto il roles ricetta utene x filtrare il
    //        {
    //            return true;
    //        }
    return false;
  }
}

bool Filtro::lessThan(const QModelIndex &source_left,
                      const QModelIndex &source_right) const {
  bool leftData = sourceModel()
                      ->data(source_left, modello::RicettaUtente)
                      .toBool(); // vado a leggere il valore RicettaUtente e lo
                                 // trasformo in bool
  bool rightData = sourceModel()
                       ->data(source_right, modello::RicettaUtente)
                       .toBool(); // vado a leggere il valore RicettaUtente e lo
                                  // trasformo in bool

  if (leftData != rightData)
    return leftData;
  else
    return QSortFilterProxyModel::lessThan(source_left, source_right);
}
