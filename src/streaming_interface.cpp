#include "streaming_interface.hpp"

streaming_interface::streaming_interface(){
	//RAII
}

streaming_interface::~streaming_interface(){
	//RDID
}

workUnit streaming_interface::getNextWorkUnit(){
	compute_workunit(current_t);
	current_t += WORKUNIT;
}

workUnit streaming_interface::getWorkUnit(timestamp t){
	compute_workunit(t);
}
