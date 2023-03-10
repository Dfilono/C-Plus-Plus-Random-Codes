#ifndef MINIDBG_DEBUGGER_H
#define MINIDBG_DEBUGGER_H

#include <utility>
#include <string>
#include <linux/types.h>
#include <unordered_map>

#include "breakpoint.h"

namespace minidbg{
    class debugger{
        public:
            debugger (std::string prog_name, pid_t pid)
                : m_prog_name{std::move(prog_name)}, m_pid{pid} {}

            void run();

        private:
            void handle_command(const std::string& line);
            void continue_execution();

            std::string m_prog_name;
            pid_t m_pid;
    };
}

#endif