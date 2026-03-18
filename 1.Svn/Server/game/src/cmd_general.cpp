
// müsait bir yere ekle

#ifdef ENABLE_TITLE_SYSTEM
namespace
{
	struct STitleSystemDef
	{
		int iTitleID;
		const char* c_szName;
		const char* c_szEffect;
	};

	const STitleSystemDef kTitleSystemDefs[] =
	{
		{ 1000, "Sansli", "d:/ymir work/effect/etc/title/title_05_medal.mse" },
		{ 1001, "Metin+", "d:/ymir work/effect/etc/title/title_06_banner_gold.mse" },
		{ 1002, "Destansi", "d:/ymir work/effect/etc/title/title_07_banner_red.mse" },
		{ 1003, "Efsanevi", "d:/ymir work/effect/etc/title/title_08_banner_blue.mse" },
		{ 1004, "Mistik", "d:/ymir work/effect/etc/title/title_02_dragon.mse" },
		{ 1005, "Gunessever", "d:/ymir work/effect/etc/title/title_01_shield.mse" },
		{ 2000, "Son kurtulan", "d:/ymir work/effect/etc/title/title_04_trophy.mse" },
		{ 2001, "Yenilmez", "d:/ymir work/effect/etc/title/title_03_fist.mse" },
		{ 2002, "Savas habercisi", "d:/ymir work/effect/etc/title/title_02_dragon.mse" },
		{ 2003, "Kasap", "d:/ymir work/effect/etc/title/title_01_shield.mse" },
		{ 3000, "Metin+", "d:/ymir work/effect/etc/title/title_06_banner_gold.mse" },
		{ 3001, "Destansi", "d:/ymir work/effect/etc/title/title_07_banner_red.mse" },
		{ 3002, "Efsanevi", "d:/ymir work/effect/etc/title/title_08_banner_blue.mse" },
		{ 3003, "Mistik", "d:/ymir work/effect/etc/title/title_02_dragon.mse" },
		{ 3004, "Sansli", "d:/ymir work/effect/etc/title/title_05_medal.mse" },
	};

	const char* TITLE_SYSTEM_CLEAR_EFFECT_TOKEN = "__TITLE_EFFECT_CLEAR__";
	const char* TITLE_SYSTEM_ACTIVE_FLAG = "title_system.active";
	const char* TITLE_SYSTEM_OWNED_FLAG_FMT = "title_system.owned.%d";
	const char* TITLE_SYSTEM_EXPIRE_FLAG_FMT = "title_system.expire.%d";

	void BuildTitleSystemOwnedFlag(int iTitleID, char* szFlag, size_t stSize)
	{
		snprintf(szFlag, stSize, TITLE_SYSTEM_OWNED_FLAG_FMT, iTitleID);
	}

	void BuildTitleSystemExpireFlag(int iTitleID, char* szFlag, size_t stSize)
	{
		snprintf(szFlag, stSize, TITLE_SYSTEM_EXPIRE_FLAG_FMT, iTitleID);
	}

	const STitleSystemDef* FindTitleSystemDef(int iTitleID)
	{
		for (size_t i = 0; i < sizeof(kTitleSystemDefs) / sizeof(kTitleSystemDefs[0]); ++i)
		{
			if (kTitleSystemDefs[i].iTitleID == iTitleID)
				return &kTitleSystemDefs[i];
		}

		return NULL;
	}

	int GetTitleSystemExpireTime(LPCHARACTER ch, int iTitleID)
	{
		if (!ch)
			return 0;

		char szFlag[64];
		BuildTitleSystemExpireFlag(iTitleID, szFlag, sizeof(szFlag));
		return ch->GetQuestFlag(szFlag);
	}

	bool IsTitleSystemOwned(LPCHARACTER ch, int iTitleID)
	{
		if (!ch)
			return false;

		char szFlag[64];
		BuildTitleSystemOwnedFlag(iTitleID, szFlag, sizeof(szFlag));
		return ch->GetQuestFlag(szFlag) > 0;
	}

	void ClearTitleSystemOwnership(LPCHARACTER ch, int iTitleID)
	{
		if (!ch)
			return;

		char szOwned[64];
		char szExpire[64];
		BuildTitleSystemOwnedFlag(iTitleID, szOwned, sizeof(szOwned));
		BuildTitleSystemExpireFlag(iTitleID, szExpire, sizeof(szExpire));
		ch->SetQuestFlag(szOwned, 0);
		ch->SetQuestFlag(szExpire, 0);

		if (ch->GetQuestFlag(TITLE_SYSTEM_ACTIVE_FLAG) == iTitleID)
			ch->SetQuestFlag(TITLE_SYSTEM_ACTIVE_FLAG, 0);
	}

	bool IsTitleSystemExpired(LPCHARACTER ch, int iTitleID)
	{
		const int iExpireAt = GetTitleSystemExpireTime(ch, iTitleID);
		if (iExpireAt <= 0)
			return false;

		if (iExpireAt > get_global_time())
			return false;

		ClearTitleSystemOwnership(ch, iTitleID);
		return true;
	}

