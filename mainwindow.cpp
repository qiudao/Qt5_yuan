#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	QWidget *cwidget = new QWidget(this);
	QHBoxLayout *hlayout = new QHBoxLayout();
	m_client = new Client();	
	m_server = new Server();	
	hlayout->addWidget(m_client);
	hlayout->addWidget(m_server);
	cwidget->setLayout(hlayout);

	setCentralWidget(cwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
