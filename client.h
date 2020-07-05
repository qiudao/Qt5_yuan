#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include "yuan.h"

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

public slots:
	void OnConnectedServer();
	void OnDisonnectedServer();
	void OnDial();
	void OnDisconnect();
	void OnSend();
	void OnRead();

private:
	void setupInfoBox();

private:
    Ui::Client *ui;
	Yuan *m_yuan;
	QLabel 		*m_lb_state;
	QLineEdit	*m_le_server;
	QLineEdit	*m_le_port;
	QPushButton *m_btn_dial;
	QPushButton *m_btn_disconnect;
	QPushButton *m_btn_send;
	QTextEdit	*m_editRead;
	QTextEdit	*m_editWrite;
};

#endif // CLIENT_H
