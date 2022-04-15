#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum { Left, Right, Up, Down };

    void drawSnake();

    bool isLose();

    void startGame();


private slots:
    void keyPressEvent(QKeyEvent* e);

    void move();

    void isExit_slot();

    void isPlay_slot();


private:
    Ui::MainWindow *ui;
    Dialog* window;
    QVector<QLabel*> body;
    QLabel* food;
    int x_food, y_food; //coordinates of food
    QTimer* timer;
    short move_to;
    unsigned score;
};
#endif // MAINWINDOW_H
