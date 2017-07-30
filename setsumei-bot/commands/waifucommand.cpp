#include "waifucommand.hpp"

WaifuCommand::WaifuCommand(QDiscord& discord)
:Command(discord)
{

}


void WaifuCommand::dispatch(QDiscordMessage message, QStringList args)
{

    // We need to select a random waifu from the list

    std::string name;
    // In this string vector we will have our waifu list.
    std::vector<std::string> WaifuNames;

    // Input stream to operate on waifus.txt.
    std::ifstream myfile("data/txt/waifus.txt");

    if(!myfile)
    {
        std::cerr <<"Error opening input file"<< std::endl;
    }
    // Extract the list from the file into name
    while (getline(myfile, name))
    {
        // Insert the content of name into the string vector
        WaifuNames.push_back(name);
    }

    //initialize the random seed
    srand (time(0));
    // Generate random number with the value of WaifuNames
    int randomIndex = rand() % WaifuNames.size();
    // QString s now have the random selected waifu
    QString s = QString::fromStdString(WaifuNames[randomIndex]);

    Q_UNUSED(args);
    //  Send the message to Discord.
    _discord.rest()->sendMessage(s, message.channelId(),false);

}


QString WaifuCommand::commandName()
{
    return "waifu";
}

QString WaifuCommand::helpText()
{
    return "Gives you a free waifu.";
}

QStringList WaifuCommand::argumentText()
{
    return QStringList();
}
