#ifndef FILE_H
#define FILE_H
// #include <iostream>
#include <QString>
#include <QFileInfo>
#include <QDateTime>
#include <QObject>


class file : public QObject
{
public:
    file(QString& pathToFile, QObject* parent = nullptr);
    bool getStatus();
    size_t getSize();
    QString getFilePath();
    void update();



private:
    size_t fileSize;
    QString fileName;
    QString pathToFile;
    bool exists;


    QDateTime modified;

    void check(bool existed, size_t size);

signals:
    void fileCreated(const QString& fileName, size_t size);
    void fileChanged(const QString& fileName,size_t size);
    void fileDeleted(const QString& fileName);
    void fileNotExists(const QString& fileName);
    void fileExists(const QString& fileName, size_t size);





};

#endif // FILE_H
