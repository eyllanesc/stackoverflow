#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractListModel>
#include <QDirIterator>
#include <QFuture>
#include <QMetaType>
#include <QUrl>
#include <QtConcurrent>

struct File {
  Q_GADGET
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(QUrl url MEMBER url)
public:
  QString name;
  QUrl url;
  File(const QString &name = "") {
    this->name = QFileInfo(name).fileName();
    this->url = QUrl::fromLocalFile(name);
  }
};
Q_DECLARE_METATYPE(File)

class FileModel : public QAbstractListModel {
  enum dashBoardRoles { NameRole = Qt::UserRole + 1, URLRole };
  Q_OBJECT
  Q_PROPERTY(QString folder READ folder WRITE setFolder NOTIFY folderChanged)
  Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters
                 NOTIFY nameFiltersChanged)
public:
  FileModel(QObject *parent = Q_NULLPTR) : QAbstractListModel(parent) {}

  Q_INVOKABLE QVariant get(int index) {
    return QVariant::fromValue(m_all_dirs[index]);
  }

  int rowCount(const QModelIndex &parent = QModelIndex()) const {
    Q_UNUSED(parent)
    return m_all_dirs.count();
  }
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
    if (index.row() < 0 && index.row() >= rowCount())
      return QVariant();
    File file = m_all_dirs[index.row()];
    if (role == NameRole)
      return file.name;
    else if (role == URLRole)
      return file.url;
    return QVariant();
  }

  QHash<int, QByteArray> roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "fileName";
    roles[URLRole] = "url";
    return roles;
  }

  QString folder() const { return mFolder; }

  void setFolder(const QString &folder) {
    if (mFolder == folder)
      return;
    mFolder = folder;
    emit folderChanged();
    findFiles();
  }

  QStringList nameFilters() const { return mNameFilters; }

  void setNameFilters(const QStringList &nameFilters) {
    if (mNameFilters == nameFilters)
      return;
    mNameFilters = nameFilters;
    emit nameFiltersChanged();
    findFiles();
  }

signals:
  void folderChanged();
  void nameFiltersChanged();

private:
  void findFiles() {

    beginResetModel();
    m_all_dirs.clear();
    if (QDir(mFolder).exists()) {
      QFuture<QStringList> future = QtConcurrent::run([=]() {
        QStringList files;
        QDirIterator it(mFolder, mNameFilters, QDir::Files,
                        QDirIterator::Subdirectories);
        while (it.hasNext()) {
          files << it.next();
        }
        return files;
      });
      QStringList fullNames = future.result();
      for (const QString &fullName : fullNames) {
        File file{fullName};
        m_all_dirs << file;
      }
    }
    endResetModel();
  }
  QString mFolder;
  QList<File> m_all_dirs;
  QStringList mNameFilters;
};

#endif // FILEMODEL_H
