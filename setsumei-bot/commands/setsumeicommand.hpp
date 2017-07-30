#ifndef SETSUMEICOMMAND_HPP
#define SETSUMEICOMMAND_HPP

#include "command.hpp"

class SetsumeiCommand : public Command
{
public:
    SetsumeiCommand(QDiscord& discord);
    void dispatch(QDiscordMessage message, QStringList args);
    QString commandName();
    QString helpText();
    QStringList argumentText();
};

#endif // SETSUMEICOMMAND_HPP
