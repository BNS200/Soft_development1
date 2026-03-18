#include "filemanager.h"

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

void fileManager::setLogger(logger* logValue){
    log = logValue;

    if (log) {
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


void fileManager::addFile(const QString& filePath)
{

    for (int i = 0; i < files.size(); ++i) {
        if (files[i].filePath() == filePath) {
            return;
        }
    }
    files.append(QFileInfo(filePath));
}

void fileManager::removeFile(const QString& filePath)
{
    for (int i = 0; i < files.size(); ++i) {
        if (files[i].filePath() == filePath) {
            files.removeAt(i);
            break;
        }
    }
}

void fileManager::updateFiles()
{

    if (!log)
        return;
    for (int i = 0; i < files.size(); ++i) {
        QFileInfo oldInfo = files[i];
        QString filePath = oldInfo.filePath();
        QFileInfo newInfo(filePath);

        bool oldExists = oldInfo.exists();
        bool newExists = newInfo.exists();

        if (!oldExists && newExists) {
            files[i] = newInfo;
            emit fileCreated(filePath, newInfo.size());
            emit fileExists(filePath, newInfo.size());
        }
        else if (oldExists && !newExists) {
            files[i] = newInfo;
            emit fileDeleted(filePath);
            emit fileNotExists(filePath);
        }
        else if (oldExists && newExists) {
            if (oldInfo.size() != newInfo.size() || oldInfo.lastModified() != newInfo.lastModified()) {
                files[i] = newInfo;
                emit fileChanged(filePath, newInfo.size());
            }
            emit fileExists(filePath, newInfo.size());
        }
        else if (!oldExists && !newExists) {
            emit fileNotExists(filePath);
        }
    }
}
