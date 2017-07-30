#ifndef SETSUMEI_HPP
#define SETSUMEI_HPP

#include <QObject>
#include <QDiscord>
#include <QFile>
#include <QCoreApplication>
#include <QDebug>
#include "interpreter.hpp"

class SelfBot : public QObject
{
	Q_OBJECT
public:
	explicit SelfBot(QObject* parent = 0);
private:
	void loginSuccess();
	void messageReceived(QDiscordMessage message);
	void loginFailed();
	QDiscord _discord;
	Interpreter _interpreter;
};

#endif // SETSUMEI_HPP
