#include <iostream>
#include <fstream>
#include <string>
#include <Accuracy.hpp>
#include <Error.hpp>

void	printAccuracy(char const *filename, double theta0, double theta1)
{
	Accuracy	accuracy(filename, theta0, theta1);

	std::cout << "R-Squared score: " << accuracy.getRSquaredScore() << std::endl;
	std::cout << "Root Mean Squared Error: " << accuracy.getRootMeanSquaredError() << std::endl;
}

void	computeAccuracy(char const *filename)
{
	std::ifstream	param(".data");
	std::string		line;
	double			theta0 = 0;
	double			theta1 = 0;

	if (!param.is_open())
		throw (Error(2, "couldn't open .data, have you trained the model yet?", ""));
	std::getline(param, line);
	theta0 = std::stod(line);
	std::getline(param, line);
	theta1 = std::stod(line);
	printAccuracy(filename, theta0, theta1);
}

int	main(int ac, char **av)
{
	try {
		if (ac != 2)
			throw (Error(1, "bad arguments", *av));
		computeAccuracy(*(av + 1));
	} catch (std::exception const &e) {
		Error::print(e);
	}
	return (0);
}
