#include "fanartcommand.hpp"

FanartCommand::FanartCommand(QDiscord& discord)
:Command(discord)
{

}


void FanartCommand::dispatch(QDiscordMessage message, QStringList args)
{

    // We need to select a random fan art from the list

    std::string name;
    // In this string vector we will have our fan art list.
    std::vector<std::string> FanartNames;

    // Input stream to operate on fanart.txt.
    std::ifstream myfile("data/txt/fanart.txt");

    if(!myfile)
    {
        std::cerr <<"Error opening input file"<< std::endl;
    }
    // Extract the list from the file into name
    while (getline(myfile, name))
    {
        // Insert the content of name into the string vector
        FanartNames.push_back(name);
    }

    //initialize the random seed
    srand (time(0));
    // Generate random number with the value of FanartNames
    int randomIndex = rand() % FanartNames.size();
    // QString s now have the random selected fan art
    QString s = QString::fromStdString(FanartNames[randomIndex]);

    Q_UNUSED(args);
    //  Send the message to Discord.
    _discord.rest()->sendMessage(s, message.channelId(),false);

}


QString FanartCommand::commandName()
{
    return "fanart";
}

QString FanartCommand::helpText()
{
    return "Gives you a random Mr Brown fan art.";
}

QStringList FanartCommand::argumentText()
{
    return QStringList();
}
