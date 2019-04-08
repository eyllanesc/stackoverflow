#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QDirIterator>
#include <QFileInfo>
#include <QFuture>
#include <QObject>
#include <QQmlListProperty>
#include <QUrl>
#include <QVector>
#include <QtConcurrent>

class File : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString fileName READ fileName CONSTANT)
  Q_PROPERTY(QUrl url READ url CONSTANT)
public:
  File(const QString fullPath = "", QObject *parent = nullptr)
      : QObject(parent) {
    mFullPath = fullPath;
  }
  QString fileName() const { return QFileInfo(mFullPath).fileName(); }
  QUrl url() const { return QUrl::fromLocalFile(mFullPath); }

private:
  QString mFullPath;
};

class FileManager : public QObject {
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<File> files READ files NOTIFY filesChanged)
  Q_PROPERTY(QString folder READ folder WRITE setFolder NOTIFY folderChanged)
  Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters
                 NOTIFY nameFiltersChanged)
public:
  explicit FileManager(QObject *parent = nullptr) : QObject(parent) {}
  QQmlListProperty<File> files() {
    return QQmlListProperty<File>(this, this, &FileManager::filesCount,
                                  &FileManager::file);
  }

  QString folder() const { return mFolder; }

  void setFolder(const QString &folder) {
    if (mFolder == folder)
      return;
    mFolder = folder;
    emit folderChanged();
    findFiles();
  }

  int filesCount() const { return mFiles.count(); }

  File *file(int index) const { return mFiles.at(index); }
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
  void filesChanged();
  void nameFiltersChanged();

private:
  void findFiles() {
    mFiles.clear();
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

      for (const QString &fullName : future.result()) {
        File *file = new File(fullName);
        mFiles << file;
      }
    }
    emit filesChanged();
  }

  static int filesCount(QQmlListProperty<File> *list) {
    return reinterpret_cast<FileManager *>(list->data)->filesCount();
  }
  static File *file(QQmlListProperty<File> *list, int index) {
    return reinterpret_cast<FileManager *>(list->data)->file(index);
  }
  QVector<File *> mFiles;
  QString mFolder;
  QStringList mNameFilters;
};

#endif // FILEMANAGER_H
