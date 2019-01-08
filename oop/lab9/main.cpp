#include <cstdlib>
#include <iostream>
#include <memory>
#include <future>
#include <functional>
#include <random>
#include <thread>


#include "triangle.h"
#include "ttree.h"
#include "list.h"
#include "cri_val.h"
#include "cri_all.h"
typedef std::function<void(void)> command;

int main(int argc, char** argv) {

    
    TTree <command> tree_cmd;
	TList<Triangle> list;
	
    command cmd_insert = [&]() {
        std::cout << "Command: Create triangles" << std::endl;
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(1, 1000);

        for (int i = 0; i < 10; i++) {
            int side = distribution(generator);
            list.addRight(std::shared_ptr<Triangle> (new Triangle(side, side, side)));
        }
    };

    command cmd_print = [&]() {
        std::cout << "Command: Print list" << std::endl;
        std::cout << list;
    };

	command cmd_reverse = [&]() {
        std::cout << "Command: Reverse list" << std::endl;
        
        TList<Triangle> list_tmp;
        while(!list.empty()) list_tmp.addRight(list.del());
        while(!list_tmp.empty()) list.addRight(list_tmp.del());
    };

    tree_cmd.insert(&cmd_insert);
	tree_cmd.insert(&cmd_print);
    tree_cmd.insert(&cmd_reverse);
	tree_cmd.insert(&cmd_print); 
	
	
	while (!tree_cmd.empty()) {
        command* cmd = tree_cmd.pop();
        std::future<void> ft = std::async(*cmd);      
        ft.get();
        //std::thread(*cmd).detach();
    }
   
   
}
/*
    tree_cmd.insert(std::shared_ptr<command> (&cmd_print, [](command*) {
    })); // using custom deleter
    tree_cmd.insert(std::shared_ptr<command> (&cmd_reverse, [](command*) {
    })); // using custom deleter
    tree_cmd.insert(std::shared_ptr<command> (&cmd_print, [](command*) {
    })); // using custom deleter
    tree_cmd.insert(std::shared_ptr<command> (&cmd_insert, [](command*) {
    })); // using custom deleter
*/
