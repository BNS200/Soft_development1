#include "filemanager.h"

// Конструктор (приватный для Singleton)
fileManager::fileManager(QObject* parent) : QObject(parent), log(nullptr), isFirstCheck(true)
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
        if (files[i].fileInfo.filePath() == filePath) {
            return;
        }
    }
    TrackedFile newFile;
    newFile.fileInfo = QFileInfo(filePath);
    newFile.exists = newFile.fileInfo.exists();
    files.append(newFile);

}


// Удаление файла из списка отслеживания
void fileManager::removeFile(const QString& filePath)
{
    for (int i = 0; i < files.size(); ++i) {
        if (files[i].fileInfo.filePath() == filePath) {
            files.removeAt(i);
            break;
        }
    }
}
// Проверка состояния файлов
void fileManager::updateFiles()
{
    if (!log)
        return;

    for (int i = 0; i < files.size(); ++i) {
        QFileInfo oldInfo = files[i].fileInfo;
        QString filePath = oldInfo.filePath();
        QFileInfo newInfo(filePath);

        bool oldExists = files[i].exists;
        bool newExists = newInfo.exists();

        // При первой проверке выводим начальное состояние
        if (isFirstCheck) {
            if (newExists) {
                emit fileExists(filePath, newInfo.size());
            } else {
                emit fileNotExists(filePath);
            }
            files[i].fileInfo = newInfo;
            files[i].exists = newExists;
        }

        // Анализ файла - сообщения ТОЛЬКО при реальных изменениях
        if (!oldExists && newExists) // Файл был создан
        {
            files[i].fileInfo = newInfo;
            files[i].exists = true;
            emit fileCreated(filePath, newInfo.size());
        }
        else if (oldExists && !newExists) // Файл был удален
        {
            files[i].fileInfo = newInfo;
            files[i].exists = false;
            emit fileDeleted(filePath);
        }
        else if (oldExists && newExists) // Файл изменен
        {

            if (oldInfo.size() != newInfo.size() ||
                oldInfo.lastModified() != newInfo.lastModified())
            {
                files[i].fileInfo = newInfo;
                emit fileChanged(filePath, newInfo.size());
            }
        }
    }

    // После первой проверки сбрасываем флаг
    if (isFirstCheck) {
        isFirstCheck = false;
    }
}
