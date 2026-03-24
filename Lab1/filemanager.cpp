#include "filemanager.h"

// Конструктор (приватный для Singleton)
fileManager::fileManager(QObject* parent) : QObject(parent), log(nullptr)
{

}

fileManager& fileManager::Instance()
{
    static fileManager instance;
    return instance;
}

fileManager::~fileManager()
{

}

// Установка логгера и подключение сигналов
void fileManager::setLogger(logger* logValue){
    log = logValue;

    if (log) {
        // Подключение всех сигналов к соответствующим слотам логгера
        connect(this, &fileManager::fileCreated, log, &logger::logCreated);
        connect(this, &fileManager::fileChanged, log, &logger::logChanged);
        connect(this, &fileManager::fileDeleted, log, &logger::logDeleted);
        connect(this, &fileManager::fileExists, log, &logger::logExists);
        connect(this, &fileManager::fileNotExists, log, &logger::logNotExists);
    } else {
        qDebug() << "Logger is null";
        return;
    }
}

// Добавление файла в список отслеживания
void fileManager::addFile(const QString& filePath)
{

    // Проверка на пустой путь
    if (filePath.isEmpty()) {
        qDebug() << "Warning: Attempted to add file with empty path, ignored";
        return;
    }

    // Проверка на наличие файла в списке отслеживаемых
    for (int i = 0; i < files.size(); ++i) {
        if (files[i].filePath() == filePath) {
            return;
        }
    }
    files.append(QFileInfo(filePath));
}


// Удаление файла из списка отслеживания
void fileManager::removeFile(const QString& filePath)
{
    for (int i = 0; i < files.size(); ++i) {
        if (files[i].filePath() == filePath) {
            files.removeAt(i);
            break;
        }
    }
}
//Проверка состояния файлов
void fileManager::updateFiles()
{

    if (!log)
        return;
    for (int i = 0; i < files.size(); ++i) {
        QFileInfo oldInfo = files[i];// Сохранение сотсояния файла
        bool oldExists = oldInfo.exists(); //Проверка существования до проверки
        QString filePath = oldInfo.filePath(); // Сохранение пути
        QFileInfo newInfo(filePath);// Тукущее сотсояние файла


        bool newExists = newInfo.exists(); //Проверка существования на данный момент


        // Анализ файла
        if (!oldExists && newExists) // Файл был создан
        {
            files[i] = newInfo;
            emit fileCreated(filePath, newInfo.size());
            emit fileExists(filePath, newInfo.size());
        }
        else if (oldExists && !newExists) // Файл был удален
        {
            files[i] = newInfo;
            emit fileDeleted(filePath);
            emit fileNotExists(filePath);
        }
        else if (oldExists && newExists) // Файл существует
        {
            if (oldInfo.size() != newInfo.size() || oldInfo.lastModified() != newInfo.lastModified()) // Поверяем на изменения
            {
                files[i] = newInfo;
                emit fileChanged(filePath, newInfo.size());
            }
            emit fileExists(filePath, newInfo.size());
        }
        else if (!oldExists && !newExists) // Файл не существует и раньше не существовал
        {
            files[i] = newInfo;
            emit fileNotExists(filePath);
        }
    }
}
