#ifndef MIGRATION_OFFICE_SIGINTHANDLER_H
#define MIGRATION_OFFICE_SIGINTHANDLER_H

#include <signal.h>

#include "src/main/common/signal_handlers/signal_handler/EventHandler.h"

class SIGINTHandler : public EventHandler {

    private:
        sig_atomic_t graceful_quit;

    public:
        SIGINTHandler();
        ~SIGINTHandler() override;
        int handle_signal(int signum) override;
        sig_atomic_t get_graceful_quit() const;

};


#endif //MIGRATION_OFFICE_SIGINTHANDLER_H
