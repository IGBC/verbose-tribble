#ifndef STREAMING_INTERFACE_HPP
#define STREAMING_INTERFACE_HPP
#include "audiotypes.h"

#define WORKUNIT 4096 //Number of samples forming a work unit.

struct {
	timestamp start_time;
	sample samples[WORKUNIT];
} typedef workUnit;

class streaming_interface {
public:
	streaming_interface();
	~streaming_interface();

	workUnit getNextWorkUnit();

	workUnit getWorkUnit(timestamp t);

protected:
	virtual workUnit compute_workunit(timestamp start_time)=0;

private:
	timestamp current_t = 0;
};
#endif