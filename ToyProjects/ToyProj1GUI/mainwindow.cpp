#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QThread>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);

    m_qd = new Q_DebugStream(std::cout,ui->textEdit); //Redirect Console output to QTextEdit
    m_qd->Q_DebugStream::registerQDebugMessageHandler(); //Redirect qDebug() output to QTextEdit

    connect(ui->pushButtonSingleThreadTest, SIGNAL(clicked()),this,SLOT(SingleThreadTest()));
    connect(ui->pushButtonMultiThreadTest, SIGNAL(clicked()),this,SLOT(MultiThreadTest()));


}

void MainWindow::SingleThreadTest()
{
    run();
}

void MainWindow::MultiThreadTest()
{
    QThread     *workerThread= new QThread;
    ThreadWorker *worker  = new ThreadWorker();
    worker->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    workerThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
