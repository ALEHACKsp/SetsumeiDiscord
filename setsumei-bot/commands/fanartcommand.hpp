#ifndef FANARTCOMMAND_H
#define FANARTCOMMAND_H

#include <iostream>
#include <fstream>
#include "command.hpp"

class FanartCommand : public Command
{
public:
    FanartCommand(QDiscord& discord);
    void dispatch(QDiscordMessage message, QStringList args);
    QString commandName();
    QString helpText();
    QStringList argumentText();
};

#endif // FANARTCOMMAND_H
