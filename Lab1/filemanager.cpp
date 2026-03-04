#include "filemanager.h"

fileManager::fileManager(QObject* parent) : QObject(parent){
    log = new logger(this);

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &fileManager::updateFiles);
    timer->start(100);
}

fileManager& fileManager::Instance(){
    static fileManager f;
    return f;
}

void fileManager::updateFiles(){
    for (auto& file : files){
        file->update();
    }
}

fileManager::~fileManager(){
    timer->stop();
}

void fileManager::addFile(const QString& filePath){
    std::shared_ptr<File> file = std::make_shared<File>(QString(filePath));
    setConnection(file);
    files.append(file);
}

void fileManager::removeFile(const QString& filePath){
    for (int i = 0; i < files.size(); ++i){
        if (files[i]->getFilePath() == filePath){
            files.removeAt(i);
            break;
        }
    }
}

void fileManager::setConnection(std::shared_ptr<File> file){
    connect(file.get(), &File::fileCreated, log, &logger::logCreated);
    connect(file.get(), &File::fileDeleted, log, &logger::logDeleted);
    connect(file.get(), &File::fileExists, log, &logger::logExists);
    connect(file.get(), &File::fileNotExists, log, &logger::logNotExists);
    connect(file.get(), &File::fileChanged, log, &logger::logChanged);
}
