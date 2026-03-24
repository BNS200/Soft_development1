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

    // Singleton: получение единственного экземпляра
    static fileManager& Instance();
    ~fileManager();


    // Управление списком отслеживаемых файлов
    void addFile(const QString& filePath);
    void removeFile(const QString& filePath);


    // Установка логгера для обработки событий
    void setLogger(logger* log);
private:
     // Приватный конструктор для Singleton
    fileManager(QObject* parent = nullptr);

    // Запрет копирования и присваивания(Singleton)
    fileManager(const fileManager&) = delete;
    fileManager& operator=(const fileManager&) = delete;



    QList<QFileInfo> files;// Список отслеживаемых файлов
    logger* log;// Указатель на логгер

signals:
    // Сигналы для уведомления о событиях
    void fileCreated(const QString& fileName, qint64 size);
    void fileChanged(const QString& fileName, qint64 size);
    void fileDeleted(const QString& fileName);
    void fileExists(const QString& fileName, qint64 size);
    void fileNotExists(const QString& fileName);

public slots:
    void updateFiles(); // Слот для обновления состояния файло
};

#endif // FILEMANAGER_H
