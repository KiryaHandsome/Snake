#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    this->setWindowTitle("Ooops");
    ui->setupUi(this);
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(exitButton_clicked()));
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(playButton_clicked()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setScore(int score_value)
{
    ui->scoreLabel->setText(QString::number(score_value));
}

void Dialog::playButton_clicked()
{
    emit isPlay();
}

void Dialog::exitButton_clicked()
{
    emit isExit();
}
