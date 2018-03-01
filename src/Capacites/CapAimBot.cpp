#include "CapAimBot.h"
#include "CapMissile.h"

CapAimBot::CapAimBot()
{
	cooldown_ = 500;
}

void CapAimBot::set_state_autoAim_true(Capacite & capacite)
{
	autoAim_ = true;
}

void CapAimBot::set_state_autoAim_false(Capacite & capacite)
{
	autoAim_ = false;
}
