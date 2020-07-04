#include "yuan.h"

Yuan::Yuan(QObject *parent)
{
	m_serverPeer = new QTcpSocket();
	connect(m_serverPeer, SIGNAL(connected()), this, SIGNAL(connected()));
	connect(m_serverPeer, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
	connect(this, SIGNAL(connected()), this, SLOT(OnServerConnected()));
	connect(this, SIGNAL(disconnected()), this, SLOT(OnServerDisconnected()));
}
Yuan::~Yuan()
{

}

QByteArray& data()
{
}

// start and Connect to peer
void Yuan::startAndDial(QString& server, quint16 port)
{
	start();
	Dial(server, port);
}
// connect or reconnect to peer
void Yuan::Dial(QString& server, quint16 port)
{
	m_server	= server;
	m_port		= port;

	if (m_serverPeer->state() == QAbstractSocket::ConnectedState)
	{
		m_serverPeer->disconnectFromHost();
	}
	m_serverPeer->connectToHost(m_server, m_port);
	qDebug() << "Dial to server: " << m_server << ", port " << m_port;

#if 0
	if (m_serverPeer->waitForConnected(5000)) {
		OnServerConnected();
	} else {
		OnServerDisconnected();
	}
#endif

}
void Yuan::ListenAndService(QString& server, quint16 port)
{
}
// disconnect
void Yuan::disconnectServer()
{
	m_serverPeer->disconnectFromHost();
}
// current connection state
int  Yuan::state()
{
	return YuanStateConnectOK;
}
// read from peer
int  Yuan::read(YuanS *buf, int n)
{
	return 0;
}
// write to peer
int  Yuan::write(YuanS *buf, int n)
{
	return 0;
}

// Slots
void Yuan::OnServerConnected()
{
	//qDebug() << "OnServerConnected: connected";
}
void Yuan::OnServerDisconnected()
{
	//qDebug() << "OnServerConnected: disconnected: " << m_serverPeer->errorString();
}
