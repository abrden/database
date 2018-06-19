#include <cstring>
#include <unistd.h>
#include <src/main/common/entities/Query.h>
#include "ClientMessage.h"
#include "Query.h"
#include "catch.hpp"

#include "MessageQueue.h"
#include "ServerMessageQueue.h"
#include "ClientMessageQueue.h"


typedef struct {
    long mtype;
    QueryData data[2];
} TestMessage;

TEST_CASE( "Message queue", "[msgq]" ) {
    const std::string queue_file = "/bin/bash";
    const char queue_letter = 'A';

    SECTION("Client message") {
        ServerMessageQueue s(queue_file, queue_letter);
        ClientMessageQueue c(queue_file, queue_letter);
        Query query(SELECT, "Juan Perez", "Calle Falsa 123", "0123456789");
        ClientMessage cmsg(getpid(), query);
        QueryData expected_query_data = cmsg.serialize().data;

        c.push(cmsg);
        ClientMessage received_msg = s.pop();

        QueryData received_query_data = received_msg.serialize().data;

        REQUIRE(received_msg.get_mtype() == cmsg.get_mtype());
        REQUIRE(received_query_data.operation == expected_query_data.operation);
        REQUIRE(strcmp(received_query_data.name,expected_query_data.name) == 0);
        REQUIRE(strcmp(received_query_data.address, expected_query_data.address) == 0);
        REQUIRE(strcmp(received_query_data.phone, expected_query_data.phone) == 0);
    }

    SECTION("Server message") {
        // TODO refactor this
        MessageQueue queue;
        queue.create(queue_file, queue_letter);

        Query query(SELECT, "Juan Perez", "Calle Falsa 123", "0123456789");
        Query query2(SELECT, "Esteban Quito", "Nazca 500", "911");
        QueryData data[] = {query.serialize(), query2.serialize()};

        TestMessage msg;
        memset(&msg, 0, sizeof(TestMessage));
        msg.mtype = 1;
        memcpy(msg.data, data, sizeof(QueryData) * 2);

        queue.push(&msg, sizeof(TestMessage));
        TestMessage received_msg;
        queue.pop(&received_msg, 0, sizeof(TestMessage));

        REQUIRE(received_msg.mtype == msg.mtype);
        REQUIRE(received_msg.data[0].operation == msg.data[0].operation);
        REQUIRE(strcmp(received_msg.data[0].name, msg.data[0].name) == 0);
        REQUIRE(strcmp(received_msg.data[0].address, msg.data[0].address) == 0);
        REQUIRE(strcmp(received_msg.data[0].phone, msg.data[0].phone) == 0);

        queue.destroy();
    }
}

