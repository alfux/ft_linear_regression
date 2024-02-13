#ifndef ACCURACY_HPP
# define ACCURACY_HPP
# include <string>
# include <cmath>
# include <fstream>
# include <Error.hpp>

class	Accuracy
{
	double	count;
	double	mean;
	double	squared_error;
	double	deviation;
	double	root_mean_squared_error;
	double	rsquared_score;
	double	theta0;
	double	theta1;

	double	f(double x);
	void	computeMean(std::string const &sample);
	void	computeSquaredSums(std::string const &sample);
	
	public:
		Accuracy(void);
		Accuracy(Accuracy const &cpy);
		Accuracy(std::string const &sample, double theta0, double theta1);
		~Accuracy(void);

		Accuracy	&operator=(Accuracy const &cpy);

		double	getRSquaredScore(void);
		double	getRootMeanSquaredError(void);
};

#endif
