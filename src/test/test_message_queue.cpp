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
        ClientMessage* received_msg = s.pop();

        QueryData received_query_data = received_msg->serialize().data;

        REQUIRE(received_msg->get_mtype() == cmsg.get_mtype());
        REQUIRE(received_query_data.operation == expected_query_data.operation);
        REQUIRE(strcmp(received_query_data.data.name,expected_query_data.data.name) == 0);
        REQUIRE(strcmp(received_query_data.data.address, expected_query_data.data.address) == 0);
        REQUIRE(strcmp(received_query_data.data.phone, expected_query_data.data.phone) == 0);

        delete received_msg;
    }

    SECTION("Server message") {
        // TODO refactor this
        MessageQueue queue;
        queue.create(queue_file, queue_letter);

        Query query(SELECT, "Juan Perez", "Calle Falsa 123", "0123456789");
        Query query2(SELECT, "Esteban Quito", "Nazca 500", "911");
        QueryData data[] = {query.serialize(), query2.serialize()};
        TestMessage expected_msg;
        memset(&expected_msg, 0, sizeof(TestMessage));
        expected_msg.mtype = 1;
        memcpy(expected_msg.data, data, sizeof(QueryData) * 2);

        {
            TestMessage sent_msg;
            memset(&sent_msg, 0, sizeof(TestMessage));
            sent_msg.mtype = 1;
            memcpy(sent_msg.data, data, sizeof(QueryData) * 2);
            queue.push(&sent_msg, sizeof(TestMessage)); 
        }
        
        TestMessage received_msg;
        queue.pop(&received_msg, 0, sizeof(TestMessage));

        REQUIRE(received_msg.mtype == expected_msg.mtype);
        REQUIRE(received_msg.data[0].operation == expected_msg.data[0].operation);
        REQUIRE(strcmp(received_msg.data[0].data.name, expected_msg.data[0].data.name) == 0);
        REQUIRE(strcmp(received_msg.data[0].data.address, expected_msg.data[0].data.address) == 0);
        REQUIRE(strcmp(received_msg.data[0].data.phone, expected_msg.data[0].data.phone) == 0);

        queue.destroy();
    }
}

