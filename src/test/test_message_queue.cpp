#include <cstring>
#include <unistd.h>
#include "catch.hpp"

#include "ServerMessageQueue.h"
#include "ClientMessageQueue.h"

TEST_CASE( "Message Queue", "[msgq]" ) {
    const std::string queue_file = "/bin/bash";
    const char queue_letter = 'A';
    ServerMessageQueue s(queue_file, queue_letter);
    ClientMessageQueue c(queue_file, queue_letter);

    Query query(SELECT, "Juan Perez", "Calle Falsa 123", "0123456789");
    ClientMessage cmsg(getpid(), &query);

    c.push(cmsg);
    ClientMessage* received_msg = s.pop();

    REQUIRE(received_msg->get_mtype() == cmsg.get_mtype());
    //REQUIRE(received_data.query_type == sent_data.query_type);
    //REQUIRE(strcmp(received_data.name,sent_data.name) == 0);
    //REQUIRE(strcmp(received_data.address, sent_data.address) == 0);
    //REQUIRE(strcmp(received_data.phone, sent_data.phone) == 0);
}

