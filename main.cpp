#include <header.hpp>

int	predict(void)
{
	Prompt	prompt;

	return (0);
}

int	main(int ac, char **av)
{
	try
	{
		if (ac > 1)
			throw (Error(1, "too many arguments", *(av + 1)));
		predict();
	}
	catch (std::exception const &e)
	{
		return (Error::print(e));
	}
	return (0);
}
