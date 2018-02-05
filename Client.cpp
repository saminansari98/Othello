//
// Created by Samin on 1/28/18.
//


#include "Client.h"

Client::Client() {
    widgetFirst = new QWidget();
    layout = new QGridLayout();
    buttonPlay = new QPushButton();
    buttonPlay-> setText("Let's Play");
    buttonExite = new QPushButton();
    buttonExite-> setText("Exite");
    layout->addWidget(buttonPlay , 0 ,0);
    layout->addWidget(buttonExite , 2 , 2);
    widgetFirst ->setLayout(layout);



    widgetFirst-> show();

    connect(buttonPlay , &QPushButton::pressed , this , &Client::gameStarting);

}

void Client::gameStarting() {
    widgetFirst->close();
    widgetFirst = new QWidget();
    layout = new QGridLayout();
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);
    layout->setMargin(-10);
    widgetFirst->show();

    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            gameCell[i][j] = new QPushButton();
//            gameCell[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//            QPixmap pedram(BLACK_PIECE);
//            gameSquares[i][j]->setIcon(pedram);
//            gameSquares[i][j]->setIconSize(QSize(75, 75));
            layout->addWidget(gameCell[i][j], i*3 , j*50, 50 ,50 );
        }
    }


    widgetFirst->setLayout(layout);

}
