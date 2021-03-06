#include "client.h"
#include "ui_client.h"
#include <QVBoxLayout>
#include <QFormLayout>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);


	m_yuan = new Yuan();
	m_yuan->start();

	setupInfoBox();

	connect(m_yuan, SIGNAL(connected()), this, SLOT(OnConnectedServer()));
	connect(m_yuan, SIGNAL(disconnected()), this, SLOT(OnDisonnectedServer()));
	connect(m_yuan, SIGNAL(readyRead()), this, SLOT(OnRead()));

}

Client::~Client()
{
    delete ui;
}

void Client::setupInfoBox()
{
	/* create debug labels */
	QWidget *info = new QWidget(this);
	QVBoxLayout *vlayout =  new QVBoxLayout;
	m_lb_state	= new QLabel(this);
	m_le_server	= new QLineEdit(this);
	m_le_port	= new QLineEdit(this);
	m_btn_dial	= new QPushButton(tr("Dial"), this);
	m_btn_disconnect	= new QPushButton(tr("Disconnect"), this);
	m_btn_send	= new QPushButton(tr("Send"), this);
	m_editRead	= new QTextEdit(this);
	m_editWrite	= new QTextEdit(this);

	m_lb_state->setMinimumWidth(250);
	m_editRead->setMinimumWidth(250);
	m_editWrite->setMinimumWidth(250);

	// formLayout
	QFormLayout *formlayout = new QFormLayout;
	formlayout->addRow(tr("Status:"), m_lb_state);
	formlayout->addRow(tr("&Server:"), m_le_server);
	formlayout->addRow(tr("&Port:"), m_le_port);
	formlayout->addRow(tr("&Dial:"), m_btn_dial);
	formlayout->addRow(tr("&Disconnect:"), m_btn_disconnect);
	formlayout->addRow(tr("read:"), m_editRead);
	formlayout->addRow(tr("write:"), m_editWrite);
	formlayout->addRow(tr("&Send:"), m_btn_send);
	m_le_server->setMaximumWidth(100);
	m_le_port->setMaximumWidth(100);
	m_btn_dial->setMaximumWidth(100);
	m_btn_disconnect->setMaximumWidth(100);
	info->setLayout(formlayout);
	info->setWindowOpacity(0);
	//info->setStyleSheet("background-color: rgba(0,0,0,0)");
	

	m_le_server->setText("127.0.0.1");
	m_le_port->setText("5100");

	connect(m_btn_dial, SIGNAL(clicked()), this, SLOT(OnDial()));
	connect(m_btn_disconnect, SIGNAL(clicked()), this, SLOT(OnDisconnect()));
	connect(m_btn_send, SIGNAL(clicked()), this, SLOT(OnSend()));
}



// slots
void Client::OnConnectedServer()
{
	m_lb_state->setText("connected");
}
void Client::OnDisonnectedServer()
{
	m_lb_state->setText(m_yuan->errorString());
}
void Client::OnDial()
{
	QString server 	= m_le_server->text();
	quint16 port 	= m_le_port->text().toInt();
	m_yuan->Dial(server, port);
}
void Client::OnDisconnect()
{
	m_yuan->disconnectServer();
}
void Client::OnRead()
{
	YuanS r;
	m_yuan->read(&r, 0);

	qDebug() << "OnClientRead: " << r.payload;
	m_editRead->append(r.payload);
}
void Client::OnSend()
{
	qDebug() << "Send: " << m_editWrite->toPlainText();
	YuanS s;
	s.magic 	= 123;
	s.id 		= 456;
	s.length	= m_editWrite->toPlainText().size();
	s.payload.append(m_editWrite->toPlainText());
	m_yuan->write(&s, sizeof(s));
}
