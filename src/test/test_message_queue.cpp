#include <cstring>
#include <unistd.h>
#include "ClientMessage.h"
#include "Query.h"
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
    QueryData expected_query_data = cmsg.serialize().data;

    c.push(cmsg);
    ClientMessage* received_msg = s.pop();

    QueryData received_query_data = received_msg->serialize().data;

    REQUIRE(received_msg->get_mtype() == cmsg.get_mtype());
    REQUIRE(received_query_data.operation == expected_query_data.operation);
    REQUIRE(strcmp(received_query_data.name,expected_query_data.name) == 0);
    REQUIRE(strcmp(received_query_data.address, expected_query_data.address) == 0);
    REQUIRE(strcmp(received_query_data.phone, expected_query_data.phone) == 0);

    delete received_msg;
}

