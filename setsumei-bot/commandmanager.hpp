#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include <QMap>
#include <QList>
#include <QString>

class Command;

class CommandManager
{
public:
	CommandManager(CommandManager& other) = delete;
	CommandManager(CommandManager&& other) = delete;
	CommandManager& operator=(CommandManager other) = delete;
	static CommandManager& instance();
	void insert(Command* command);
	Command* command(QString name);
	const QMap<QString, Command*>& commands();
private:
	CommandManager() = default;
	~CommandManager();
	QMap<QString, Command*> _commands;
};

#define REGISTER_COMMAND(COMMAND_CLASS, ...) \
	CommandManager::instance().insert(new COMMAND_CLASS(__VA_ARGS__))

#endif // COMMANDMANAGER_HPP
