#include "../streaming_interface.hpp"

class ossilator: public streaming_interface {
	ossilator(frequency f);
protected:
	workUnit compute_workunit(timestamp start_time);
	frequency freq;
};