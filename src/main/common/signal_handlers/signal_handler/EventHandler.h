#ifndef MIGRATION_OFFICE_EVENTHANDLER_H
#define MIGRATION_OFFICE_EVENTHANDLER_H

class EventHandler {
    public:
        virtual int handle_signal(int signum) = 0;
        virtual ~EventHandler() = default;
};

#endif /* MIGRATION_OFFICE_EVENTHANDLER_H */
