#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "file.h"
#include "logger.h"
#include <QList>
#include <memory>
#include <QTimer>



class fileManager : public QObject
{
    Q_OBJECT;
public:
    static fileManager& Instance();

    void addFile(const QString& filePath);
    void removeFile(const QString& filePath);

    ~fileManager();
    void setConnection(std::shared_ptr<File> file);
private:
    QList<std::shared_ptr<File>> files;
    logger* log;
    QTimer* timer;
    fileManager(QObject* parent = nullptr);

private slots:
    void updateFiles();
};

#endif // FILEMANAGER_H
