#include "Action.h"

using namespace state;

Action::Action()
{
}

ActionType Action::GetActionType ()
{
	return(ActionType::_INITIALISATION);
}
