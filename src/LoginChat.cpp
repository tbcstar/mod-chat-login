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

	std::string channelName = sConfigMgr->GetStringDefault("LoginChat.name", "world");
        QueryResult result = CharacterDatabase.PQuery("SELECT channelId FROM channels WHERE name = '%s'", channelName.c_str());

        if (!result) return;

    	if (ChannelMgr* cMgr = ChannelMgr::forTeam(player->GetTeamId()))
    	{
        	if (Channel* channel = cMgr->GetJoinChannel("world", 9))
            		channel->JoinChannel(player, "");
    		cMgr->LoadChannels();
	}

    }
};

void AddLoginChatScripts() {
    new LoginChat();
}

