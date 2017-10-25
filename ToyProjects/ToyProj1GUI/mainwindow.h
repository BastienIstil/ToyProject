#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "q_debugstream.h"
#include "../ToyProj1/Header.h"
namespace Ui {
class MainWindow;
}

class ThreadWorker : public QObject
{
    Q_OBJECT
public:
    ThreadWorker()
    {
    }
private:

signals:

    void finished();

public slots:
    void doWork()
    {
        run();
        emit finished();
    }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void SingleThreadTest();
    void MultiThreadTest();



private:
    Ui::MainWindow *ui;

      Q_DebugStream* m_qd;
};

#endif // MAINWINDOW_H
