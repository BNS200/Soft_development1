#ifndef FILE_H
#define FILE_H
// #include <iostream>
#include <QString>
#include <QFileInfo>
#include <QDateTime>
#include <memory>


class File : public QObject
{

    Q_OBJECT;
public:
    explicit File(const QString& pathToFile, QObject* parent = nullptr);
    bool getStatus();
    qint64 getSize();
    QString getFilePath();
    void update();

private:
    size_t fileSize;
    QString fileName;
    QString pathToFile;
    bool exists;


    QDateTime modified;

    void check(bool existed, qint64 size);

signals:
    void fileCreated(const QString& fileName, qint64 size);
    void fileChanged(const QString& fileName,qint64 size);
    void fileDeleted(const QString& fileName);
    void fileNotExists(const QString& fileName);
    void fileExists(const QString& fileName, qint64 size);
};

//QFileInfo::size -> qint64

#endif // FILE_H
