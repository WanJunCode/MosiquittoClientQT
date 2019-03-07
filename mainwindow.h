#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mosquitto.h>
#include "mosquittop.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_linkButton_clicked();

private:
    bool activePublish() const;

private:
    Ui::MainWindow *ui;
    mosquittop *mqtt_;
    bool isConnect;
};

#endif // MAINWINDOW_H
