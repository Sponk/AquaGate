/* PlayerControllerStateSwim.cpp
  version 0.0.1, August 1st, 2012

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

/* Changelog
   0.0.1 - 01.08.2012 - First implementation of skeleton Player controller
                        base state. - PG
*/

#include "PlayerControllerStateSwim.h"

#include <stdio.h>

//----------------------------------------
// Commands
//----------------------------------------

void PlayerControllerStateSwim::Enter()
{
    printf("Enter Swim\n");
    PlayerControllerState::Enter();
}

void PlayerControllerStateSwim::Update()
{
    printf("Update Swim\n");
    PlayerControllerState::Update();
}

void PlayerControllerStateSwim::Exit()
{
    printf("Exit Swim\n");
    PlayerControllerState::Update();
}
