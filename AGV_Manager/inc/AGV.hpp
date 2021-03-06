#pragma once

#include "Warehouse.hpp"
#include "Task.hpp"

/*
 * Definition of AGV class that represents AGV vehicle 
 */
class AGV{

int id;  // ID of vehicle
int current_pos; // current position of vehicle
bool in_use;  // does it have task?
unsigned int target; // Point of the warehouse to achieve
std::list<int> path_to_target;  // list including points to the target 
int road_length = 0;  // The length of the road
float task_percent = 0; // task perform percent
int current_task = 0;  // current task id
int home_pos;  // start postion of AGV

public:
AGV() = delete; // to prevent using a default constructor

/*
 * Parametrical  constructor using to set data to AGV object.
 * @param[in] id - using to set id of AGV object
 * @param[in] current_pos - using to set AGV current_pos
 */
AGV(const int id, const int current_pos);


int return_id() {return this->id;} // using to return AGV id
int return_current_pos() {return this->current_pos;}// using to return AGV current_pos
bool return_status() {return this->in_use;} // returns current status of the AGV
float return_task_percent() {return this->task_percent;} // returns current status of the AGV
int return_task_id() {return this->current_task;} // returns current status of the AGV
int return_home_pos() {return this->home_pos;} // returns home position of AGV

void print_info(); // using to print info about AGV object

/*
 * method to set a target and a path, if AGV does not have a task to do
 * @param [in] task_to_assign - task to do 
 * @return true if finished with success (not in use), else false
 */
void add_task(const Task task_to_assign, const std::list<int> path_to_target);


/*
 * method performing move - chainging current position to the next position included in a path to do
 */
void make_move();


std::list<int> return_path() {return this->path_to_target;}


};
