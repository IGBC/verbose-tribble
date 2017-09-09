#ifndef BLOCKS_HPP
#define BLOCKS_HPP
#include "../streaming_interface.hpp"

class ossilator: public streaming_interface {
public:
	ossilator(frequency f);
protected:
	workUnit compute_workunit(timestamp start_time);
	frequency freq;
};
#endif