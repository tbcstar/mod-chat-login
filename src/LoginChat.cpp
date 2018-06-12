/**
    This plugin can be used for common player customizations
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "ChannelMgr.h"
#include "Chat.h"

class LoginChat : public PlayerScript{
public:

    LoginChat() : PlayerScript("LoginChat") { }

    void OnLogin(Player* player) override {


        if (sConfigMgr->GetBoolDefault("LoginChat.enabled", false)) {

            ChannelMgr* cMgr = ChannelMgr::forTeam(TEAM_ALLIANCE);

            std::string channelName = sConfigMgr->GetStringDefault("LoginChat.name", "world");
            QueryResult result = CharacterDatabase.PQuery("SELECT channelId FROM channels WHERE name = '%s'", channelName.c_str());

            if (!result) return;

            uint32 channelId = (*result)[0].GetUInt32();

            Channel* joinChannel = cMgr->GetJoinChannel(channelName, channelId);

            joinChannel->JoinChannel(player, "");

        }
    }
};

class login_chat_conf : public WorldScript
{
public:
    login_chat_conf() : WorldScript("login_chat_conf") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/login_chat.conf";
#ifdef WIN32
            cfg_file = "reward_shop.conf";
#endif
            std::string cfg_def_file = cfg_file + ".dist";

            sConfigMgr->LoadMore(cfg_def_file.c_str());

            sConfigMgr->LoadMore(cfg_file.c_str());
        }
    }
};


void AddLoginChatScripts() {
    new LoginChat();
    new login_chat_conf();
}

