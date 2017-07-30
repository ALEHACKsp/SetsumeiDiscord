#include "helpcommand.hpp"
#include "commandmanager.hpp"

HelpCommand::HelpCommand(QDiscord& _discord, QString& prefix)
:Command(_discord), _prefix(prefix)
{

}

void HelpCommand::dispatch(QDiscordMessage message, QStringList args)
{
	if(args.length() > 1)
	{
        _discord.rest()->sendMessage("Too many arguments.", message.channelId(),false);

		return;
	}
	//Give information for one command in case it's specified.
	if(args.length() == 1)
	{
		Command* command =CommandManager::instance().command(args[0]);
		if(!command)
		{
            _discord.rest()->sendMessage("Command not found.", message.channelId(),false);
			return;
		}
		QString text = "**" + command->commandName() + ":**\n";
		text += "**Description:**\n";
		text += command->helpText() + "\n";
		text += "**Syntax:** `" + _prefix + command->commandName();
		if(command->argumentText().length() == 0)
			text += "`\n";
		else
		{
			text += " " + command->argumentText()[0] + "`\n";
			text += "**Where:**";
			for(const QString arg : command->argumentText().mid(1))
				text += "\n" + arg;
		}
        _discord.rest()->sendMessage(text, message.channelId(), false);
		return;
	}
	//If not, just list all of the commands.
	QString text = "All available commands:\n`";
	text += CommandManager::instance().commands().keys().join("`, `");
	text += "`.";
    _discord.rest()->sendMessage(text, message.channelId(), false);
}

QString HelpCommand::commandName()
{
	return "help";
}

QString HelpCommand::helpText()
{
	return "Provides command descriptions and usage information.";
}

QStringList HelpCommand::argumentText()
{
	return {"[COMMAND]",
		"COMMAND is the command you need help with."
		"When omitted will display all available commands."};
}
