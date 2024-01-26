#ifndef PROMPT_HPP
# define PROMPT_HPP

# include <termios.h>
# include <signal.h>
# include <iostream>
# include <string>
# include <Error.hpp>

/*	A simple prompt class to wrap terminal setting changes and signal changes in
	order to properly process user inputs when asked in a C++ program*/

class	Prompt
{
	static struct termios		default_settings;
	static size_t				instances;

	struct termios				input_settings;
	struct sigaction			signal_settings;
	std::string					esc;
	std::string					str;
	char						c;
	size_t						cursor;

	int		setSignals(void);
	void	unsetSignals(void);
	void	processEscapeSequence(void);

	static void	signalHandler(int sig);
	
	public:
		Prompt(void);
		Prompt(Prompt const &cpy);
		~Prompt(void);

		Prompt	&operator=(Prompt const &cpy);
	
		std::string const	&get(void);
		std::string const	&input(void);
};

#endif
