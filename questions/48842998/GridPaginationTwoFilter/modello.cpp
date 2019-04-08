#include "modello.h"

Tile::Tile(const QString &nomeRicetta, const QString &colore, const int &durata,
           const bool &ricettaUtente)
    : m_nomeRicetta(nomeRicetta), m_colore(colore), m_durata(durata),
      m_ricettaUtente(ricettaUtente) {}

QString Tile::nomeRicetta() const { return m_nomeRicetta; }

QString Tile::colore() const { return m_colore; }

int Tile::durata() const { return m_durata; }

bool Tile::ricettaUtente() const { return m_ricettaUtente; }

modello::modello(QObject *parent)
    : QAbstractListModel(parent), m_numIndicatori(1), m_totTile(1) {
  addRicetta("Aggiungi Ricetta", "grey", 1, true);
}

modello::~modello() {}

int modello::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return m_ricette.count();
}

QVariant modello::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= m_ricette.count())
    return QVariant();

  const Tile &tiletemp = m_ricette[index.row()];
  switch (role) {
  case NomeRicetta:
    return tiletemp.nomeRicetta();
    break;
  case Colore:
    return tiletemp.colore();
    break;
  case Durata:
    return tiletemp.durata();
    break;
  case RicettaUtente:
    return tiletemp.ricettaUtente();
    break;
  default:
    return QVariant();
    break;
  }
}

QHash<int, QByteArray> modello::roleNames() const {

  QHash<int, QByteArray> roles;
  roles[NomeRicetta] = "nomeRicetta";
  roles[Colore] = "colore";
  roles[Durata] = "durata";
  roles[RicettaUtente] = "ricettaUtente";
  return roles;
}

bool modello::removeRows(int row, int count, const QModelIndex &parent) {

  Q_UNUSED(parent);

  beginRemoveRows(parent, row, row + count - 1); // row row perchè ne elimino 1
  m_ricette.removeAt(row);
  endRemoveRows();

  QModelIndex top = createIndex(0, 0);
  QModelIndex bottom = createIndex(rowCount() - 1, 0);
  emit dataChanged(top, bottom);
  setnumIndicatori(rowCount()); // passo il totale degli elementi
  setTotTile(rowCount()); // aggiorno la property con il totale mi serve il suo
                          // emit x il qml
  return true;
}

void modello::addRicetta(QString nomeRic, QString color, int durata,
                         bool ricettaUtente) {
  Tile tileTmp(nomeRic, color, durata, ricettaUtente);

  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  if (rowCount() == 0)
    m_ricette << tileTmp;
  else
    m_ricette.insert(rowCount() - 1, tileTmp);
  endInsertRows();

  // mi serve per aggiornare in automatico il qml
  QModelIndex top = createIndex(0, 0);
  QModelIndex bottom = createIndex(rowCount() - 1, 0);
  emit dataChanged(top, bottom);
  setnumIndicatori(rowCount()); // passo il totale degli elementi
  setTotTile(rowCount()); // aggiorno la property con il totale mi serve il suo
                          // emit x il qml
}

qint16 modello::numIndicatori() const { return m_numIndicatori; }

qint16 modello::totTile() const { return m_totTile; }

void modello::setnumIndicatori(qint16 numIndicatori) {
  // divido x 6 perchè ho scelto di visualizzare 6 elemti alla volta
  if (numIndicatori % 6 == 0)
    m_numIndicatori = (numIndicatori / 6);
  else
    m_numIndicatori = (numIndicatori / 6) + 1;
  emit numIndicatoriChanged();
}

void modello::setTotTile(qint16 totTile) {

  if (m_totTile == totTile)
    return;

  m_totTile = totTile;
  emit totTileChanged();
}
