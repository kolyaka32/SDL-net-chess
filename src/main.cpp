#include "data/data.hpp"
#include "selectCycle.hpp"
#include "workCodes.hpp"

// Main process data
Data data;

// Main function
int main(int argv, char **args){

    // Starting selecting cycle
    SelectCycle cycle;
    cycle.run();

    // Reloading game
    if(data.restart){
        data.restart = false;
        return main(argv, args);
    };

    // Finishing main process
	return NOR_WOR;
};
