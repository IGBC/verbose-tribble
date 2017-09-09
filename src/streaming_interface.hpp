#include "audiotypes.h"

#define WORKUNIT 4096 //Number of samples forming a work unit.

struct workUnit {
	timestamp start_time;
	sample samples[WORKUNIT];
};

class streaming_interface {
public:
	streaming_interface();
	~streaming_interface();

	workUnit getNextWorkUnit();

	workUnit getWorkUnit(timestamp t);

protected:
	virtual workUnit compute_workunit(timestamp start_time){};

private:
	timestamp current_t = 0;
};