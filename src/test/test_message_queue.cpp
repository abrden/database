#include <cstring>
#include <unistd.h>
#include <src/main/common/entities/Query.h>
#include "ClientMessage.h"
#include "Query.h"
#include "catch.hpp"

#include "MessageQueue.h"
#include "ServerMessageQueue.h"
#include "ClientMessageQueue.h"

TEST_CASE( "Message queue", "[msgq]" ) {
    const std::string queue_file = "/bin/bash";
    const char queue_letter = 'A';

    SECTION("with a client message") {
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

    SECTION("with a server message") {
        // Setup
        ServerMessageQueue sv_queue(queue_file, queue_letter);
        ClientMessageQueue cl_queue(queue_file, queue_letter);

        Entry* entry_1 = new Entry("Juan Perez", "Calle Falsa 123", "0123456789");
        Entry* entry_2 = new Entry("Esteban Quito", "Nazca 500", "911");
        std::vector<Entry*> entries = { entry_1, entry_2 };

        Response* sent_response = new Response(true, "Test message", QUERY_TYPE::SELECT, entries);
        ServerMessage smsg(1, sent_response);
        ServerMessageData expected_smsg_data = smsg.serialize();

        sv_queue.push(smsg);
        ServerMessage* rcvd_smsg = cl_queue.pop(0);
        ServerMessageData rcvd_smsg_data = rcvd_smsg->serialize();

        // Testing general data
        REQUIRE(rcvd_smsg_data.mtype == expected_smsg_data.mtype);
        REQUIRE(rcvd_smsg_data.data.operation == expected_smsg_data.data.operation);
        REQUIRE(strcmp(rcvd_smsg_data.data.msg, expected_smsg_data.data.msg) == 0);
        REQUIRE(rcvd_smsg_data.data.len_selection == expected_smsg_data.data.len_selection);  

        // Testing entries
        EntryData rcvd_entry_1 = rcvd_smsg_data.data.selection[0];
        EntryData expected_entry_1 = expected_smsg_data.data.selection[0];

        REQUIRE(strcmp(rcvd_entry_1.name, expected_entry_1.name) == 0);
        REQUIRE(strcmp(rcvd_entry_1.address, expected_entry_1.address) == 0);
        REQUIRE(strcmp(rcvd_entry_1.phone, expected_entry_1.phone) == 0);

        EntryData rcvd_entry_2 = rcvd_smsg_data.data.selection[1];
        EntryData expected_entry_2 = expected_smsg_data.data.selection[1];

        REQUIRE(strcmp(rcvd_entry_2.name, expected_entry_2.name) == 0);
        REQUIRE(strcmp(rcvd_entry_2.address, expected_entry_2.address) == 0);
        REQUIRE(strcmp(rcvd_entry_2.phone, expected_entry_2.phone) == 0);

        delete rcvd_smsg;
    }
}

