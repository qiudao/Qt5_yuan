#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

	setupInfoBox();

	m_serverThread = new ServerThread();
	m_serverThread->start();
	connect(m_serverThread, SIGNAL(client1Connected(bool)), this, SLOT(OnClient1Connected(bool)));
	connect(m_serverThread, SIGNAL(client2Connected(bool)), this, SLOT(OnClient2Connected(bool)));
}

Server::~Server()
{
    delete ui;
}

void Server::setupInfoBox()
{
	/* create debug labels */
	QWidget *info = new QWidget(this);
	QVBoxLayout *vlayout =  new QVBoxLayout;
	m_lb_state1	= new QLabel(this);
	m_lb_state2	= new QLabel(this);
	m_le_server	= new QLineEdit(this);
	m_le_port	= new QLineEdit(this);

	m_lb_state1->setMinimumWidth(250);
	m_lb_state2->setMinimumWidth(250);

	// formLayout
	QFormLayout *formlayout = new QFormLayout;
	formlayout->addRow(tr("Client1:"), m_lb_state1);
	formlayout->addRow(tr("Client2:"), m_lb_state2);
	formlayout->addRow(tr("&Server:"), m_le_server);
	formlayout->addRow(tr("&Port:"), m_le_port);
	m_le_server->setMaximumWidth(100);
	m_le_port->setMaximumWidth(100);
	info->setLayout(formlayout);
	info->setWindowOpacity(0);

	m_le_server->setText("127.0.0.1");
	m_le_port->setText("5100");
	m_le_server->setEnabled(false);
	m_le_port->setEnabled(false);

	connect(m_le_server, SIGNAL(editingFinished()), this, SLOT(OnParaChanged()));
	connect(m_le_port, SIGNAL(editingFinished()), this, SLOT(OnParaChanged()));
}

void Server::OnParaChanged()
{
}

void Server::OnClient1Connected(bool on)
{
	if (on)
		m_lb_state1->setText("connected");
	else
		m_lb_state1->setText("disconnected");
}
void Server::OnClient2Connected(bool on)
{
	if (on)
		m_lb_state2->setText("connected");
	else
		m_lb_state2->setText("disconnected");
}


ServerThread::ServerThread(QObject *parent)
{
	m_tcpServer = new QTcpServer();
	m_tcpServer->listen(QHostAddress::Any, 5100);
	if (m_tcpServer->isListening())
		qDebug() << "server Listening ok";
	else
		qDebug() << "server Listening fail";

	m_client1 = NULL;
	m_client2 = NULL;

	connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));
}
ServerThread::~ServerThread()
{
}

void ServerThread::OnNewConnection()
{

	qDebug() << "OnNewConnection:";

	if (!m_client1 || 
				(m_client1->state() != QTcpSocket::ConnectedState) )
	{
		qDebug() << "client1 is not in connection";
		m_client1 = m_tcpServer->nextPendingConnection();
		if (m_client1->state() == QTcpSocket::ConnectedState)
		{
			qDebug() << "New connection established.";
			emit client1Connected(true);

		}
		connect(m_client1, SIGNAL(disconnected()), this, SLOT(On1Disconnected()));
		connect(m_client1, SIGNAL(readyRead()), this, SLOT(On1ReadyRead()));
		return;

	}
	if (!m_client2 ||
			(m_client2->state() == QTcpSocket::ConnectedState) )
	{
		qDebug() << "client2 is not in connection";
		m_client2 = m_tcpServer->nextPendingConnection();
		if (m_client2->state() == QTcpSocket::ConnectedState)
		{
			qDebug() << "New connection established.";
			emit client2Connected(true);
		}
		connect(m_client2, SIGNAL(disconnected()), this, SLOT(On2Disconnected()));
		connect(m_client2, SIGNAL(readyRead()), this, SLOT(On2ReadyRead()));
		return;
	}
}

void ServerThread::On1Disconnected()
{
	qDebug() << "On1Disconnected";
	m_client1->deleteLater();
	m_client1 = NULL;
	emit client1Connected(false);
}
void ServerThread::On1ReadyRead()
{
	QByteArray data = m_client1->readAll();
	m_client2->write(data);
	qDebug() << "On1ReadyRead, size " << data.size() <<", : " << data;
}
void ServerThread::On2Disconnected()
{
	qDebug() << "On2Disconnected";
	m_client2->deleteLater();
	m_client2 = NULL;
	emit client2Connected(false);
}
void ServerThread::On2ReadyRead()
{
	qDebug() << "On2ReadyRead";
	QByteArray data = m_client2->readAll();
	m_client1->write(data);
}
