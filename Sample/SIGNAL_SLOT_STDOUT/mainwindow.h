#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTextEdit>

namespace Ui {
    class MainWindow;
}


class ThreadWorker : public QObject
{
        Q_OBJECT
    public:
        ThreadWorker()  {}
    private:

    signals:
        void finished();
        void sendMessage(QString msg);

    public slots:
        void doWork()
        {
            emit sendMessage("Hello world from another thread");
            emit finished();
        }
};

class MessageHandler : public QObject
{
    Q_OBJECT
    public :
        MessageHandler(QTextEdit *textEdit, QObject * parent = Q_NULLPTR) : QObject(parent), m_textEdit(textEdit){}

    public slots:
        void catchMessage(QString msg);

    private:
        QTextEdit * m_textEdit;
};

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    signals:
        void sendMessage(QString msg);

    public slots:
        void SingleThreadTest();
        void MultiThreadTest();

    private:
        Ui::MainWindow *ui;
        MessageHandler *msgHandler = Q_NULLPTR;
};

#endif // MAINWINDOW_H
