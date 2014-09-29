#include "includes.h"
#include "KennyLoggins.h"

KennyLoggins::KennyLoggins()
	:output("lyrics.txt", e::ios::app), id(0)
{
	e::string l[] = { 
		"Revvin' up your engine",
		"Listen to her howlin' roar",
		"Metal under tension",
		"Beggin' you to touch and go",

		"Highway to the Danger Zone",
		"Ride into the Danger Zone",

		"Headin' into twilight",
		"Spreadin' out her wings tonight",
		"She got you jumpin' off the deck",
		"And shovin' into overdrive",

		"Highway to the Danger Zone",
		"I'll take you",
		"Right into the Danger Zone",

		"They never say hello to you",
		"Until you get it on the red line overload",
		"You'll never know what you can do",
		"Until you get it up as high as you can go",

		"Out along the edge",
		"Is always where I burn to be",
		"The further on the edge",
		"The hotter the intensity",

		"Highway to the Danger Zone",
		"I'm gonna take you",
		"Right into the Danger Zone",
		"Highway to the Danger Zone",
		"Right into the Danger Zone"
	};
	lyrics = e::vector<e::string>(l, l + 26);
}

KennyLoggins::KennyLoggins(KennyLoggins &&other)
	:output(e::move(other.output))
{

}

void KennyLoggins::Log(e::string msg)
{
	output << lyrics[id++] << e::endl;
	if (id == lyrics.size())
		id = 0;
}