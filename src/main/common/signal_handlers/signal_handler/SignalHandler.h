#ifndef MIGRATION_OFFICE_SIGNALHANDLER_H
#define MIGRATION_OFFICE_SIGNALHANDLER_H

#include <signal.h>
#include <stdio.h>
#include <memory.h>

#include "src/main/common/signal_handlers/signal_handler/EventHandler.h"

class SignalHandler {

    private:
        static SignalHandler* instance;
        static EventHandler* signal_handlers[NSIG];

        SignalHandler();
        static void dispatcher(int signum);

    public:
        static SignalHandler* get_instance();
        static void destroy();
        EventHandler* register_handler(int signum, EventHandler* eh);
        int remove_handler(int signum);

};

#endif /* MIGRATION_OFFICE_SIGNALHANDLER_H */
