#include "setsumei.hpp"

SelfBot::SelfBot(QObject* parent)
:QObject(parent), _discord(),_interpreter(_discord)
{
	connect(&_discord, &QDiscord::loginSuccess, this, &SelfBot::loginSuccess);
	connect(&_discord, &QDiscord::loginFailed, this, &SelfBot::loginFailed);
	qDebug()<<"Opening token file...";
    QFile tokenFile(QCoreApplication::applicationDirPath()+"/data/tokens/token.txt");
	if(!tokenFile.exists())
	{
		qDebug()<<tokenFile.fileName()<<"does not exist.";
		qFatal("Could not recover from error.");
	}
	if(!tokenFile.open(QFile::ReadOnly))
	{
		qDebug()<<"Could not open"<<tokenFile.fileName();
		qFatal("Could not recover from error.");
	}
	qDebug()<<"Reading token...";
	QString token = tokenFile.readLine().trimmed();
	qDebug()<<"Starting login...";
	_discord.login(token, QDiscordTokenType::None);
	qDebug()<<"Closing token file...";
	tokenFile.close();
}

void SelfBot::loginSuccess()
{
	qDebug()<<"Login successful.";
}

void SelfBot::loginFailed()
{
	qDebug()<<"Login failed.";
	qApp->exit(EXIT_FAILURE); //Stop the application with a fail return code.
}
