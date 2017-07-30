#include "commandmanager.hpp"
#include "command.hpp"

CommandManager& CommandManager::instance()
{
	static CommandManager mgr;
	return mgr;
}

void CommandManager::insert(Command* command)
{
	if(!command)
		return;
	_commands.insert(command->commandName(), command);
}

CommandManager::~CommandManager()
{
	qDeleteAll(_commands);
}

Command* CommandManager::command(QString name)
{
	if(!_commands.keys().contains(name))
		return nullptr;
	return _commands.value(name);
}

const QMap<QString, Command*>& CommandManager::commands()
{
	return _commands;
}
