#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void setScore(int score_value);

private slots:
    void playButton_clicked();

    void exitButton_clicked();

signals:
    void isExit();
    void isPlay();


private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
