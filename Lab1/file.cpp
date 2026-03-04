#include "file.h"

File::File(const QString& filePath, QObject* parent)
    : QObject(parent), fileSize(0), fileName("unnamed"), pathToFile(filePath), exists(false)
{
    update();
}

QString File::getFilePath(){
    return pathToFile;
}

qint64 File::getSize(){
    return fileSize;
}

bool File::getStatus(){
    return exists;
}

void File::update(){
    QFileInfo fileInfo(pathToFile);
    bool existed = exists;
    qint64 wasSize = fileSize;

    exists = fileInfo.exists();

    if(existed){
        fileSize = fileInfo.size();
        modified = fileInfo.lastModified();
    } else {
        fileSize = 0;
    }

    check(existed, wasSize);
}

void File::check(bool existed, qint64 size){
    if (!existed && exists){
        emit fileCreated(pathToFile, fileSize);
        emit fileExists(pathToFile, fileSize);
    }
    else if (existed && !exists){
        emit fileDeleted(pathToFile);
        emit fileNotExists(pathToFile);

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
        emit fileNotExists(pathToFile);
    }
}
