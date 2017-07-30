#include "urbancommand.hpp"

UrbanCommand::UrbanCommand(QDiscord& discord, QObject* parent)
:QObject(parent), Command(discord)
{

}

void UrbanCommand::dispatch(QDiscordMessage message, QStringList args)
{
	if(args.length() != 1)
	{
        //_discord.rest()->editMessage("One argument is required.", message);
        _discord.rest()->sendMessage("One argument is required",message.channelId(),false);
		return;
	}
	//Construct the URL
	QUrl url(_urbanEndpoint + args[0]);
	//Construct our request
	QNetworkRequest request(url);
	//Tell the access manager to GET our request.
	QNetworkReply* reply = _accessManager.get(request);
	//Connect the reply with a lambda so we can process it once it's done.
	//Notice that our lambda captures by copy instead of by reference.
	//This method is going to end and everything in scope will be destroyed,
	//after which the lambda will be called once the request is done.
	//If the lambda captured by reference, those references wouldn't really be
	//pointing to valid objects.
	connect(reply, &QNetworkReply::finished,
	[=]() {
		if(reply->error() != QNetworkReply::NoError)
		{
            _discord.rest()->sendMessage("Error: " + reply->errorString(),message.channelId(),false);
			reply->deleteLater();
			return;
		}
		QJsonObject object = QJsonDocument::fromJson(reply->readAll()).object();
		if(
				!object.contains("result_type") ||
				object["result_type"].toString() != "exact" ||
				!object.contains("list")
		  )
		{
            _discord.rest()->sendMessage("Could not find a definition.",message.channelId(),false);
			reply->deleteLater();
			return;
		}
		object = object["list"].toArray().first().toObject();
		QString definition = "**" + args[0] + ":**\n";
		definition += "**Definition:**\n" + object["definition"].toString() + "\n";
		definition += "**Example:**\n" + object["example"].toString() + "\n";
		definition += "**Link:** <" + object["permalink"].toString() + ">";
		if(definition.length() > 2000)
			definition = "Definition too long. Visit " + object["permalink"].toString();
        _discord.rest()->sendMessage(definition, message.channelId(),false);
		reply->deleteLater();
	});
}

QString UrbanCommand::commandName()
{
	return "urban";
}

QString UrbanCommand::helpText()
{
	return "Searches <http://urbandictionary.com> for the specified text.";
}

QStringList UrbanCommand::argumentText()
{
	return {"(TEXT)", "TEXT is the query."};
}
