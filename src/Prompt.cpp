#include <Prompt.hpp>

//	Static class variables to keep original terminal settings
struct termios	Prompt::default_settings;
size_t			Prompt::instances = 0;

//	Default constructor, sets terminal and signal settings to our convenience
Prompt::Prompt(void):
	esc(), str(), c(0), cursor(0)
{
	if (tcgetattr(0, &this->input_settings))
		throw (Error("Prompt::Prompt(void)"));
	if (!Prompt::instances)
		Prompt::default_settings = this->input_settings;
	this->input_settings.c_lflag &= ~(ICANON | ECHO);
	this->signal_settings.sa_handler = Prompt::signalHandler;
	if (this->setSignals() || tcsetattr(0, TCSANOW, &this->input_settings))
	{
		this->unsetSignals();
		throw (Error("Prompt::Prompt(void)"));
	}
	Prompt::instances++;
}

//	Signal handler, reset terminal settings and quits
void	Prompt::signalHandler(int sig)
{
	if (tcsetattr(0, TCSANOW, &Prompt::default_settings))
		Error("Prompt::signalHandler(int sig)").print();
	std::_Exit(128 + sig);
}

//	Sets all signal handler to Prompt::signalHandler
int	Prompt::setSignals(void)
{
	int	i;
	
	for (i = 1; i < 32; ++i)
		if (i != SIGKILL && i != SIGSTOP && sigaction(i, &this->signal_settings, 0))
			return (-1);
	return (0);
}

//	Sets all signal handlers to default
void	Prompt::unsetSignals(void)
{
	struct sigaction	def;
	int					i;

	def.sa_handler = SIG_DFL;
	for (i = 1; i < 32; ++i)
		if (i != SIGKILL && i != SIGSTOP && sigaction(i, &def, 0))
			Error("Prompt::unsetSignals(void)").print();
}

//	Copy constructor
Prompt::Prompt(Prompt const &cpy):
	input_settings(cpy.input_settings),
	signal_settings(cpy.signal_settings),
	esc(cpy.esc),
	str(cpy.str),
	c(cpy.c),
	cursor(cpy.cursor)
{
	Prompt::instances++;
}

//	Destructor, reverts all changes to terminal and signal settings
Prompt::~Prompt(void)
{
	Prompt::instances--;
	if (!Prompt::instances)
	{
		if (tcsetattr(0, TCSANOW, &Prompt::default_settings))
			Error("Prompt::~Prompt(void)").print();
		this->unsetSignals();
	}
}

//	Assignment operator
Prompt	&Prompt::operator=(Prompt const &cpy)
{
	this->input_settings = cpy.input_settings;
	this->signal_settings = cpy.signal_settings;
	this->esc = cpy.esc;
	this->str = cpy.str;
	this->c = cpy.c;
	this->cursor = cpy.cursor;
	return (*this);
}

//	String getter
std::string const	&Prompt::get(void)
{
	return (this->str);
}

//	Once the object is created, this methods properly prompts for input
std::string const	&Prompt::input(void)
{
	size_t	i;

	this->str.clear();
	do {
		this->c = std::cin.get();
		if (this->c == 033 || this->esc.size())
			this->processEscapeSequence();
		else if (this->c > 037 && this->c < 0177)
		{
			this->str.insert(this->cursor, 1, this->c);
			std::cout << this->str.substr(this->cursor);
			this->cursor++;
			if (this->cursor < this->str.size())
				for (i = 0; i < this->str.size() - this->cursor; ++i)
					std::cout << "\033[D";
		}
		else if (this->c == 0177 && this->cursor)
		{
			std::cout << '\b' << '\40' << '\b';
			this->str.erase(this->cursor - 1, 1);
			this->cursor--;
		}
	} while (this->c != '\n' && this->c != '\0');
	std::cout << this->c;
	return (this->str);
}

//	Deal with escape sequences
void	Prompt::processEscapeSequence(void)
{
	this->esc += this->c;
	if (this->esc.size() < 3)
		return ;
	if (!this->esc.compare("\033[D") && this->cursor)
	{
		std::cout << this->esc;
		this->cursor--;
	}
	else if (!this->esc.compare("\033[C") && this->cursor < this->str.size())
	{
		std::cout << this->esc;
		this->cursor++;
	}
	this->esc.clear();
}
