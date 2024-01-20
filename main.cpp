#include <header.hpp>

int	main(int ac, char **av)
{
	while (*av)
		std::cout << ac << ": " << *(av++) << std::endl;
	return (0);
}
