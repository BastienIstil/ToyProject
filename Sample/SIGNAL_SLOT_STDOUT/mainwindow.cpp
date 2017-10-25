#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

void MessageHandler::catchMessage(QString msg){
    this->m_textEdit->append(msg);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->msgHandler = new MessageHandler(this->ui->textEdit, this);

    connect(this, &MainWindow::sendMessage, msgHandler, &MessageHandler::catchMessage);
    connect(ui->pushButtonSingleThreadTest, SIGNAL(clicked()),this,SLOT(SingleThreadTest()));
    connect(ui->pushButtonMultiThreadTest, SIGNAL(clicked()),this,SLOT(MultiThreadTest()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SingleThreadTest()
{
    emit sendMessage("Hello world from main thread");
}

void MainWindow::MultiThreadTest()
{
    QThread     *workerThread = new QThread;
    ThreadWorker *worker  = new ThreadWorker();
    worker->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, &ThreadWorker::sendMessage, this->msgHandler, &MessageHandler::catchMessage);
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    workerThread->start();
}
