#include "setsumeicommand.hpp"

SetsumeiCommand::SetsumeiCommand(QDiscord& discord)
:Command(discord)
{

}

void SetsumeiCommand::dispatch(QDiscordMessage message, QStringList args)
{
    Q_UNUSED(args);
    //main message
    _discord.rest()->sendMessage("Setsumei it's where we are making understanding things a little easier through analysis, summaries and breaks down hours of research and learning into just a few minutes. Saving you time while making you smarter and cooler than your dummy friends. Our channel: https://www.youtube.com/channel/UC6mK6FQowKjHpjEgOfh6pMg",message.channelId(),false);
}

QString SetsumeiCommand::commandName()
{
    return "setsumei";
}

QString SetsumeiCommand::helpText()
{
    return "Information about setsumei youtube channel description.";
}

QStringList SetsumeiCommand::argumentText()
{
    return QStringList();
}
