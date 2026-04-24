#include "logger.h"



logger::logger(QObject* parent) : QObject(parent){

}
// Логирование изменения файла
void logger::logChanged(const QString& fileName, qint64 size){
    print(QString("File '%1' changed, size '%2'").arg(fileName).arg(formatSize(size)));
}
// Логирование удаления файла
void logger::logDeleted(const QString& fileName){
    print(QString("File '%1' deleted").arg(fileName));
}
//Логирование существования файла
void logger::logExists(const QString& fileName, qint64 size){
    print(QString("File '%1' exists, size '%2'").arg(fileName).arg(formatSize(size)));
}
// Логирование отсутствия файла
void logger::logNotExists(const QString& fileName){
    print(QString("File '%1' not exists").arg(fileName));
}

void logger::logCreated(const QString& fileName, qint64 size){
    print(QString("File '%1' created, size '%2'").arg(fileName).arg(formatSize(size)));

}
// Вывод сообщения в консоль
void logger::print(const QString& message){
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    qDebug() << time << " - " << message;
}


// Форматирование вывода
QString logger::formatSize(qint64 size){
    if (size < 1024){
        return QString::number(size) + "B";
    }

    if (size < 1024 * 1024){
        return QString::number(size / 1024, 'f', 2) + "KB";
    }

    if (size < 1024 * 1024 * 1024){
        return QString::number(size / (1024 * 1024), 'f', 2) + "MB";
    }
    return QString::number(size / (1024 * 1024 * 1024), 'f', 2) + "GB";
}
