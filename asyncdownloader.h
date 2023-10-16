#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class asyncDownloader: public std::enable_shared_from_this<asyncDownloader>
{
public:
    explicit asyncDownloader(net::io_context& ioc)
            : resolver_(net::make_strand(ioc))
            , stream_(net::make_strand(ioc))
        {

        }

    explicit asyncDownloader()
            : resolver_(net::make_strand(_ioc))
            , stream_(net::make_strand(_ioc))
    {}
    void run(char const* host, char const* port, char const* target, int version, std::function<void(std::string)> callback);
    void on_resolve(beast::error_code ec, tcp::resolver::results_type results);
    void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type);
    void on_write(beast::error_code ec, std::size_t bytes_transferred);
    void on_read(beast::error_code ec, std::size_t bytes_transferred);

private:
    net::io_context _ioc;
    tcp::resolver resolver_;
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_; // (Must persist between reads)
    http::request<http::empty_body> req_;
    http::response<http::string_body> res_;
    std::function<void(std::string)> callback_;
};
//https://www.boost.org/doc/libs/master/libs/beast/example/http/client/async/http_client_async.cpp
