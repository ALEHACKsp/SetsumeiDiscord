#include "hellocommand.hpp"

HelloCommand::HelloCommand(QDiscord& discord)
:Command(discord)
{

}


void HelloCommand::dispatch(QDiscordMessage message, QStringList args)
{

    std::ifstream file("data/txt/firstname.txt"); // Create an input file stream to read from the file named firstname.txt.

    if (!file) { // If firstname.txt does not exist.
        std::cout << "Error: Can't open the file named firstname.txt\n";
        exit(1);
    }

    if (file.is_open()) // If file firstname.txt it's open.
    {

        std::string firstname[22]; // Array of 22 strings to hold the first names.

        for (int i = 0; i < 22; ++i)
        {
            file >> firstname[i];
        }

        std::ifstream file2("data/txt/lastname.txt"); // Create an input file stream to read from the file named lastname.txt.

        if (!file2) { // If lastname.txt does not exist.
            std::cout << "Error: Can't open the file named lastname.txt\n";
            exit(1);
        }

        if(file2.is_open()) // If file lastname.txt it's open.
        {
            std::string lastname[22]; // Array of 21 strings to hold the last names.

            for (int i = 0; i < 22; ++i)
            {
                file2 >> lastname[i];
            }

            srand(time(0)); // Generate random numbers by seeding rand with a starting value, in this case time(0) gives the time in seconds, to be used as seed.
            //char gName;

                //cout << "Generated Name: " << firstname[rand() % 22] << " " << lastname[rand() % 22] << endl;


            std::stringstream buffer;
            //buffer << "Hello Im " << firstname[rand() % 22] << " " << lastname[rand() % 22] << endl;
            buffer<< "Hello i'm " << firstname[rand() % 22] << " " << lastname[rand() % 22];

            //buffer.str();



    // QString s now have the random name
    //QString s = buffer.str();
    QString s = QString::fromStdString(buffer.str());

    Q_UNUSED(args);
    //  Send the message to Discord.
    _discord.rest()->sendMessage(s, message.channelId(),false);

        }

    }

}


QString HelloCommand::commandName()
{
    return "hello";
}

QString HelloCommand::helpText()
{
    return "Gives your greeting.";
}

QStringList HelloCommand::argumentText()
{
    return QStringList();
}
