#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <qdiscord.hpp>

class Command
{
public:
	//Require a reference to QDiscord when constructing all commands.
	Command(QDiscord& discord);
	//Virtual destructor. Not having this would be pretty bad.
	virtual ~Command() = default;
	//A dispatch member function that gets called when the command is called by
	//the user.
	virtual void dispatch(QDiscordMessage message, QStringList args) = 0;
	//The command name that will be used to call the command.
	virtual QString commandName() = 0;
	//A description of the command.
	virtual QString helpText() = 0;
	//A list of strings to describe the arguments this command expects.
	//The first element should be the syntax, while the next elements should
	//explain each argument separately.
	virtual QStringList argumentText() = 0;
protected:
	//All commands will get a reference to QDiscord for output.
	QDiscord& _discord;
};

#endif // COMMAND_HPP
