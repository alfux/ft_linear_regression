#ifndef PROMPT_HPP
# define PROMPT_HPP

# include <termios.h>
# include <string>

class	Prompt
{
	std::string	str;
	char		c;

	public:
		Prompt(void);
		Prompt(Prompt const &cpy);
		~Prompt(void);

		Prompt	&operator=(Prompt const &cpy);
};

#endif
