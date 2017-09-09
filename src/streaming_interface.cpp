#include "streaming_interface.hpp"

streaming_interface::streaming_interface(){
	//RAII
}

streaming_interface::~streaming_interface(){
	//RDID
}

workUnit streaming_interface::getNextWorkUnit(){
	workUnit w = compute_workunit(current_t);
	current_t += WORKUNIT;
	return w;
}

workUnit streaming_interface::getWorkUnit(timestamp t){
	return compute_workunit(t);
}
