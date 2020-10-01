#pragma once

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace mtx::responses {

//! Response of the `GET /_matrix/client/r0/voip/turnServer` endpoint.
//
//! This API provides credentials for the client to use when initiating calls.
struct TurnServer
{
        //! The username to use.
        std::string username;

        //! The password to use.
        std::string password;

        //! A list of TURN URIs.
        std::vector<std::string> uris;

        //! The time-to-live in seconds.
        uint32_t ttl;
};

void
from_json(const nlohmann::json &obj, TurnServer &turnServer);
}
