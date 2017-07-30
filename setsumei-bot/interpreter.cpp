#include "interpreter.hpp"
#include "commands/all.hpp"

Interpreter::Interpreter(QDiscord& discord, QString prefix, QObject* parent)
:QObject(parent), _discord(discord)
{

	connect(_discord.state(), &QDiscordStateComponent::messageCreated,
			this, &Interpreter::messageReceived);
	//Cache the config object so we don't have to keep copying it every time we
	//need it, not that anyone's going to notice the speed difference with a
	//small config file.
	QJsonObject configObject = _config.object();
	if(!configObject.contains("interpreter"))
	{
        configObject["interpreter"] = QJsonObject({{"prefix", "s!"}});
		_config.setObject(configObject);
	}
	qDebug()<<"Setting prefix...";
	_prefix = configObject["interpreter"].toObject()["prefix"].toString(prefix);
	qDebug()<<"Prefix is now"<<_prefix;
	registerCommands();
}

void Interpreter::messageReceived(QDiscordMessage message)
{
	qDebug()<<"Message received. Author:"<<(message.author()?message.author()->username():"nullptr")
		   <<"Content:"<<message.content()
		  <<"Channel:"<<(message.channel()?message.channel()->name():message.channelId());

	//Make sure the message is a command.
	if(!message.content().startsWith(_prefix))
		return;
	//Some string handling to get the command out.
	int i = message.content().indexOf("\n") - _prefix.length();
	QString content = message.content().mid(_prefix.length(), i);
	QString command = content.mid(0, content.indexOf(" "));
	//Constant reference to the global command manager's command list.
	const QMap<QString, Command*>& commands =
			CommandManager::instance().commands();
	//Make sure the command is actually one we know.
	if(!commands.keys().contains(command))
	{
        _discord.rest()->sendMessage("`" + command + "` is not a command.", message.channelId(),false);
		return;
	}
	QStringList args;
	//Populate the command arguments if there are actually any arguments.
	if(content.contains(" "))
	{
		//Get the argument text.
		QString arg = content.mid(content.indexOf(" ") + 1);
		//Tokenize the arguments with a parser that can handle quotes and escape
		//characters.
		args = Utils::tokenizeArguments(arg);
	}
	qDebug()<<"Executing command:"<<command<<args;
	//And actually forward the command to the command itself.
	commands.value(command)->dispatch(message, args);
}

void Interpreter::registerCommands()
{
	qDebug()<<"Registering commands...";
    REGISTER_COMMAND(UrbanCommand, _discord);
    REGISTER_COMMAND(HelpCommand, _discord, _prefix);
    REGISTER_COMMAND(SetsumeiCommand, _discord);
    REGISTER_COMMAND(WaifuCommand, _discord);
    REGISTER_COMMAND(FanartCommand, _discord);
	qDebug()<<"All commands registered.";
}
