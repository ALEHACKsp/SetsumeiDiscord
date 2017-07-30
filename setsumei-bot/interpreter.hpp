#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <QObject>
#include <QDiscord>
#include <QDebug>
#include "commandmanager.hpp"
#include "config.hpp"
#include "utils.hpp"

class Interpreter : public QObject
{
	Q_OBJECT
public:
	explicit Interpreter(QDiscord& discord,
                         QString prefix = "s!",
						 QObject* parent = 0);
private:
	void messageReceived(QDiscordMessage message);
	void registerCommands();
	QDiscord& _discord;
	Config _config;
	QString _prefix;
};

#endif // INTERPRETER_HPP
