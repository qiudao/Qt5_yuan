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
	m_client1 = new Client();	
	m_client2 = new Client();	
	m_server = new Server();	
	hlayout->addWidget(m_client1);
	hlayout->addWidget(m_client2);
	hlayout->addWidget(m_server);
	cwidget->setLayout(hlayout);

	m_client1->setStyleSheet("background-color:#C4F2C5;");
	m_client2->setStyleSheet("background-color:#C4F2C5;");
	m_server->setStyleSheet("background-color:#AED1F4;");

	// background
	cwidget->setAutoFillBackground(true);
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(QPixmap(":/images/setup-page-background.png")));
	cwidget->setPalette(palette);

	
	setCentralWidget(cwidget);
	resize(1050, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}
