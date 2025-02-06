#include "DetailsOverlay.h"

DetailsOverlay& DetailsOverlay::Get() {
	return DetailsOverlay_Instance;
}

void DetailsOverlay::update()
{
}

void DetailsOverlay::render(RenderWindow& window)
{
}

DetailsOverlay DetailsOverlay::DetailsOverlay_Instance;
