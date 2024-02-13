#include <Accuracy.hpp>

Accuracy::Accuracy(std::string const &sample, double theta0, double theta1):
	count(0),
	mean(0),
	squared_error(0),
	deviation(0),
	root_mean_squared_error(0),
	rsquared_score(0),
	theta0(theta0),
	theta1(theta1)
{
	this->computeMean(sample);
	this->computeSquaredSums(sample);
	this->rsquared_score = 1 - (this->squared_error / (this->count * this->deviation));
	this->root_mean_squared_error = sqrt(this->squared_error / this->count);
}

Accuracy::~Accuracy(void) {}

double	Accuracy::f(double x)
{
	return (this->theta0 + this->theta1 * x);
}

void	Accuracy::computeMean(std::string const &sample)
{
	std::ifstream	file(sample);
	std::string		line;

	if (!file.is_open())
		throw (Error(2, "couldn't open file", sample.c_str()));
	std::getline(file, line);
	std::getline(file, line);
	while (!file.eof())
	{
		line.erase(0, line.find_first_of(","));
		line.erase(0, 1);
		this->mean += std::stod(line);
		++this->count;
		std::getline(file, line);
	}
	this->mean /= this->count;
}

void	Accuracy::computeSquaredSums(std::string const &sample)
{
	std::ifstream	file(sample);
	std::string		line;
	double			mileage;
	double			price;

	if (!file.is_open())
		throw (Error(2, "counldn't open file", sample.c_str()));
	std::getline(file, line);
	std::getline(file, line);
	while (!file.eof())
	{
		mileage = std::stod(line);
		line.erase(0, line.find_first_of(","));
		line.erase(0, 1);
		price = std::stod(line);
		this->squared_error += pow(price - this->f(mileage), 2);
		this->deviation += pow(price - this->mean, 2);
		std::getline(file, line);
	}
	this->deviation /= this->count - 1;
}

double	Accuracy::getRSquaredScore(void)
{
	return (this->rsquared_score);
}

double	Accuracy::getRootMeanSquaredError(void)
{
	return (this->root_mean_squared_error);
}
