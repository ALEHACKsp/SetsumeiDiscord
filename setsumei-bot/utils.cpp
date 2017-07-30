#include "utils.hpp"

QStringList Utils::tokenizeArguments(QString args)
{
	//This is totally not copied from StackOverflow.
	//Totes.
	QStringList matchList;
	enum class ParserState {
		Beginning, Word, Quote, Escape
	} state = ParserState::Beginning;
	QString buffer;
	for(QChar c : args)
	{
		switch(state)
		{
		case ParserState::Beginning:
			if(c == '\"')
				state = ParserState::Quote;
			else if(c != ' ')
			{
				state = ParserState::Word;
				buffer.append(c);
			}
			break;
		case ParserState::Word:
			if(c == ' ')
			{
				state = ParserState::Beginning;
				matchList.append(buffer);
				buffer.clear();
			}
			else if(c == '\\')
				state = ParserState::Escape;
			else
				buffer.append(c);
			break;
		case ParserState::Quote:
			if(c == '\"')
			{
				state = ParserState::Beginning;
				matchList.append(buffer);
				buffer.clear();
			}
			else if(c == '\\')
				state = ParserState::Escape;
			else
				buffer.append(c);
			break;
		case ParserState::Escape:
			if(c == '\"' || c == '\\')
			{
				state = ParserState::Quote;
				buffer.append(c);
			}
			else if(c == 'n')
			{
				state = ParserState::Quote;
				buffer.append('\n');
			}
			else
			{
				state = ParserState::Quote;
				buffer.append('\\');
				buffer.append(c);
			}
		default:;
		}
	}
	if(state != ParserState::Beginning)
	{
		matchList.append(buffer);
		buffer.clear();
	}
	return matchList;
}
