#include <iostream>
#include <chrono>
#include <exception>
#include <string>

#include "Hotel.h"
#include "StandardRoom.h"
#include "FamilyRoom.h"
#include "LuxuryRoom.h"
#include "Reservation.h"
#include "Guest.h"
#include "AutomatedTest.h"
#include "ConsoleUI.h"

int main() {
	Hotel hotel;
	ConsoleUI ui;
	ui.run(hotel);
	return 0;
}