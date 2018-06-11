/**
    This plugin can be used for common player customizations
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "ChannelMgr.h"

class LoginChat : public PlayerScript{
public:

    LoginChat() : PlayerScript("LoginChat") { }

    void OnLogin(Player* player) override {


        if (sConfigMgr->GetBoolDefault("LoginChat.enabled", false)) {

            std::string channelName = sConfigMgr->getStringDefault("LoginChat.name", "world");
            int channelId = sConfigMgr->GetIntDefault("LoginChat.id", 9);

            joinChannel = cMgr->GetJoinChannel(channelName, channelId);
            joinChannel->JoinChannel(this, ""); 
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

