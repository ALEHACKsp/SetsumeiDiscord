#ifndef HELLOCOMMAND_HPP
#define HELLOCOMMAND_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include "command.hpp"

class HelloCommand : public Command
{
public:
    HelloCommand(QDiscord& discord);
    void dispatch(QDiscordMessage message, QStringList args);
    QString commandName();
    QString helpText();
    QStringList argumentText();
};

#endif // HELLOCOMMAND_HPP
