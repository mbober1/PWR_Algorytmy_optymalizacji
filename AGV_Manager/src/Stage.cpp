#include "inc/Stage.hpp"

Stage::Stage(const char * filename_warehouse, const char* filename_tasks, vehicle_num option)
{
    this->Warehouse_object= read_from_file(filename_warehouse);
    this->read_tasks_from_file(filename_tasks);
    this->add_vehicles(option);
}

void Stage::print_info()
{
    /* this->Warehouse_object.print(); */
    for(auto& it: this->AGV_vehicles)
    {
        it.print_info();
    }
}

bool Stage::read_tasks_from_file(const char * filename)
{   
    std::ifstream ReadFile(filename);
    if(!ReadFile.is_open())
    {
        std::cerr << "Stage::read_tasks_from_file: Problem with file opening \n";
        return false;
    }

    this->tasks_to_do.clear();
    Task temp_task;

    while(ReadFile >> temp_task.task_id && ReadFile >> temp_task.target)
    {
        this->tasks_to_do.push_back(temp_task);
    }

    ReadFile.close();

    return true;
}


void Stage::add_vehicles(vehicle_num option)
{
    for(auto i = 0; i < option; i++)
    {
        AGV temp_object(i, STAR_POSITION);
        AGV_vehicles.push_back(std::move(temp_object));
    }
}

void Stage::add_task_to_vehicle(int AGV_id)
{
    if(tasks_to_do.empty())
    {
        return;
    }
    else
    {
        if(! AGV_vehicles[AGV_id].return_status())
        {

            Task temp_task = tasks_to_do.front();
            std::list<int> temp_path=std::move(Warehouse_object.compute_path_Dijkstra(AGV_vehicles[AGV_id].return_current_pos(),temp_task.target));
            tasks_to_do.pop_front();

            if(!temp_path.empty())
                AGV_vehicles[AGV_id].add_task(temp_task,temp_path);

        }
        
    }
}

void Stage::make_moves()
{
    for(auto& it: this->AGV_vehicles)
    {
        if(it.return_status())
        {
            it.make_move();
        }
    }
}



std::vector<int> Stage::return_current_positions()
{
    std::vector<int> current_pos;

    for(auto& it: this->AGV_vehicles)
    {
        current_pos.push_back(it.return_current_pos());
    }

    return current_pos;
}

int Stage::return_current_position(int AGV_id) 
{
    return AGV_vehicles[AGV_id].return_current_pos();
}

std::list<int> Stage::return_path(int AGV_id) 
{
    return AGV_vehicles[AGV_id].return_path();
}


std::vector<std::list<int>> Stage::return_paths()
{
    std::vector<std::list<int>> paths;

    for(auto& it: this->AGV_vehicles)
    {
        paths.push_back(it.return_path());
    }

    return paths;

}


std::vector<int> Stage::free_AGVs()
{
    std::vector<int> AGVs;

    for(auto& it: this->AGV_vehicles)
    {
        if(! it.return_status())
        {
            AGVs.push_back(it.return_id());
        }
    } 

    return AGVs;
}


bool Stage::AGV_in_use(int AGV_id)
{
    return AGV_vehicles[AGV_id].return_status();
}


float Stage::return_task_percent(int AGV_id)
{
    if(AGV_id > this->AGV_vehicles.size())
    {
        std::cout << "Stage::return_task_percent:  given ID is greater than the number of vehicles " << std::endl;
        exit(1);
    }
    return this->AGV_vehicles[AGV_id].return_task_percent();
}


int Stage::return_task_id(int AGV_id)
{
    if(AGV_id > this->AGV_vehicles.size())
    {
        std::cout << "Stage::return_task_percent:  given ID is greater than the number of vehicles " << std::endl;
        exit(1);
    }
    return this->AGV_vehicles[AGV_id].return_task_id();
}