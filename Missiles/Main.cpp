#include <iostream>
#include <string>


typedef struct position
{
	int x;
	int y;

	void print()
	{
		std::cout << x << y << std::endl;
	}
}Coordinates;

enum WarHead {EXPLOSIVE, NUCLEAR};

typedef struct Enemy
{
	Coordinates coordinates;
	void setCoordinates()
	{
		coordinates.x = 40;
		coordinates.y = 127;
	}
	bool targetHit(int XCoOrd, int YCoOrd)
	{
		if (coordinates.x == XCoOrd && coordinates.y == YCoOrd)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}Target;


struct Missile
{
	WarHead payload;
	Coordinates coordinates;
	Target target;
	int launchCode = 000000;
	bool armed = false;
	void aim(int xpos, int ypos)
	{
		coordinates.x = xpos;
		coordinates.y = ypos;
	}
	void arm(bool arm)
	{
		if (arm == true)
		{
			armed = true;
		}
		else
		{
			armed = false;
		}
	}

	bool chooseWarhead(std::string warhead)
	{
		if (warhead == "nuclear")
		{
			payload = NUCLEAR;
			return true;
		}
		else if (warhead == "explosive")
		{
			payload = EXPLOSIVE;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool launch(int launchcode)
	{
		if (launchCode == launchcode)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void update()
	{
		coordinates.x += 1;
		coordinates.y += 2;
	}
};

int main()
{
	Missile missile;
	Enemy trump;
	std::string payload = " ";
	char again = ' ';
	bool tryAgain = true;
	int xpos = 0;
	int ypos = 0;
	int missileCount = 10;
	bool arm = false;
	bool codeCorrect = false;
	int lauchCode = 0;
	bool payloadChoice = false;
	bool enemyhit = false;
	bool gameOver = false;
	char missarm = ' ';
	trump.setCoordinates();
	std::cout << "Welcome, to the Donald Trump Simulator 2017." << std::endl;
	std::cout << "Your goal is to nuke North Korea." << std::endl;
	std::cout << "You must get the co-ordinates for North Korea (do not use decimals)" << std::endl;
	std::cout << "You have " << missileCount << " missiles" << std::endl;
	std::cout << "Good Luck" << std::endl;
	std::cout << std::endl;
	system("pause");
	system("cls");
	while (!gameOver)
	{
		std::cout << "What warhead do you want, explosive, or nuclear? ";
		std::cin >> payload;
		for (int index = 0; index < payload.length(); index++)
		{
			payload[index] = tolower(payload[index]);
		}
		payloadChoice = missile.chooseWarhead(payload);
		std::cout << std::endl;
		if (!payloadChoice)
		{
			std::cout << "You entered the wrong kind of payload." << std::endl;
			std::cout << "That will cost you a missile, but you survived." << std::endl;
			std::cout << "Try again, and choose an available option." << std::endl;
			std::cout << "(PS. Don't get the launch code wrong)" << std::endl;
			std::cout << std::endl;
			system("pause");
		}
		else if (payloadChoice)
		{
			std::cout << "Enter X co-cordinate for the missile: ";
			std::cin >> xpos;
			std::cout << std::endl;
			std::cout << "Enter Y co-cordinate for the missile: ";
			std::cin >> ypos;
			std::cout << std::endl;
			missile.aim(xpos, ypos);
			std::cout << "Enter launch code (6 digits): ";
			std::cin >> lauchCode;
			codeCorrect = missile.launch(lauchCode);
			std::cout << std::endl;
			if (codeCorrect)
			{
				std::cout << "Do you want to arm missile? Y/N ";
				std::cin >> missarm;
				missarm = toupper(missarm);
				std::cout << std::endl;
				if (missarm == 'N')
				{
					gameOver = true;
					break;
				}
				else if (missarm == 'Y')
				{
					missile.arm(arm);
					std::cout << "armed!" << std::endl;
					std::cout << std::endl;
					std::cout << "Missile lauching....." << std::endl;
					missile.update();
					enemyhit = trump.targetHit(xpos, ypos);
					if (enemyhit)
					{
						std::cout << std::endl;
						std::cout << "Hit!" << std::endl;
						std::cout << std::endl;
						system("pause");
						gameOver = true;
					}
					else
					{
						std::cout << std::endl;
						std::cout << "Miss....." << std::endl;
						std::cout << std::endl;
						system("pause");
					}
				}
			}
			else if (!codeCorrect)
			{
				std::cout << "Error! Launch codes incorrect!" << std::endl;
				gameOver = true;
				std::cout << std::endl;
				system("pause");
				system("cls");
				break;
			}
		}
		system("cls");
		if (!gameOver)
		{
			std::cout << "You did not hit North Korea" << std::endl;
			std::cout << "You made Donad Trump sad" << std::endl;
			std::cout << "Try again? Y/N" << std::endl;
			std::cin >> again;
			again = toupper(again);
			if (again == 'N')
			{
				gameOver = true;
			}
			else
			{
				system("cls");
				missileCount--;
				std::cout << "You have " << missileCount << " missiles left" << std::endl;
				if (missileCount == 0)
				{
					gameOver = true;
				}
			}
		}
	}
	system("cls");
	if (enemyhit && missile.payload == NUCLEAR)
	{
		std::cout << "North Korea is gone." << std::endl;
		std::cout << "You have saved the world (as soon as all the radiation leaves)" << std::endl;
		std::cout << "The cockroaches will be happy" << std::endl;
	}
	else if (enemyhit && missile.payload == EXPLOSIVE)
	{
		std::cout << "North Korea is gone." << std::endl;
		std::cout << "You have saved the world in a non-nuclear way" << std::endl;
		std::cout << "Congratulations" << std::endl;
	}
	else if (!enemyhit && codeCorrect  && missile.armed)
	{
		std::cout << "North Korea is still here." << std::endl;
		std::cout << "You have been nuked out of existance" << std::endl;
		std::cout << "Hard luck Mr. President." << std::endl;
	}
	else if (!enemyhit && !codeCorrect && !missile.armed)
	{
		std::cout << "You entered the wrong launch code." << std::endl;
		std::cout << "You nuked yourself out of existance." << std::endl;
		std::cout << "You blithering idiot." << std::endl;
	}
	else if (!enemyhit && codeCorrect && !missile.armed)
	{
		std::cout << "You cancelled the launch." << std::endl;
		std::cout << "You upset yourself." << std::endl;
		std::cout << "You curl up under your desk and \nlook forward to the end that \nshall soon be coming via nukes from North Korea." << std::endl;
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}