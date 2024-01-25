#include <Error.hpp>
#include <cerrno>

//	Default error message and status code
Error::Error(void):
	wht(strerror(errno)), whr(""), code(errno) {}

//	Copy constructor
Error::Error(Error const &cpy):
	std::exception(cpy), wht(cpy.wht), whr(cpy.whr), code(cpy.code) {}

//	Personalised error code, message and location
Error::Error(int cde, char const *wht, char const *whr):
	wht(wht), whr(whr), code(cde) {}

//	Reverse inheritance constructor
Error::Error(std::exception const &e):
	wht(e.what()), whr(""), code(errno ? errno : 1) {}

//	Destructor
Error::~Error(void) throw() {}

//	Copy operator
Error	&Error::operator=(Error const &cpy)
{
	this->std::exception::operator=(cpy);
	this->wht = cpy.wht;
	this->whr = cpy.whr;
	this->code = cpy.code;
	return (*this);
}

//	Overloaded what function
char const	*Error::what(void) const throw()
{
	return (this->wht);
}

//	Indicate where the error occurred
char const	*Error::where(void) const throw()
{
	return (this->whr);
}

//	Returns status code
int	Error::getCode(void) const throw()
{
	return (this->code);
}

//	Prints error on stderr and returns status code
int	Error::print(void) const throw()
{
	std::cerr << "error: ";
	if (*this->whr)
		std::cerr << this->whr << ": ";
	if (*this->wht)
		std::cerr << this->wht << std::endl;
	else
		std::cerr << "undefined" << std::endl;
	return (this->code);
}

//	Prints std::exception or Error on stderr and return status code
int	Error::print(std::exception const &e) throw()
{
	try
	{
		return ((dynamic_cast<Error const &> (e)).print());
	}
	catch (...)
	{
		std::cerr << "error: " << e.what() << std::endl;
		return (errno ? errno : 1);
	}
}
