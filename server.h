#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFormLayout>
#include "yuan.h"

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();


public slots:
	void OnConnectedServer();
	void OnDisonnectedServer();
	void OnParaChanged();

private:
	void setupInfoBox();

private:
    Ui::Server *ui;
	Yuan *m_yuan;
	QLabel 		*m_lb_state;
	QLineEdit	*m_le_server;
	QLineEdit	*m_le_port;
};

#endif // SERVER_H
