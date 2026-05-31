#pragma once
#include "Hotel.h"

class ConsoleUI
{
private:
	static bool askRetry();
	static void handleNewGuest(Hotel& hotel);
	static void handleNewReservation(Hotel& hotel);
	static void handleCheckIn(Hotel& hotel);
	static void handleCheckOut(Hotel& hotel);
	static void handleSearch(const Hotel& hotel);
	static void handleLoading(Hotel& hotel);
	static void handleSaving(const Hotel& hotel);
public:
	static void run(Hotel& hotel);
};

