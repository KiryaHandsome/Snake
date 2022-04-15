#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <random>

const int block_size = 20;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), score(0)
{
    ui->setupUi(this);

    window = new Dialog;
    window->setWindowTitle("Ooops...");

    connect(window, SIGNAL(isExit()), this, SLOT(isExit_slot()));
    connect(window, SIGNAL(isPlay()), this, SLOT(isPlay_slot()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    startGame();
}

MainWindow::~MainWindow()
{
    int size = body.size();
    for(int i = 0; i < size; ++i){
        delete body[i];
    }
    delete window;
    delete food;
    delete ui;
}

void MainWindow::drawSnake()
{
    for(int i = body.size() - 1; i > 0; --i){
        body[i]->setGeometry(body[i - 1]->geometry());
    }
}

bool MainWindow::isLose()
{
    for(int i = 1; i < body.size(); ++i){
        if(body[i]->geometry() == body[0]->geometry()){
            return true;
        }
    }
    return false;
}

void MainWindow::startGame()
{
    QLabel* head = new QLabel(this);
    head->setStyleSheet("background-color:red");

    int x1 = (this->width() / 2) / block_size * block_size; //start coordinates
    int y1 = (this->height() / 2) / block_size * block_size;//of head

    head->setGeometry(x1, y1, block_size, block_size);
    head->show();
    body.push_back(head);

    srand(time(NULL));
    food = new QLabel(this);
    int food_x = (rand() % this->width()) / block_size * block_size;
    int food_y = (rand() % this->height()) / block_size * block_size;
    food->setGeometry(food_x, food_y, block_size, block_size);
    food->setStyleSheet("background-color:green");
    food->show();
}


void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(!timer->isActive()){
        timer->start(100);
    }
    if(event->key() == Qt::Key_Up){
        if(move_to != Down || score == 0){
            move_to = Up;
        }
    }
    if(event->key() == Qt::Key_Down){
        if(move_to != Up || score == 0){
            move_to = Down;
        }
    }
    if(event->key() == Qt::Key_Left){
        if(move_to != Right || score == 0){
            move_to = Left;
        }
    }
    if(event->key() == Qt::Key_Right){
        if(move_to != Left || score == 0){
            move_to = Right;
        }
    }
}



void MainWindow::move()
{
    int w = this->width(), h = this->height();
    int x = body[0]->x(), y = body[0]->y();
    if(move_to == Up){
        y -= block_size;
    }
    if(move_to == Down){
        y = (y + block_size) % h;
    }
    if(move_to == Left){
        x -= block_size;
    }
    if(move_to == Right){
        x = (x + block_size) % w;
    }
    if(x < 0){
        x = w - block_size;
    }
    if(y < 0){
        y = h - block_size;
    }
    drawSnake();
    body[0]->setGeometry(x, y, block_size, block_size);
    if(isLose()){
        timer->stop();
        window->setScore(score);
        window->show();
    }
    if(food->geometry().x() == x && food->geometry().y() == y){
        int new_x = (rand() % w) / block_size * block_size, new_y = (rand() % h) / block_size * block_size;
        food->setGeometry(new_x, new_y, block_size, block_size);
        QLabel* new_block = new QLabel(this);
        new_block->setStyleSheet("background-color:yellow");
        int tail_x = body[body.size() - 1]->x(), tail_y = body[body.size() - 1]->y();
        int x = 0, y = 0;
        if(move_to == Left){
            x = tail_x + block_size;
            y = tail_y;
        }
        if(move_to == Right){
            x = tail_x - block_size;
            y = tail_y;
        }
        if(move_to == Up){
            x = tail_x;
            y = tail_y + block_size;
        }
        if(move_to == Down){
            x = tail_x;
            y = tail_y - block_size;
        }
        new_block->setGeometry(x, y, block_size, block_size);
        new_block->show();
        body.push_back(new_block);
        ui->scoreLabel->setText(QString::number(++score));
    }
}

void MainWindow::isExit_slot()
{
    qApp->exit();
}

void MainWindow::isPlay_slot()
{
    window->close();
    score = 0;
    ui->scoreLabel->setText(QString::number(score));
    int size = body.size();
    for(int i = 0; i < size; ++i){
        delete body[i];
    }
    delete food;
    body.clear();
    startGame();
}


