#ifndef FILTRO_H
#define FILTRO_H
#include <QSortFilterProxyModel>

class Filtro : public QSortFilterProxyModel {
  Q_OBJECT
  Q_PROPERTY(bool showOnlyUserRic READ showOnlyUserRic WRITE setshowOnlyUserRic
                 NOTIFY showOnlyUserRicChanged)
  Q_PROPERTY(QString string READ string WRITE setstring NOTIFY stringChanged)

public:
  Filtro(QObject *parent = 0);
  ~Filtro();

  Q_INVOKABLE void setStringaFiltro(QString string);

public slots:
  void setshowOnlyUserRic(bool showOnlyUserRic);
  bool showOnlyUserRic() const;

  QString string() const;
  void setstring(QString string);

signals:
  void showOnlyUserRicChanged();
  void oggettiFiltChanged();

  void stringChanged();

private:
  bool m_showOnlyUserRic;
  int m_oggettiFilt;

  QString m_string;

protected:
  bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
  // QSortFilterProxyModel interface
  bool lessThan(const QModelIndex &source_left,
                const QModelIndex &source_right) const;
};

#endif // FILTRO_H
