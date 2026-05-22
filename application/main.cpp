#include "mainwindow.h"

#include <QApplication>

// точка входа приложения - инициализирует главное окно

// главная функция приложения - создаёт и показывает главное окно
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
