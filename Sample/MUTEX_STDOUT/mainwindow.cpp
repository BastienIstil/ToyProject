#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

QTextEdit * MainWindow::ptrTextEdit = Q_NULLPTR;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ptrTextEdit = ui->textEdit;

    connect(ui->pushButtonSingleThreadTest, SIGNAL(clicked()),this,SLOT(SingleThreadTest()));
    connect(ui->pushButtonMultiThreadTest, SIGNAL(clicked()),this,SLOT(MultiThreadTest()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myMessageOutput(QtMsgType , const QMessageLogContext &, const QString &msg){
    ptrTextEdit->append(msg);
}

void MainWindow::SingleThreadTest()
{
    qDebug() <<  "Hello world from main thread";
}

void MainWindow::MultiThreadTest()
{
    QThread     *workerThread = new QThread;
    ThreadWorker *worker  = new ThreadWorker(&stdoutMutex);
    worker->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    workerThread->start();
}
