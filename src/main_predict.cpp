#include <fstream>
#include <Prompt.hpp>
#include <Error.hpp>

static double	estimatePrice(double mileage)
{
	std::ifstream	data("./.data");
	std::string		line;
	double			t0;
	double			t1;

	if (!data.is_open())
		throw (Error(2, "couldn't open file", ".data"));
	std::getline(data, line);
	t0 = std::stod(line);
	std::getline(data, line);
	t1 = std::stod(line);
	return (t0 + t1 * mileage);
}

static int	predict()
{
	Prompt	prompt;
	double	mileage;

	std::cout << "mileage: ";
	prompt.input();
	mileage = std::stod(prompt.get());
	std::cout << "estimated price: " << estimatePrice(mileage) << " (" << mileage << ")"  << std::endl;
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
