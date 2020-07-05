#include "yuan.h"

Yuan::Yuan(QObject *parent)
{
	m_serverPeer = new QTcpSocket();
	connect(m_serverPeer, SIGNAL(connected()), this, SIGNAL(connected()));
	connect(m_serverPeer, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
	connect(m_serverPeer, SIGNAL(readyRead()), this, SLOT(OnRead()));
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
		qDebug() << "Deisconnect from server: " << m_server << ", port " << m_port;
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
QByteArray intTo4ByteArray(int i)
{
	QByteArray ba;
	ba.resize(4);
	ba[0] = (uchar)(0x000000ff & i);
	ba[1] = (uchar)((0x0000ff00&i)>>8);
	ba[2] = (uchar)((0x00ff0000&i)>>16);
	ba[3] = (uchar)((0xff000000&i)>>24);
	return ba;
}

// read from peer
int  Yuan::read(YuanS *buf, int n)
{
	qDebug() << "Yuan read 1, left " << m_rlist.size();
	if (m_rlist.size() == 0)
		return -1;
	qDebug() << "Yuan read 2";
	YuanS first;
	first = m_rlist.first();
	buf->magic 	= first.magic;
	buf->id		= first.id;
	buf->length	= first.id;
	buf->payload.append(first.payload);
	qDebug() << "Yuan: read size  " << sizeof(first) << ", " << buf->payload;
	m_rlist.removeFirst();
	return 0;
}
// write to peer
int  Yuan::write(YuanS *buf, int n)
{
	YuanS last;
	last.magic	= buf->magic;
	last.id		= buf->id;
	last.length = buf->length;
	last.payload.append(buf->payload);
	m_wlist.append(last);

	if (m_wlist.size() > 0)
	{
		QByteArray out;
		out.append(intTo4ByteArray(m_wlist.last().magic));
		out.append(intTo4ByteArray(m_wlist.last().id));
		out.append(intTo4ByteArray(m_wlist.last().length));
		out.append(m_wlist.last().payload);
		m_serverPeer->write(out);
		qDebug() << "YUAN: write " << m_wlist.last().payload;
		m_wlist.removeLast();
	}
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

int ByteArray4ToInt(const QByteArray &bytes)
{
    int i = bytes[0] & 0x000000FF;
    i |= ((bytes[1] <<8)&0x0000FF00);
    i |= ((bytes[2] <<16)&0x00FF0000);
    i |= ((bytes[3] <<24)&0xFF000000);
    return i;
}
void Yuan::OnRead()
{
#define HEADLEN	12
	m_rbuf.append(m_serverPeer->readAll());
	if (m_rbuf.size() < 12)
		return;
	int len = ByteArray4ToInt(m_rbuf.mid(8,4));
	if (m_rbuf.size() < 12 + len)
		return;

	YuanS s;
	s.magic 	= ByteArray4ToInt(m_rbuf.left(4));
	s.id		= ByteArray4ToInt(m_rbuf.mid(4, 4));
	s.length	= ByteArray4ToInt(m_rbuf.mid(8, 4));
	s.payload.append(m_rbuf.mid(12, s.length));
	m_rlist.append(s);
	m_rbuf.remove(0, 12 + len);
	qDebug() << QString("Yuan: OnRead, magic %1, id %2, len %3, payload: ").arg(s.magic).arg(s.id).arg(s.length) << s.payload;

	emit readyRead();

}
