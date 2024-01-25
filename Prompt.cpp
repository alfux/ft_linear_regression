#include <Prompt.hpp>

Prompt::Prompt(void):
	str(), c(0)
{
	//	Empty body
}

Prompt::Prompt(Prompt const &cpy):
	str(cpy.str), c(cpy.c)
{
	//	Empty body
}

Prompt::~Prompt(void)
{
	//	Empty body
}

Prompt	&Prompt::operator=(Prompt const &cpy)
{
	this->str = cpy.str;
	this->c = cpy.c;
	return (*this);
}
