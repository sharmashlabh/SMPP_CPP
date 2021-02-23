/*
 * Copyright (C) 2014 OnlineCity
 * Licensed under the MIT license, which can be read at: http://www.opensource.org/licenses/mit-license.php
 */
#ifndef SMPPCLIENT_TEST_H_
#define SMPPCLIENT_TEST_H_
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <memory>
#include "gtest/gtest.h"
#include "connectionsetting.h"
#include "smpp/smppclient.h"

class SmppClientTest: public testing::Test {
public:
    boost::asio::ip::tcp::endpoint endpoint;
    boost::asio::io_service ios;
    std::shared_ptr<boost::asio::ip::tcp::socket> socket;
    std::shared_ptr<smpp::SmppClient> client;

    SmppClientTest() :
            client(std::shared_ptr<smpp::SmppClient>(new smpp::SmppClient(socket))) {

boost::asio::io_service io_service;
boost::asio::ip::tcp::resolver resolver(io_service);
boost::asio::ip::tcp::resolver::query query(SMPP_HOST, SMPP_PORT);
boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
endpoint = iter->endpoint();

    socket = std::make_shared<boost::asio::ip::tcp::socket>(ios);
    client = std::make_shared<smpp::SmppClient>(socket);
    }

    virtual void SetUp() {
        client->setVerbose(false);
    }

    virtual void TearDown() {
        if (client->isBound()) {
            client->unbind();
        }
        socket->close();
    }
};
#endif  // SMPPCLIENT_TEST_H_
