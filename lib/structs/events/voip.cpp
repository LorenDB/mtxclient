#include "mtx/events/voip.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace mtx::events::msg {

// m.call.invite
void
from_json(const json &obj, CallInvite &content)
{
        content.call_id  = obj.at("call_id").get<std::string>();
        content.sdp      = obj.at("offer").at("sdp").get<std::string>();
        content.version  = obj.at("version").get<uint16_t>();
        content.lifetime = obj.at("lifetime").get<uint32_t>();
}

void
to_json(json &obj, const CallInvite &content)
{
        obj["call_id"]  = content.call_id;
        obj["offer"]    = {{"sdp", content.sdp}, {"type", "offer"}};
        obj["version"]  = content.version;
        obj["lifetime"] = content.lifetime;
}

// m.call.candidates
void
from_json(const json &obj, CallCandidates::Candidate &content)
{
        content.sdpMid        = obj.at("sdpMid").get<std::string>();
        content.sdpMLineIndex = obj.at("sdpMLineIndex").get<uint16_t>();
        content.candidate     = obj.at("candidate").get<std::string>();
}

void
to_json(json &obj, const CallCandidates::Candidate &content)
{
        obj["sdpMid"]        = content.sdpMid;
        obj["sdpMLineIndex"] = content.sdpMLineIndex;
        obj["candidate"]     = content.candidate;
}

void
from_json(const json &obj, CallCandidates &content)
{
        content.call_id    = obj.at("call_id").get<std::string>();
        content.candidates = obj.at("candidates").get<std::vector<CallCandidates::Candidate>>();
        content.version    = obj.at("version").get<uint16_t>();
}

void
to_json(json &obj, const CallCandidates &content)
{
        obj["call_id"]    = content.call_id;
        obj["candidates"] = content.candidates;
        obj["version"]    = content.version;
}

// m.call.answer
void
from_json(const json &obj, CallAnswer &content)
{
        content.call_id = obj.at("call_id").get<std::string>();
        content.sdp     = obj.at("answer").at("sdp").get<std::string>();
        content.version = obj.at("version").get<uint16_t>();
}

void
to_json(json &obj, const CallAnswer &content)
{
        obj["call_id"] = content.call_id;
        obj["answer"]  = {{"sdp", content.sdp}, {"type", "answer"}};
        obj["version"] = content.version;
}

// m.call.hangup
void
from_json(const json &obj, CallHangUp &content)
{
        content.call_id = obj.at("call_id").get<std::string>();
        content.version = obj.at("version").get<uint16_t>();
        if (obj.count("reason") == 0) {
                content.reason = CallHangUp::Reason::User;
        } else {
                if (obj.at("reason").get<std::string>() == "ice_failed")
                        content.reason = CallHangUp::Reason::ICEFailed;
                else if (obj.at("reason").get<std::string>() == "invite_timeout")
                        content.reason = CallHangUp::Reason::InviteTimeOut;
        }
}

void
to_json(json &obj, const CallHangUp &content)
{
        obj["call_id"] = content.call_id;
        obj["version"] = content.version;
        if (content.reason == CallHangUp::Reason::ICEFailed)
                obj["reason"] = "ice_failed";
        else if (content.reason == CallHangUp::Reason::InviteTimeOut)
                obj["reason"] = "invite_timeout";
}

} // namespace mtx::events::msg
