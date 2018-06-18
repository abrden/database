#include <src/main/common/definitions/QueryData.h>
#include <cstring>
#include "catch.hpp"

#include "ServerMessageQueue.h"
#include "ClientMessageQueue.h"

TEST_CASE( "Message Queue", "[msgq]" ) {
    const std::string queue_file = "/bin/bash";
    const char queue_letter = 'A';
    ServerMessageQueue s(queue_file, queue_letter);
    ClientMessageQueue c(queue_file, queue_letter);

    QueryData sent_data ;
    memset(&sent_data, 0, sizeof(QueryData));
    sent_data.mtype = 1;
    sent_data.query_type = GET;
    std::string name = "Juan Perez";
    strncpy(sent_data.name, name.c_str(), name.length());
    std::string address = "Calle Falsa 123";
    strncpy(sent_data.address, address.c_str(), address.length());
    std::string phone = "0123456789";
    strncpy(sent_data.phone, phone.c_str(), phone.length());

    c.push(&sent_data);
    QueryData received_data = s.pop();

    REQUIRE(received_data.mtype == sent_data.mtype);
    REQUIRE(received_data.query_type == sent_data.query_type);
    REQUIRE(strcmp(received_data.name,sent_data.name) == 0);
    REQUIRE(strcmp(received_data.address, sent_data.address) == 0);
    REQUIRE(strcmp(received_data.phone, sent_data.phone) == 0);
}

