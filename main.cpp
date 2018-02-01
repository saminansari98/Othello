#include <iostream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include "Client.h"

int main(int argc , char *argv[]) {
    QApplication app (argc , argv);

    Client *client = new Client();


    return app.exec();
}