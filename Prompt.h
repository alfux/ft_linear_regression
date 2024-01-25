#ifndef PROMPT_H
# define PROMPT_H

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
