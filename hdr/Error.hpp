#ifndef ERROR_HPP
# define ERROR_HPP

# include <exception>
# include <cstring>
# include <iostream>

/*	A class to quickly deal with exceptions and error messages */

class	Error: public std::exception
{
	char const	*wht;
	char const	*whr;
	int			code;

	public:
		Error(void);
		Error(Error const &cpy);
		Error(char const *whr);
		Error(int cde, char const *wht, char const *whr);
		Error(std::exception const &e);
		~Error(void) throw();

		Error	&operator=(Error const &cpy);
		
		char const	*what(void) const throw();
		char const	*where(void) const throw();
		int			getCode(void) const throw();
		int			print(void) const throw();
		
		static int	print(std::exception const &e) throw();
};

#endif
