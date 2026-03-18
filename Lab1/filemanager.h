#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QFileInfo>
#include <QList>
#include <QTimer>
#include "logger.h"

class fileManager : public QObject
{
    Q_OBJECT

public:
    static fileManager& Instance();
    ~fileManager();

    void addFile(const QString& filePath);
    void removeFile(const QString& filePath);


    void setLogger(logger* log);
private:
    fileManager(QObject* parent = nullptr);
    fileManager(const fileManager&) = delete;
    fileManager& operator=(const fileManager&) = delete;



    QList<QFileInfo> files;
    logger* log;

signals:
    void fileCreated(const QString& fileName, qint64 size);
    void fileChanged(const QString& fileName, qint64 size);
    void fileDeleted(const QString& fileName);
    void fileExists(const QString& fileName, qint64 size);
    void fileNotExists(const QString& fileName);

public slots:
    void updateFiles();
};

#endif // FILEMANAGER_H
