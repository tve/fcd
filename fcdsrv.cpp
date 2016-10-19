/*
  fcdsrv.cpp - let clients control funcubedongles via websocket connections

*/
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>

extern "C"
{
#include "libfcd.h"
}

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef server::message_ptr message_ptr;

// Define a callback to handle incoming messages
void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {

  std::string payload = msg->get_payload();

  // check for a special command to instruct the server to stop listening so
  // it can be cleanly exited.
  if (payload == "stop-listening") {
    s->stop_listening();
    s->close(hdl, 0, "");
    return;
  }

  std::string reply;

  try {
    rapidjson::Document d;
    d.Parse(payload.c_str());
    rapidjson::Value::MemberIterator freq = d.FindMember("freqMHz");
    if (freq == d.MemberEnd()) throw std::runtime_error("missing 'freqMHz' field");
    if (! freq->value.IsDouble()) throw std::runtime_error("invalid 'freqMHz' field - must be a double");
    double f = d["freqMHz"].GetDouble();
    if (f < 1.0 || f > 1100) throw std::runtime_error("freqMHz must be in the range [1.0, 1100]");
    
    // look for a funcubedongle, get sampling rate and firmware version,
    // and set the frequency.
    fcdDesc fcd;
    int enumNum = 0;
    uint8_t busNum = 0;
    uint8_t devNum = 0;
    uint32_t actualFreq = 0;

    if (FCD_RETCODE_OKAY != fcdOpen(&fcd, enumNum, busNum, devNum, 0)) {
      throw std::runtime_error("noFCD");
    }
    unsigned char fwversion[128];
    if (FCD_RETCODE_OKAY != fcdGetFwVerStrExt(&fcd, fwversion, 128)) {
      fcdClose(&fcd);
      throw std::runtime_error("noFirmwareVersion");
    }
    if (FCD_RETCODE_OKAY != fcdAppSetFreq(&fcd, f * 1e6, (uint32_t *)&actualFreq)) {
      fcdClose(&fcd);
      throw std::runtime_error(std::string("freqSetFailure"));
    }
    /* this is a pain in the ass library to use
    rapidjson::Document json_reply;
    rapidjson::Value afreq(actualFreq / 1000.0);
    json_reply.AddMember("MHz", afreq, json_reply.GetAllocator());
    rapidjson::Value model; model.SetString(fcd.pszModelName, strlen(fcd.pszModelName));
    json_reply.AddMember("model", model, json_reply.GetAllocator()); //, strlen((const char *)fcd.pszModelName));
    rapidjson::Value version; version.SetString(fwversion, strlen(fwversion)));
    json_reply.AddMember("firmware", version, json_reply.GetAllocator()); //.SetString((const char *)fwversion, strlen((const char *)fwversion));
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    json_reply.Accept(writer);
    reply = buffer.GetString();
    */
    std::string fw((char *)fwversion);
    int rate = 96000;
    if (0 == fw.compare("FUNcube Dongle V0.0BL")) 
      rate = 0;
    else if (0 == fw.compare("FUNcube Dongle V2.034"))
      rate = 48000;
    else if (0 == fw.compare("FUNcube Dongle V1.0  "))
      rate = 96000;
    else if (0 == fw.compare("FUNcube Dongle V2.039"))
      rate = 96000;
    else if (0 == fw.compare("FUNcube Dongle V2.0  "))
      rate = 192000;

    reply = "{\"error\":\"\",\"freqMHz\":" + std::to_string(actualFreq / 1e6) + ",\"model\":\"" + std::string(fcd.pszModelName) + "\",\"firmware\":\"" + fw + "\", \"sampRate\":" + std::to_string(rate) + "}";
    fcdClose(&fcd);
  } catch (std::runtime_error e) {
    reply = "{\"error\":\"" + std::string(e.what()) + "\"}";
  }
  try {
    s->send(hdl, reply, msg->get_opcode());
  } catch (const websocketpp::lib::error_code& e) {
    std::cout << "Echo failed because: " << e
              << "(" << e.message() << ")" << std::endl;
  }
};

int main() {
  // Create a server endpoint
  server fcd_server;

  try {
    // Set logging settings
    fcd_server.set_access_channels(websocketpp::log::alevel::all);
    fcd_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

    // Initialize Asio
    fcd_server.init_asio();

    // Register our message handler
    fcd_server.set_message_handler(bind(&on_message, &fcd_server, ::_1, ::_2));

    // Listen on port 9002
    fcd_server.listen(boost::asio::ip::tcp::v4(), 9002);

    // Start the server accept loop
    fcd_server.start_accept();

    // Start the ASIO io_service run loop
    fcd_server.run();
  } catch (websocketpp::exception const & e) {
    std::cout << e.what() << std::endl;
  } catch (...) {
    std::cout << "other exception" << std::endl;
  }
}
