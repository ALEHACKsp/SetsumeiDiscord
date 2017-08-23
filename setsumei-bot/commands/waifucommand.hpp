#ifndef WAIFUCOMMAND_HPP
#define WAIFUCOMMAND_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <chrono>
#include "command.hpp"

class WaifuCommand : public Command
{
public:
    WaifuCommand(QDiscord& discord);
    void dispatch(QDiscordMessage message, QStringList args);
    QString commandName();
    QString helpText();
    QStringList argumentText();
};

#endif // WAIFUCOMMAND_HPP
