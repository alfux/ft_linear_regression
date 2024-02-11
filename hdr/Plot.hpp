#ifndef PLOT_HPP
# define PLOT_HPP
# include <SDL.h>
# include <fstream>
# include <string>
# include <Error.hpp>

enum	WinState
{
	PLAY,
	EXIT
};

typedef struct	s_coord
{
	double	x;
	double	y;
}				t_coord;

class	Plot
{
	static size_t	pv_number_of_instances;

	SDL_Window		*pv_window;
	SDL_Renderer	*pv_renderer;
	SDL_Texture		*pv_canvas;
	uint32_t		*pv_pixels;
	uint32_t		pv_width;
	uint32_t		pv_height;
	double			pv_max_x;
	double			pv_max_y;
	WinState		pv_current;

	void	processInput(void);
	void	colorPixel(ssize_t x, ssize_t y, uint32_t argb);
	t_coord	toCoord(double x, double y);
	void	destroy(void);

	public:
		Plot(void);
		Plot(Plot const &cpy);
		~Plot(void);

		Plot	&operator=(Plot const &cpy);

		void	drawAxis(uint32_t argb);
		void	drawFunction(double (*f)(double), uint32_t argb);
		void	drawDots(std::string const &file, uint32_t argb);
		void	calibrate(std::string const &file);
		void	draw(void);
		void	wait(void);
};

#endif
