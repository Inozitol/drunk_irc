#include "stack.h"

//--------------------//
//tempStack
//--------------------//

temp_stack::temp_stack(){
    top = NULL;
    depth_counter = 0;
}

void temp_stack::push(std::string input){
    if(top == NULL){
        top = new temp_stack_part;
        top -> param = input;
        top -> next = NULL;
    }
    else{
        temp_stack_part *nextPart = new temp_stack_part;
        nextPart -> param = input;
        nextPart -> next = top;
        top = nextPart;
    }
    depth_counter++;
}

std::string temp_stack::pop(){
    temp_stack_part *holder;
    std::string output = top -> param;

    holder = top;
    top = top -> next;
    delete(holder);

    return(output);
}

//--------------------//
//--------------------//
//--------------------//


//--------------------//
//permStack
//--------------------//

perm_stack::perm_stack(){
    top = NULL;
    depth_counter = 0;
}

void perm_stack::push(std::string name,std::string address, int16_t port, std::string nick){
    if(top == NULL){
        top = new perm_stack_part;
        top -> address.index = depth_counter;
        top -> address.name = name.c_str();
        top -> address.address = address.c_str();
        top -> address.port = port;
        top -> address.nick = nick.c_str();
        top -> next = NULL;
    }
    else{
        perm_stack_part *nextPart = new perm_stack_part;
        nextPart -> address.index = depth_counter;
        nextPart -> address.name = name.c_str();
        nextPart -> address.address = address.c_str();
        nextPart -> address.port = port;
        nextPart -> address.nick = nick.c_str();
        nextPart -> next = top;
        top = nextPart;
    }
    depth_counter++;
}

serverAddress perm_stack::pop(){
    perm_stack_part *holder;
    serverAddress output = top -> address;

    holder = top;
    top = top -> next;
    delete(holder);

    return(output);
}

serverAddress perm_stack::read(int index){
    perm_stack_part *reader = top;

        //THIS SHIT IS HORRIBLE, I FEEL HORRIBLE.
        //WHY DOES THIS GIVE SEGMENTATION FAULT ?
        //...
        //SHOULD I KILL MY SELF ?
        //...
        //NAAH
        //1 DAY LATER
        //ITS GONE! FINALLY!

    while(reader -> next != NULL){
        if(reader -> address.index == index){
            return reader -> address;
        }
        else{
            reader = reader -> next;
        }
    }
    //I know this shit underneath is really nasty. Don't judge me, I have no energy for this shit.
    return reader -> address;

}

BOOL perm_stack::del_index(int index){
    perm_stack_part *holder = top;
    perm_stack_part *deleter;

    std::ifstream file;
    file.open("serverlist.txt",std::ios::in);
    if(file){
        int num_line = depth_counter;
        if(num_line < index){
            std::cout << "No line to delete.";
            return -1;
        }
        std::ofstream outfile;
        outfile.open("temp.txt",std::ios::out);
        char data;
        int line_num = 0;
        while(file.get(data)){
            if(line_num != index) outfile << data;
            if(data == '\n') line_num++;
        }
        outfile.close();
        file.close();

        std::remove("serverlist.txt");

        std::rename("temp.txt","serverlist.txt");
    }

    if(holder -> address.index == index){
        top = holder -> next;
        delete(holder);
        return 1;
    }
    else{
        do{
            if(holder -> next -> address.index == index){
                holder -> address.index--;
                deleter = holder -> next;
                holder -> next = deleter -> next;
                delete(deleter);
                return 1;
            }
            holder -> address.index--;
            holder = holder -> next;
        }
        while(holder -> next != NULL);
    }
    return -1;
}

//--------------------//
//--------------------//
//--------------------//
