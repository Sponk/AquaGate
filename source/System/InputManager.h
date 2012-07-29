#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

class IInputCommand
{
public:
	virtual const char* GetKeyName() = 0;
	virtual const char* GetCommandName() = 0;
	virtual void		OnKeyPressed() {}
	virtual void		OnKeyReleased() {}
};

#include <vector>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void RegisterCommand(IInputCommand* command);
	void UnregisterCommand(IInputCommand* command);

	void Update();
private:
	struct commandDef
	{
		enum commandState
		{
			eUp,
			ePressed,
			eDown,
			eReleased,
		};

		IInputCommand*	command;
		commandState	state;
	};

	typedef std::vector<commandDef*>	commandVec;
	typedef commandVec::iterator		commandVecIter;

	commandVec	m_Commands;
};

#endif /*__INPUT_MANAGER_H__*/
