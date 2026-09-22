/*
 * Copyright (c) 2026-present Thomas Baricault
 *
 * SPDX-License-Identifier: MIT
 */


#include <openssl/ssl.h>

#ifdef _WIN32
#include <winsock2.h>
#endif

#include "sockets/Context.hpp"


namespace tbaricault::sockets
{

    Context::Context()
    {
#ifdef _WIN32
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa))
            return;
#endif
        SSL_load_error_strings();
        OpenSSL_add_ssl_algorithms();
        this->_valid = true;
        return;
    }

    Context::~Context() noexcept
    {
#ifdef _WIN32
        WSACleanup();
#endif
        EVP_cleanup();
        return;
    }

    Context::operator bool() const noexcept
    {
        return (this->_valid);
    }

}
