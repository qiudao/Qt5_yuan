#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
	m_yuan = new Yuan();
	m_yuan->start();

	setupInfoBox();
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
	m_lb_state	= new QLabel(this);
	m_le_server	= new QLineEdit(this);
	m_le_port	= new QLineEdit(this);

	m_lb_state->setMinimumWidth(250);

	// formLayout
	QFormLayout *formlayout = new QFormLayout;
	formlayout->addRow(tr("Status:"), m_lb_state);
	formlayout->addRow(tr("&Server:"), m_le_server);
	formlayout->addRow(tr("&Port:"), m_le_port);
	m_le_server->setMaximumWidth(100);
	m_le_port->setMaximumWidth(100);
	info->setLayout(formlayout);
	info->setWindowOpacity(0);
	info->setStyleSheet("background-color: rgba(0,0,0,0)");

	connect(m_le_server, SIGNAL(editingFinished()), this, SLOT(OnParaChanged()));
	connect(m_le_port, SIGNAL(editingFinished()), this, SLOT(OnParaChanged()));
}



// slots
void Server::OnConnectedServer()
{
	m_lb_state->setText("connected");
}
void Server::OnDisonnectedServer()
{
	m_lb_state->setText("disconnected");
}
void Server::OnParaChanged()
{
	QString server 	= m_le_server->text();
	quint16 port 	= m_le_port->text().toInt();
	m_yuan->ListenAndService(server, port);
}
