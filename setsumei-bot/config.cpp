#include "config.hpp"

Config::Config(QObject* parent)
:QObject(parent)
{
	//Limit writing to file to once every five seconds so we don't wear out the
	//hard drive as much from constant writing, while still keeping a somewhat
	//recent version of the config saved in case of a crash.
	_flushTimer.setInterval(5000);
	_flushNeeded = false;
	connect(&_flushTimer, &QTimer::timeout,
			this, &Config::flushTimerTimeout);
	readFile();
	_flushTimer.start();
}

Config::~Config()
{
	if(_flushTimer.isActive())
		_flushTimer.stop();
	//Make sure the file is synced when we get deleted.
	if(_flushNeeded)
		flushNow();
}

QJsonObject Config::object()
{
	return _object;
}

void Config::setObject(QJsonObject object)
{
	_object = object;
	requestFlush();
}

void Config::requestFlush()
{
	qDebug()<<"Config file flush requested...";
	_flushNeeded = true;
}

void Config::flushNow()
{
	_flushNeeded = false;
	qDebug()<<"Flushing config to file...";
	QFile configFile(QCoreApplication::applicationDirPath() + "/config.json");
	if(!configFile.open(QFile::WriteOnly | QFile::Truncate))
	{
		qDebug()<<"Could open config file for writing.";
		qDebug()<<"Reason:"<<configFile.errorString();
	}
	configFile.write(QJsonDocument(_object).toJson(QJsonDocument::Indented));
	configFile.close();
}

void Config::flushTimerTimeout()
{
	if(_flushNeeded)
		flushNow();
}

void Config::readFile()
{
	qDebug()<<"Opening config file...";
	QFile configFile(QCoreApplication::applicationDirPath() + "/config.json");
	if(!configFile.exists())
	{
		qDebug()<<"Config file does not exist, creating empty one...";
		if(!configFile.open(QFile::WriteOnly | QFile::Truncate))
		{
			qDebug()<<"Could not create new config file.";
			qDebug()<<"Reason:"<<configFile.errorString();
		}
		configFile.write(QJsonDocument(QJsonObject()).toJson(QJsonDocument::Indented));
		configFile.close();
	}
	if(!configFile.open(QFile::ReadOnly))
	{
		qDebug()<<"Could not open config file.";
		qDebug()<<"Reason:"<<configFile.errorString();
	}
	qDebug()<<"Reading config from file...";
	_object = QJsonDocument::fromJson(configFile.readAll()).object();
	configFile.close();
	qDebug()<<"Done.";
}
