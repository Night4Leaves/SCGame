#include "TextDisplayLayer.h"

TextDisplayLayer::TextDisplayLayer()
{
}

TextDisplayLayer::~TextDisplayLayer()
{
}

bool TextDisplayLayer::init()
{
	do {
		CC_BREAK_IF(!Layer::init());

		return true;
	} while (0);

	log("TextDisplayLayer initialize failed!");

	return false;
}
