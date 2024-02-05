#include <fstream>
#include <Error.hpp>

static void	compute(std::ifstream &data, std::string &line, double *theta, double learning_rate)
{
	size_t			count;
	double			mileage;
	double			price;
	double			theta_next[2];
	double			to_minimise;

	count = 0;
	theta_next[0] = 0;
	theta_next[1] = 0;
	to_minimise = 0;
	std::getline(data, line);
	while (!data.eof())
	{
		mileage = std::stod(line);
		line.erase(0, line.find(","));
		line.erase(0, 1);
		price = std::stod(line);
		theta_next[0] += (theta[0] + theta[1] * mileage) - price;
		theta_next[1] += ((theta[0] + theta[1] * mileage) - price) * mileage;
		to_minimise += ((theta[0] + theta[1] * mileage) - price) * ((theta[0] + theta[1] * mileage) - price);
		++count;
		std::getline(data, line);
	}
	theta[0] -= learning_rate * theta_next[0] / count;
	theta[1] -= learning_rate * theta_next[1] / count;
	to_minimise /= count;
	std::cout << "to_minimise: " << to_minimise << std::endl;
}

static void	learn(double *theta, double learning_rate)
{
	std::ifstream	data("./data.csv");
	std::string		line;

	if (!data.is_open())
		throw (Error(2, "couldn't open file", "data.csv"));
	std::getline(data, line);
	compute(data, line, theta, learning_rate);
}

static void	save(double *theta)
{
	std::ofstream	save("./.data");

	if (!save.is_open())
		throw (Error(2, "couldn't open file", "./.data"));
	save << theta[0] << std::endl << theta[1] << std::endl;
}

int	main(void)
{
	try
	{
		double	theta[2];
		double	last_theta[2];
		double	learning_rate;

		theta[0] = 0;
		theta[1] = 0;
		learning_rate = 0.001;
		do {
			last_theta[0] = theta[0];
			last_theta[1] = theta[1];
			learn(theta, learning_rate);
			std::cout << theta[0] << "," << theta[1] << std::endl;
			learning_rate /= 1000;
		} while (theta[0] != last_theta[0] || theta[1] != last_theta[1]);
		std::cout << "Final computed parameters:" << std::endl << "theta0: "
			<< theta[0] << std::endl << "theta1: " << theta[1] << std::endl;
		save(theta);
	}
	catch (std::exception const &e)
	{
		return (Error::print(e));
	}
	return (0);
}
