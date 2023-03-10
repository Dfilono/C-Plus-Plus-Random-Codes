 #include <iostream>
 #include <vector>
 #include <sys/ptrace.h>
 #include <sys/wait.h>
 #include <unistd.h>
 #include <sstream>
 
 #include "linenoise.h"
 #include 'debugger.h'

 using namespace minibdg

void debugger::run(){
    int wait_status;
    auto options = 0;
    waitpid(m_pid, &wait_status, options);

    char* line = nullptr;
    while((line = linenoise("minidbg> ")) != nullptr){
        handle_command(line);
        linenoiseHistoryAdd(line);
        linenoiseFree(line);
    }
}

void debugger::handle_command(const std::string& line){
    auto args = split(line, ' ');
    auto command = args[0];

    if (is_prefix(command, "continue")){
        continue_execution();
    }
    else{
        std::cerr << "Unknown command\n";
    }
}

std::vector<std::string> split(const std::string &s, char delimiter){
    std::vector<std::string> out{};
    std::stringstream ss {s};
    std::string item;

    while (std::getline(ss, item, delimiter)){
        out.push_back(item);
    }

    return out;
}

bool is_prefix(const std::string& s, const std::string& of){
    if (s.size() > of.size()) return false;

    return std::equal(s.begin(), s.end(), of.begin());
}

void debugger::continue_execution(){
    ptrace(PTRACE_CONT, m_pid, nullptr, nullptr);

    int wait_status
    auto options = 0;
    waitpid(m_pid, &wait_status, options);
}

int main(int argc, char* argv[]){
    if (argc < 2){
        std::cerr << "Program name not specified";
        return -1;
    }

    auto prog = argv[1];

    auto pid = fork();
    
    if (pid == 0){
        // in child process
        // execute debugee
        ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
        execl(prog, prog, nullptr);
    }
    else if (pid >= 1){
        // parent process
        // execute debugger
        std::cout << "Started debugging process " << pid << "\n";
        debugger dbg{prog, pid};
        dbg.run();
    }
}