#include <Plot.hpp>

size_t	Plot::pv_number_of_instances = 0;

Plot::Plot(void):
	pv_window(nullptr),
	pv_renderer(nullptr),
	pv_canvas(nullptr),
	pv_pixels(nullptr),
	pv_width(1024),
	pv_height(768),
	pv_max_x(1024),
	pv_max_y(768),
	pv_current(PLAY)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->pv_window = SDL_CreateWindow("Graph", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, this->pv_width, this->pv_height, SDL_WINDOW_OPENGL);
	if (!this->pv_window)
		throw (Error(3, SDL_GetError(), "Plot::Plot(void)"));
	this->pv_renderer = SDL_CreateRenderer(this->pv_window, -1, 0);
	if (!this->pv_renderer)
		throw (Error(4, SDL_GetError(), "Plot::Plot(void)"));
	this->pv_canvas = SDL_CreateTexture(this->pv_renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, this->pv_width, this->pv_height);
	if (!this->pv_canvas)
		throw (Error(5, SDL_GetError(), "Plot::Plot(void)"));
	this->pv_pixels = new uint32_t [this->pv_width * this->pv_height];
	if (!this->pv_pixels)
		throw (Error("Plot::Plot(void)"));
	memset(this->pv_pixels, 0, this->pv_width * this->pv_height * sizeof (uint32_t));
	++Plot::pv_number_of_instances;
}

Plot::Plot(Plot const &cpy):
	pv_window(nullptr),
	pv_renderer(nullptr),
	pv_canvas(nullptr),
	pv_pixels(nullptr),
	pv_width(1024),
	pv_height(768),
	pv_max_x(1024),
	pv_max_y(768),
	pv_current(PLAY)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->pv_window = SDL_CreateWindowFrom(cpy.pv_window);
	if (!this->pv_window)
		throw (Error(3, SDL_GetError(), "Plot::Plot(Plot const &cpy)"));
	this->pv_renderer = SDL_CreateRenderer(this->pv_window, -1, 0);
	if (!this->pv_renderer)
		throw (Error(4, SDL_GetError(), "Plot::Plot(void)"));
	this->pv_canvas = SDL_CreateTexture(this->pv_renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, this->pv_width, this->pv_height);
	if (!this->pv_canvas)
		throw (Error(5, SDL_GetError(), "Plot::Plot(void)"));
	this->pv_pixels = new uint32_t [this->pv_width * this->pv_height];
	if (!this->pv_pixels)
		throw (Error("Plot::Plot(void)"));
	for (size_t i = 0; i < this->pv_width * this->pv_height; ++i)
		this->pv_pixels = cpy.pv_pixels;
	++Plot::pv_number_of_instances;
}

void	Plot::destroy(void)
{
	delete[] (this->pv_pixels);
	SDL_DestroyTexture(this->pv_canvas);
	SDL_DestroyRenderer(this->pv_renderer);
	SDL_DestroyWindow(this->pv_window);
}

Plot::~Plot(void)
{
	--Plot::pv_number_of_instances;
	this->destroy();
	if (!Plot::pv_number_of_instances)
		SDL_Quit();
}

Plot	&Plot::operator=(Plot const &cpy)
{
	SDL_Window	*buffer;

	buffer = SDL_CreateWindowFrom(cpy.pv_window);
	if (!buffer)
		throw (Error(3, SDL_GetError(), "Plot::operator=(Plot const &cpy)"));
	this->destroy();
	this->pv_window = buffer;
	return (*this);
}

void	Plot::processInput(void)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				this->pv_current = EXIT;
				break ;
			case SDL_KEYDOWN:
				this->pv_current = EXIT;
				break ;
			default :
				break ;
		}
	}
}

void	Plot::colorPixel(ssize_t x, ssize_t y, uint32_t argb)
{
	if (x >= 0 && x < this->pv_width && y >= 0 && y < this->pv_height)
		*(this->pv_pixels + y * this->pv_width + x) = argb;
}

t_coord	Plot::toCoord(double x, double y)
{
	t_coord	coord;

	coord.x = x;
	coord.y = this->pv_height - y;
	return (coord);
}

