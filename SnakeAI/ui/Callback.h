#pragma once
template <class Owner>
struct Callback {
	Owner owner = null;
	void(Owner::*func)(void);
};