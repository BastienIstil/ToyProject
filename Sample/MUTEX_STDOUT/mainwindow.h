#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutexLocker>
#include <QMutex>
#include <QDebug>
#include <QTextEdit>

namespace Ui {
    class MainWindow;
}


class ThreadWorker : public QObject
{
        Q_OBJECT
    public:
        ThreadWorker(QMutex * mutex) : mutex(mutex)
        {
        }
    private:
        QMutex *mutex;

    signals:
        void finished();

    public slots:
        void doWork()
        {
            QMutexLocker(this->mutex);
            qDebug() << "Hello world from another thread";
            emit finished();
        }
};


class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    public slots:
        void SingleThreadTest();
        void MultiThreadTest();

    private:
        Ui::MainWindow *ui;
        QMutex stdoutMutex;
        static QTextEdit * ptrTextEdit;
};

#endif // MAINWINDOW_H
