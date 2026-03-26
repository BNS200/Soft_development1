#include <QCoreApplication>
#include "filemanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    // Получение единственного экземпляра менеджера файлов
    fileManager& manager = fileManager::Instance();

    // Создание логгера с привязкой к объекту приложения
    logger* log = new logger(&a);

    // Установка логгера для менеджера файлов
    manager.setLogger(log);

    // Создание таймера для периодической проверки
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &manager, &fileManager::updateFiles);
    timer.start(1000); // Проверка каждые 100 мс



    manager.addFile("/Users/nikitabufalov/work2/Soft_development/Lab1/file1.txt");
    manager.addFile("/Users/nikitabufalov/work2/Soft_development/Lab1/file2.txt");
    // manager.addFile("/Users/nikitabufalov/work2/Soft_development/Lab1/file3.txt");


    return a.exec();// Запуск цикла обработки событий
}
