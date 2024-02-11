#include <fstream>
#include <cmath>
#include <Plot.hpp>
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

static double	estimate(double mileage)
{
	std::ifstream	data("./.data");
	std::string		line;
	double			t0;
	double			t1;

	if (!data.is_open())
		return (0);
	std::getline(data, line);
	t0 = std::stod(line);
	std::getline(data, line);
	t1 = std::stod(line);
	return (t0 + t1 * mileage);
}

int	main(int ac, char **av)
{
	try {
		Plot			plot;
		double			theta[2] = {0, 0};
		double			last_theta[2] = {0, 0};
		uint32_t		argb = 0xff00ffff;
		std::ifstream	dots("./data.csv");

		if (ac != 1)
			throw (Error(1, "no arguments authorized", *(av + 1)));
		if (!dots.is_open())
			throw (Error(2, "couldn't open file", "data.csv"));
		plot.calibrate("./data.csv");
		plot.drawAxis(0xffffffff);
		plot.drawDots("./data.csv", 0xffff0000);
		do {
			last_theta[0] = theta[0];
			last_theta[1] = theta[1];
			learn(theta);
			save(theta);
			plot.drawFunction(&estimate, argb);
			plot.draw();
			argb += 0x00110000 - 0x00001111;
		} while (sqrt(pow(theta[0] - last_theta[0], 2) + pow(theta[1] - last_theta[1], 2)) > EPSILON);
		plot.wait();
	} catch (std::exception const &e) {
		return (Error::print(e));
	}
	return (0);
}
