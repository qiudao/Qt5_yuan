#ifndef YUAN_H
#define YUAN_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

#define YuanStateConnectOK				0
#define YuanStateConnectFailed			1

typedef struct {
	quint32		magic;
	quint32		id;
	quint32		length;
	QByteArray 	payload;
}YuanS;

class Yuan : public QThread
{
    Q_OBJECT

public:
    Yuan(QObject *parent=nullptr);
    ~Yuan();

	void startAndDial(QString& server, quint16 port);
	void Dial(QString& server, quint16 port);
	void ListenAndService(QString& server, quint16 port);
	void disconnectServer();
	int  state();
	int  read(YuanS *buf, int n);
	int  write(YuanS *buf, int n);

	// state
	QString& errorString() {m_serverError.clear();  m_serverError.append(m_serverPeer->errorString()); return  m_serverError;}
signals:
	void connected();
	void disconnected();
	void readyRead();

public slots:
	void OnServerConnected();
	void OnServerDisconnected();
	void OnRead();

private:
	QList<YuanS> 	m_rlist;
	QList<YuanS> 	m_wlist;
	QString 		m_server;
	quint16			m_port;
	QByteArray		m_rbuf;

	QTcpSocket		*m_serverPeer;
	QString			m_serverError;
};

#endif // YUAN_H
