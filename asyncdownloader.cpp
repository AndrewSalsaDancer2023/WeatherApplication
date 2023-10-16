#include "asyncdownloader.h"
#include <boost/lexical_cast.hpp>

void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

void asyncDownloader::run(char const* host, char const* port, char const* target,
                          int version, std::function<void(std::string)> callback)
{
    callback_ = callback;
    // Set up an HTTP GET request message
    req_.version(version);
    req_.method(http::verb::get);
    req_.target(target);
    req_.set(http::field::host, host);
    req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // Look up the domain name
        resolver_.async_resolve( host, port,
            beast::bind_front_handler( &asyncDownloader::on_resolve, shared_from_this()));
}

void asyncDownloader::on_resolve(beast::error_code ec, tcp::resolver::results_type results)
{
        if(ec)
            fail(ec, "resolve");

        // Set a timeout on the operation
        stream_.expires_after(std::chrono::seconds(30));

        // Make the connection on the IP address we get from a lookup
        stream_.async_connect(results,
            beast::bind_front_handler(&asyncDownloader::on_connect, shared_from_this()));
}

void asyncDownloader::on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
{
    if(ec)
        fail(ec, "connect");

    // Set a timeout on the operation
    stream_.expires_after(std::chrono::seconds(30));

    // Send the HTTP request to the remote host
    http::async_write(stream_, req_,
            beast::bind_front_handler(&asyncDownloader::on_write, shared_from_this()));
}

void asyncDownloader::on_write(beast::error_code ec, std::size_t bytes_transferred)
   {
       boost::ignore_unused(bytes_transferred);

       if(ec)
           fail(ec, "write");

       // Receive the HTTP response
       http::async_read(stream_, buffer_, res_,
           beast::bind_front_handler(&asyncDownloader::on_read, shared_from_this()));
   }

   void asyncDownloader::on_read(beast::error_code ec, std::size_t bytes_transferred)
   {
       boost::ignore_unused(bytes_transferred);

       if(ec)
           fail(ec, "read");

       // Write the message to standard out
    //   std::cout << res_ << std::endl;
       if(callback_)
       {
           auto strHeaders =
                       boost::lexical_cast<std::string>(res_.body());
           //auto responce = boost::beast::buffers_to_string(res_.body().data());
           callback_(std::move(strHeaders));
       }
       // Gracefully close the socket
       stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

       // not_connected happens sometimes so don't bother reporting it.
       if(ec && ec != beast::errc::not_connected)
           fail(ec, "shutdown");

       // If we get here then the connection is closed gracefully
   }