void	Plot::drawAxis(uint32_t argb)
{
	size_t	i;

	for (i = 0; i < this->pv_height; ++i)
	{
		this->colorPixel(0, i, argb);
		if (!(i % (this->pv_height / 100)))
		{
			this->colorPixel(1, i, argb);
			this->colorPixel(2, i, argb);
			this->colorPixel(3, i, argb);
			if (!(i % ((this->pv_height / 100) * 10)))
			{
				this->colorPixel(4, i, argb);
				this->colorPixel(5, i, argb);
				this->colorPixel(6, i, argb);
			}
		}
	}
	for (i = 0; i < this->pv_width; ++i)
	{
		this->colorPixel(i, this->pv_height - 1, argb);
		if (!(i % (this->pv_width / 100)))
		{
			this->colorPixel(i, this->pv_height - 2, argb);
			this->colorPixel(i, this->pv_height - 3, argb);
			this->colorPixel(i, this->pv_height - 4, argb);
			if (!(i % ((this->pv_width / 100) * 10)))
			{
				this->colorPixel(i, this->pv_height - 5, argb);
				this->colorPixel(i, this->pv_height - 6, argb);
				this->colorPixel(i, this->pv_height - 7, argb);
			}
		}
	}
}

void	Plot::drawFunction(double (*f)(double), uint32_t argb)
{
	size_t	x;
	t_coord	coord;

	for (x = 0; x < this->pv_width; ++x)
	{
		coord = this->toCoord(x,
			f(x * this->pv_max_x / this->pv_width) * this->pv_height / this->pv_max_y);
		this->colorPixel(coord.x, coord.y, argb);
	}
	SDL_UpdateTexture(this->pv_canvas, nullptr, this->pv_pixels,
		this->pv_width * sizeof (uint32_t));
}

void	Plot::drawDots(std::string const &file, uint32_t argb)
{
	double			mileage;
	double			price;
	t_coord			coord;
	std::string		line;
	std::ifstream	data(file);

	if (!data.is_open())
		throw (Error(2, "bad argument", "Plot::drawDot(std::ifstream &data"));
	std::getline(data, line);
	std::getline(data, line);
	while (!data.eof())
	{
		mileage = std::stod(line);
		line.erase(0, line.find(","));
		line.erase(0, 1);
		price = std::stod(line);
		std::getline(data, line);
		coord = this->toCoord(mileage * this->pv_width / this->pv_max_x,
			price * this->pv_height / this->pv_max_y);
		this->colorPixel(coord.x, coord.y, argb);
		this->colorPixel(coord.x + 1, coord.y, argb);
		this->colorPixel(coord.x + 1, coord.y + 1, argb);
		this->colorPixel(coord.x, coord.y + 1, argb);
	}
}

void	Plot::calibrate(std::string const &file)
{
	double			mileage;
	double			price;
	std::string		line;
	std::ifstream	data(file);

	if (!data.is_open())
		throw (Error(2, "bad argument", "Plot::drawDot(std::ifstream &data"));
	std::getline(data, line);
	std::getline(data, line);
	while (!data.eof())
	{
		mileage = std::stod(line);
		line.erase(0, line.find(","));
		line.erase(0, 1);
		price = std::stod(line);
		std::getline(data, line);
		if (mileage > this->pv_max_x)
			this->pv_max_x = mileage;
		if (price > this->pv_max_y)
			this->pv_max_y = price;
	}
	this->pv_max_x += 0.1 * this->pv_max_x;
	this->pv_max_y += 0.1 * this->pv_max_y;
}

void	Plot::draw(void)
{
	this->processInput();
	SDL_RenderClear(this->pv_renderer);
	SDL_RenderCopy(this->pv_renderer, this->pv_canvas, nullptr, nullptr);
	SDL_RenderPresent(this->pv_renderer);
	SDL_UpdateWindowSurface(this->pv_window);
}

void	Plot::wait(void)
{
	while (this->pv_current != EXIT)
		this->processInput();
}
