#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelp(
	const AvailabilityMatrix& avail, 
	DailySchedule& sched, 
	const size_t dailyNeed, 
	const size_t maxShifts, 
	vector<int> rtn,
	size_t day, 
	Worker_T worker)
{
	if(day == sched.size()) return true;

	if(day == avail.size()-1) 
	if(worker == dailyNeed) return true;

	if(worker == dailyNeed)
	{
		day++;
		worker = 0;
	}

	for(unsigned int i = 0; i < avail[0].size(); i++)
	{
		if(avail[day][i] && rtn[i]<maxShifts)
		{
			sched[day][worker] = i;
			rtn[i]++;

			if(scheduleHelp(avail, sched, dailyNeed, maxShifts, rtn, day, worker+1))
				return true;

			sched[day][worker] = INVALID_ID;
			rtn[i]--;
		}
	}
	return false;
}

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    
    for(unsigned int i = 0; i < avail.size(); i++)
    {
        vector<Worker_T> sched_;
        for(unsigned int j = 0; j < dailyNeed; j++)
        {
            sched_.push_back(INVALID_ID);
        }
        sched.push_back(sched_);
    }

		vector<int> rtn(avail[0].size(), 0);

		return scheduleHelp(avail, sched, dailyNeed, maxShifts, rtn, 0, 0);




}

