#include "file.h"

file::file(QString& filePath, QObject* parent)
    : QObject(parent), fileSize(0), fileName("unnamed"), pathToFile(filePath), exists(false)
{
    update();
}

QString file::getFilePath(){
    return pathToFile;
}

size_t file::getSize(){
    return fileSize;
}

bool file::getStatus(){
    return exists;
}

void file::update(){
    QFileInfo fileInfo(pathToFile);
    bool existed = exists;
    size_t wasSize = fileSize;

    exists = fileInfo.exists();

    if(existed){
        fileSize = fileInfo.size();
        modified = fileInfo.lastModified();
    } else {
        fileSize = 0;
    }

    check(existed, wasSize);
}

void file::check(bool existed, size_t size){
    if (!existed && exists){
        emit fileCreated(pathToFile, fileSize);
        emit fileExists(pathToFile, fileSize);
    }
    else if (existed && !exists){
        emit fileDeleted(pathToFile);
        emit fileNotExist(pathToFile);

    }
    else if (existed && exists){
        if (size != fileSize){
            emit fileChanged(pathToFile,fileSize);
            emit fileExists(pathToFile, fileSize);
        } else {
            emit fileExists(pathToFile, fileSize);
        }
    }
    else if (!existed && !exists){
        emit fileNotExists(fileSize);
    }


}
