set(NAME combined_ob)
project(${NAME})
add_compile_definitions(CCAPI_ENABLE_SERVICE_MARKET_DATA)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_BINANCE)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_BINANCE_USDS_FUTURES)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_BINANCE_COIN_FUTURES)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_BITMEX)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_KRAKEN)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_KRAKEN_FUTURES)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_OKX)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_GEMINI)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_COINBASE)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_BYBIT)
add_compile_definitions(CCAPI_ENABLE_EXCHANGE_DERIBIT)


add_executable(${NAME} main.cpp)
add_dependencies(${NAME} boost rapidjson)