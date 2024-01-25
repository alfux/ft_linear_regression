#ifndef ERROR_HPP
# define ERROR_HPP

# include <exception>
# include <iostream>

class	Error: public std::exception
{
	char const	*wht;
	char const	*whr;
	int			code;

	public:
		Error(void);
		Error(Error const &cpy);
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
