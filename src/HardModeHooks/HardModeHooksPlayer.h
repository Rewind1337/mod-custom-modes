#ifndef MODULE_HARDMODE_HOOKS_PLAYER_H
#define MODULE_HARDMODE_HOOKS_PLAYER_H

#include "Player.h"
#include "ScriptMgr.h"

class HardModeHooksPlayerScript : PlayerScript
{
public:
    HardModeHooksPlayerScript() : PlayerScript("HardModeHooksPlayerScript") { }

private:
    void OnPlayerGiveXP(Player* player, uint32& amount, Unit* victim, uint8 xpSource) override;
    void OnPlayerQuestComputeXP(Player* player, Quest const* quest, uint32& xpValue) override;

    bool OnPlayerCanEquipItem(Player* player, uint8 slot, uint16& dest, Item* pItem, bool swap, bool notLoading) override;
    bool OnPlayerCanCastItemUseSpell(Player* player, Item* item, SpellCastTargets const& targets, uint8 castCount, uint32 glyphIndex) override;
    void OnPlayerCreateItem(Player* player, Item* item, uint32 count) override;

    void OnPlayerResurrect(Player* player, float restorePercent, bool& applySickness) override;
    void OnPlayerReleasedGhost(Player* player) override;
    bool OnPlayerCanRepopAtGraveyard(Player* player) override;

    bool OnPlayerBeforeTeleport(Player* player, uint32 mapId, float x, float y, float z, float orientation, uint32 options, Unit* target) override;
    void OnPlayerLearnTalents(Player* player, uint32 talentId, uint32 talentRank, uint32 spellId) override;

    bool OnPlayerCanInitTrade(Player* player, Player* target) override;
    bool OnPlayerCanSendMail(Player* player, ObjectGuid receiverGuid, ObjectGuid mailbox, std::string& subject, std::string& body, uint32 money, uint32 cod, Item* item) override;
    bool OnPlayerCanJoinLfg(Player* player, uint8 roles, lfg::LfgDungeonSet& dungeons, const std::string& comment) override;
    bool OnPlayerCanGroupInvite(Player* player, std::string& memberName) override;

    void OnPlayerLogin(Player* player) override;
    void OnPlayerDelete(ObjectGuid guid, uint32 accountId) override;
};

#endif // MODULE_HARDMODE_HOOKS_PLAYER_H
