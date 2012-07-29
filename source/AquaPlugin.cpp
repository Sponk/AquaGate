/* AquaPlugin.cpp
  version 0.0.1, February 12th, 2012

  Copyright (C) 2012 Philipp Geyer

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Philipp Geyer
*/

// Standard include
#include "AquaPlugin.h"

// Project includes
#include "PenguinController.h"
#include "AquaGame.h"

// System includes

// static games.
MGame* s_prevGame = NULL;
AquaGame* s_tutGame = NULL;

void StartPlugin()
{
	MEngine* engine = MEngine::getInstance();
	// just cache the previous game, shouldn't need to, but just in case
	s_prevGame = engine->getGame();
	s_tutGame = new AquaGame;
	engine->setGame(s_tutGame);
}

void EndPlugin()
{
	// check that the game we're removing is ourself
	MEngine* engine = MEngine::getInstance();
	if(engine->getGame() == s_tutGame)
		engine->setGame(s_prevGame);
	// delete me
	SAFE_DELETE(s_tutGame);
}
