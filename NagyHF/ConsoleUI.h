#pragma once
#include "Hotel.h"

class ConsoleUI
{
private:
	void handleNewGuest(Hotel& hotel);
	void handleNewReservation(Hotel& hotel);
	void handleCheckIn(Hotel& hotel);
	void handleCheckOut(Hotel& hotel);
	void handleSearch(Hotel& hotel);
	void handleLoading(Hotel& hotel);
	void handleSaving(Hotel& hotel);
public:
	void run(Hotel& hotel);
};

