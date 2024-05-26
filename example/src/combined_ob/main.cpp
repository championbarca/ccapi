#include <string>
#include <iostream>
#include "ccapi_cpp/ccapi_session.h"

namespace ccapi {
Logger* Logger::logger = nullptr;  // This line is needed.
class MyEventHandler : public EventHandler {
 public:
  bool processEvent(const Event& event, Session* session) override {
    if (event.getType() == Event::Type::SUBSCRIPTION_STATUS) {
      
      std::cout << "Received an event of type SUBSCRIPTION_STATUS:\n" + event.toStringPretty(2, 2) << std::endl;
    } else if (event.getType() == Event::Type::SUBSCRIPTION_DATA) {
      for (const auto& message : event.getMessageList()) {
        std::cout << std::string("Best bid and ask at ") + UtilTime::getISOTimestamp(message.getTime()) + " are:" << std::endl;
        for (const auto& element : message.getElementList()) {
          const std::map<std::string, std::string>& elementNameValueMap = element.getNameValueMap();
          for (const auto& x : elementNameValueMap) {
            std::cout << x.first << " : " << x.second << std::endl;
          }
        }
      }
    }
    else if (event.getType() == Event::Type::SESSION_STATUS) {
        // std::cout << "Received an event of type SESSION_STATUS:\n" + event.toString() << std::endl;
        for (const auto& message : event.getMessageList()) {
            for (const auto& element : message.getElementList()) {
                const std::map<std::string, std::string>& elementNameValueMap = element.getNameValueMap();
                for (const auto& x : elementNameValueMap) {
                  std::cout << x.first << " : " << x.second << std::endl;
                }
            }
        }
    }
    else {
      std::cerr << "Not handled event: " + event.toString() << std::endl;
    }
    return true;
  }
};
} /* namespace ccapi */
using ::ccapi::MyEventHandler;
using ::ccapi::Session;
using ::ccapi::SessionConfigs;
using ::ccapi::SessionOptions;
using ::ccapi::Subscription;
using ::ccapi::toString;
int main(int argc, char** argv) {
  SessionOptions sessionOptions;
  SessionConfigs sessionConfigs;
  MyEventHandler eventHandler;
  Session session(sessionOptions, sessionConfigs, &eventHandler);
  Subscription subscription1(CCAPI_EXCHANGE_NAME_KRAKEN, "BTCUSDT", CCAPI_MARKET_DEPTH, "MARKET_DEPTH_MAX=20");
  session.subscribe(subscription1);
  Subscription subscription2(CCAPI_EXCHANGE_NAME_BINANCE, "BTCUSDT", CCAPI_MARKET_DEPTH, "MARKET_DEPTH_MAX=20");
  session.subscribe(subscription2);
//   Subscription subscription3(CCAPI_EXCHANGE_NAME_BINANCE_COIN_FUTURES, "BTC-USDT", CCAPI_MARKET_DEPTH);
//   session.subscribe(subscription3);
//   Subscription subscription4(CCAPI_EXCHANGE_NAME_GEMINI, "BTC-USDT", CCAPI_MARKET_DEPTH);
//   session.subscribe(subscription4);
//   Subscription subscription5(CCAPI_EXCHANGE_NAME_BYBIT, "BTC-USDT", CCAPI_MARKET_DEPTH);
//   session.subscribe(subscription5);
//   Subscription subscription6(CCAPI_EXCHANGE_NAME_DERIBIT, "BTC-USDT", CCAPI_MARKET_DEPTH);
//   session.subscribe(subscription6);
//   Subscription subscription7(CCAPI_EXCHANGE_NAME_BITMEX, "BTC-USDT", CCAPI_MARKET_DEPTH);
//   session.subscribe(subscription7);
//   Subscription subscription8(CCAPI_EXCHANGE_NAME_OKX, "BTC-USDT", CCAPI_MARKET_DEPTH);
//   session.subscribe(subscription8);
//   Subscription subscription9(CCAPI_EXCHANGE_NAME_COINBASE, "BTC-USDT", CCAPI_MARKET_DEPTH);
//   session.subscribe(subscription9);

  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Press enter to stop" << std::endl;
    if (std::cin.get() == '\n') {
      break;
    }
  }
  session.stop();
  std::cout << "Bye" << std::endl;
  return EXIT_SUCCESS;
}