	void SetTitleSystemActive(LPCHARACTER ch, int iTitleID)
	{
		if (!ch)
			return;

		ch->SetQuestFlag(TITLE_SYSTEM_ACTIVE_FLAG, iTitleID);
	}
}

ACMD(do_title)
{
	char arg1[256];
	argument = one_argument(argument, arg1, sizeof(arg1));

	if (!*arg1)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Title commands: /title list, /title equip <id>, /title clear, /title status");
		return;
	}

	if (!str_cmp(arg1, "list"))
	{
		ch->ChatPacket(CHAT_TYPE_COMMAND, "TitleSyncReset");
		ch->ChatPacket(CHAT_TYPE_INFO, "Unlocked titles:");
		for (size_t i = 0; i < sizeof(kTitleSystemDefs) / sizeof(kTitleSystemDefs[0]); ++i)
		{
			const int iTitleID = kTitleSystemDefs[i].iTitleID;
			if (!IsTitleSystemOwned(ch, iTitleID))
				continue;

			if (IsTitleSystemExpired(ch, iTitleID))
				continue;

			const int iExpireAt = GetTitleSystemExpireTime(ch, iTitleID);
			ch->ChatPacket(CHAT_TYPE_COMMAND, "TitleSyncAdd %d", iTitleID);
			if (iExpireAt > 0)
				ch->ChatPacket(CHAT_TYPE_INFO, "- %d: %s (expires in %d sec)", iTitleID, kTitleSystemDefs[i].c_szName, iExpireAt - get_global_time());
			else
				ch->ChatPacket(CHAT_TYPE_INFO, "- %d: %s", iTitleID, kTitleSystemDefs[i].c_szName);
		}
		return;
	}

	if (!str_cmp(arg1, "status"))
	{
		const int iActive = ch->GetQuestFlag(TITLE_SYSTEM_ACTIVE_FLAG);
		ch->ChatPacket(CHAT_TYPE_COMMAND, "TitleSyncActive %d", iActive);
		if (iActive <= 0)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "No active title.");
			return;
		}

		const STitleSystemDef* pkDef = FindTitleSystemDef(iActive);
		if (!pkDef)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "Active title id: %d", iActive);
			return;
		}

		ch->ChatPacket(CHAT_TYPE_INFO, "Active title: %d (%s)", iActive, pkDef->c_szName);
		return;
	}


	if (!str_cmp(arg1, "sync"))
	{
		ch->ChatPacket(CHAT_TYPE_COMMAND, "TitleSyncReset");
		for (size_t i = 0; i < sizeof(kTitleSystemDefs) / sizeof(kTitleSystemDefs[0]); ++i)
		{
			const int iTitleID = kTitleSystemDefs[i].iTitleID;
			if (!IsTitleSystemOwned(ch, iTitleID))
				continue;

			if (IsTitleSystemExpired(ch, iTitleID))
				continue;

			ch->ChatPacket(CHAT_TYPE_COMMAND, "TitleSyncAdd %d", iTitleID);
		}
		ch->ChatPacket(CHAT_TYPE_COMMAND, "TitleSyncActive %d", ch->GetQuestFlag(TITLE_SYSTEM_ACTIVE_FLAG));
		return;
	}

	if (!str_cmp(arg1, "clear"))
	{
		SetTitleSystemActive(ch, 0);
		ch->SpecificEffectPacket(TITLE_SYSTEM_CLEAR_EFFECT_TOKEN);
		// no restart for title clear (client sync command handles UI state)
		ch->ChatPacket(CHAT_TYPE_COMMAND, "TitleSyncActive 0");
		ch->ChatPacket(CHAT_TYPE_INFO, "Title unequipped.");
		return;
	}

	if (!str_cmp(arg1, "equip"))
	{
		char arg2[256];
		one_argument(argument, arg2, sizeof(arg2));
		if (!*arg2)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "Usage: /title equip <id>");
			return;
		}

		int iTitleID = 0;
		str_to_number(iTitleID, arg2);
		const STitleSystemDef* pkDef = FindTitleSystemDef(iTitleID);
		if (!pkDef)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "Unknown title id.");
			return;
		}

		if (!IsTitleSystemOwned(ch, iTitleID) || IsTitleSystemExpired(ch, iTitleID))
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "You do not own this title or it has expired.");
			return;
		}
		const int iActiveTitle = ch->GetQuestFlag(TITLE_SYSTEM_ACTIVE_FLAG);
		if (iActiveTitle == iTitleID)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "This title is already active.");
			return;
		}
		if (iActiveTitle > 0)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, "Remove your current title first.");
			return;
		}
		ch->SpecificEffectPacket(TITLE_SYSTEM_CLEAR_EFFECT_TOKEN);
		SetTitleSystemActive(ch, iTitleID);
		ch->ChatPacket(CHAT_TYPE_COMMAND, "TitleSyncActive %d", iTitleID);
		if (pkDef->c_szEffect && *pkDef->c_szEffect) ch->SpecificEffectPacket(pkDef->c_szEffect);
		ch->ChatPacket(CHAT_TYPE_INFO, "%s was equipped.", pkDef->c_szName);
		return;
	}

	ch->ChatPacket(CHAT_TYPE_INFO, "Unknown title command.");
}
#endif
