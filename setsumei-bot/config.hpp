#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QObject>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>

class Config
:public QObject
{
public:
	explicit Config(QObject* parent = 0);
	~Config();
	QJsonObject object();
	void setObject(QJsonObject object);
	void requestFlush();
	void flushNow();
private:
	void flushTimerTimeout();
	void readFile();
	bool _flushNeeded;
	QTimer _flushTimer;
	QJsonObject _object;
};

#endif // CONFIG_HPP
