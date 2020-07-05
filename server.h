#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTcpServer>
#include "yuan.h"


class ServerThread : public QThread
{
	Q_OBJECT

public:
	explicit ServerThread(QObject *parent = nullptr);
	~ServerThread();

signals:
	void client1Connected(bool);
	void client2Connected(bool);

public slots:
	void OnNewConnection();
	void On1Disconnected();
	void On1ReadyRead();
	void On2Disconnected();
	void On2ReadyRead();

private:
	QTcpServer *m_tcpServer;
	QTcpSocket *m_client1;
	QTcpSocket *m_client2;
	
};

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

private:
	void setupInfoBox();

public slots:
	void OnParaChanged();
	void OnClient1Connected(bool);
	void OnClient2Connected(bool);

private:
    Ui::Server *ui;
	QTcpServer  *m_tcpServer;

	QLabel 		*m_lb_state1;
	QLabel 		*m_lb_state2;
	QLineEdit	*m_le_server;
	QLineEdit	*m_le_port;

	ServerThread *m_serverThread;
};


#endif // SERVER_H
