#include <fstream>
#include <cmath>
#include <Error.hpp>

#define EPSILON 0.000001

static void	learningRate(std::string &line, double *theta, double *theta_next)
{
	std::ifstream	data("./data.csv");
	double			mileage;
	double			price;
	double			alpha;
	double			div;

	if (!data.is_open())
		throw (Error(2, "couldn't open file", "data.csv"));
	alpha = 0;
	div = 0;
	std::getline(data, line);
	std::getline(data, line);
	while (!data.eof())
	{
		mileage = std::stod(line);
		line.erase(0, line.find(","));
		line.erase(0, 1);
		price = std::stod(line);
		alpha += (price - (theta[1] * mileage + theta[0])) * (theta_next[1] * mileage + theta_next[0]);
		div += pow(theta_next[1] * mileage + theta_next[0], 2);
		std::getline(data, line);
	}
	alpha /= div;
	theta[0] += alpha * theta_next[0];
	theta[1] += alpha * theta_next[1];
}

static void	compute(std::ifstream &data, std::string &line, double *theta)
{
	size_t			count;
	double			mileage;
	double			price;
	double			diff;
	double			theta_next[2];

	count = 0;
	theta_next[0] = 0;
	theta_next[1] = 0;
	std::getline(data, line);
	while (!data.eof())
	{
		mileage = std::stod(line);
		line.erase(0, line.find(","));
		line.erase(0, 1);
		price = std::stod(line);
		diff = (theta[0] + theta[1] * mileage) - price;
		theta_next[0] += diff;
		theta_next[1] += diff * mileage;
		++count;
		std::getline(data, line);
	}
	theta_next[0] /= -count;
	theta_next[1] /= -count;
	learningRate(line, theta, theta_next);
}

static void	learn(double *theta)
{
	std::ifstream	data("./data.csv");
	std::string		line;

	if (!data.is_open())
		throw (Error(2, "couldn't open file", "data.csv"));
	std::getline(data, line);
	compute(data, line, theta);
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

		theta[0] = 0;
		theta[1] = 0;
		do {
			last_theta[0] = theta[0];
			last_theta[1] = theta[1];
			learn(theta);
			std::cout << "theta0 " << theta[0] << ", theta1 " << theta[1] << std::endl;
		} while (sqrt(pow(theta[0] - last_theta[0], 2) + pow(theta[1] - last_theta[1], 2)) > EPSILON);
		std::cout << "Final computed parameters:" << std::endl
			<< "theta0: " << theta[0] << std::endl
			<< "theta1: " << theta[1] << std::endl;
		save(theta);
	}
	catch (std::exception const &e)
	{
		return (Error::print(e));
	}
	return (0);
}
