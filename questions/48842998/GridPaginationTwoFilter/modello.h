#ifndef MODELLO_H
#define MODELLO_H

#include <QAbstractItemModel>
#include <QObject>
#include <QSortFilterProxyModel>

class Tile {
public:
  Tile(const QString &nomeRicetta, const QString &colore, const int &durata,
       const bool &ricettaUtente);
  QString nomeRicetta() const;
  QString colore() const;
  int durata() const;
  bool ricettaUtente() const;

private:
  QString m_nomeRicetta;
  QString m_colore;
  int m_durata;
  bool m_ricettaUtente;
};

class modello : public QAbstractListModel {
  Q_OBJECT
public:
  explicit modello(QObject *parent = 0);

  ~modello();
  Q_PROPERTY(qint16 numIndicatori READ numIndicatori WRITE setnumIndicatori
                 NOTIFY numIndicatoriChanged)
  Q_PROPERTY(qint16 totTile READ totTile WRITE setTotTile NOTIFY
                 totTileChanged) // property x fare in modo che solo l'ultima
                                 // tile sia cliccabile

  enum TileRoles {

    NomeRicetta = Qt::UserRole + 1,
    Colore,
    Durata,
    RicettaUtente
  };

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  QHash<int, QByteArray> roleNames() const;
  Q_INVOKABLE bool
  removeRows(int row, int count,
             const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
  Q_INVOKABLE void addRicetta(QString nomeRic, QString color, int durata,
                              bool ricettaUtente);

  qint16 numIndicatori() const;
  qint16 totTile() const;

public slots:
  void setnumIndicatori(qint16 numIndicatori);
  void setTotTile(qint16 totTile);

signals:
  void numIndicatoriChanged();
  void totTileChanged();

private:
  QList<Tile> m_ricette;
  qint16 m_numIndicatori;
  qint16 m_totTile;
};

#endif // MODELLO_H
