#include "InputManager.h"

#include <MEngine.h>

InputManager::InputManager()
{
}
InputManager::~InputManager()
{
	for(commandVecIter iCommand = m_Commands.begin(); 
		iCommand != m_Commands.end(); 
		iCommand++)
	{
		delete *iCommand;
	}
	m_Commands.clear();
}
void InputManager::RegisterCommand(IInputCommand* command)
{
	for(commandVecIter iCommand = m_Commands.begin(); 
		iCommand != m_Commands.end(); 
		iCommand++)
	{
		// this command is already registered
		if((*iCommand)->command == command)
			return;
	}
	commandDef* newCommand = new commandDef;
	newCommand->command = command;
	newCommand->state = commandDef::eUp;
	m_Commands.push_back(newCommand);
}
void InputManager::UnregisterCommand(IInputCommand* command)
{
	for(commandVecIter iCommand = m_Commands.begin(); 
		iCommand != m_Commands.end(); 
		iCommand++)
	{
		if((*iCommand)->command == command)
		{
			delete *iCommand;
			m_Commands.erase(iCommand);
			return;
		}
	}
}
void InputManager::Update()
{
	MEngine* engine = MEngine::getInstance();
	
	if(MInputContext* input = engine->getInputContext())
	{
		for(commandVecIter iCommand = m_Commands.begin(); 
			iCommand != m_Commands.end(); 
			iCommand++)
		{
			commandDef::commandState state = (*iCommand)->state;
			if(input->isKeyPressed((*iCommand)->command->GetKeyName()))
			{
				switch(state)
				{
				case commandDef::eUp:
				case commandDef::eReleased:
					(*iCommand)->command->OnKeyPressed();
					(*iCommand)->state = commandDef::ePressed;
					break;
				case commandDef::ePressed:
				case commandDef::eDown:
					(*iCommand)->state = commandDef::eDown;
					break;
				}
			}
			else
			{
				switch(state)
				{
				case commandDef::eUp:
				case commandDef::eReleased:
					(*iCommand)->state = commandDef::eUp;
					break;
				case commandDef::ePressed:
				case commandDef::eDown:
					(*iCommand)->command->OnKeyReleased();
					(*iCommand)->state = commandDef::eReleased;
					break;
				}
			}
		}
	}
}