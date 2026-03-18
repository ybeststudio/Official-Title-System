
// Ara

bool CAN_ENTER_ZONE(const LPCHARACTER& ch, int map_index)
{
	.....
	.....
}

// Altına Ekle

#ifdef ENABLE_TITLE_SYSTEM
namespace
{
	const char* GetTitleSystemEffectPath(int iTitleID)
	{
		switch (iTitleID)
		{
			case 1000: return "d:/ymir work/effect/etc/title/title_05_medal.mse";
			case 1001: return "d:/ymir work/effect/etc/title/title_06_banner_gold.mse";
			case 1002: return "d:/ymir work/effect/etc/title/title_07_banner_red.mse";
			case 1003: return "d:/ymir work/effect/etc/title/title_08_banner_blue.mse";
			case 1004: return "d:/ymir work/effect/etc/title/title_02_dragon.mse";
			case 1005: return "d:/ymir work/effect/etc/title/title_01_shield.mse";
			case 2000: return "d:/ymir work/effect/etc/title/title_04_trophy.mse";
			case 2001: return "d:/ymir work/effect/etc/title/title_03_fist.mse";
			case 2002: return "d:/ymir work/effect/etc/title/title_02_dragon.mse";
			case 2003: return "d:/ymir work/effect/etc/title/title_01_shield.mse";
			case 3000: return "d:/ymir work/effect/etc/title/title_06_banner_gold.mse";
			case 3001: return "d:/ymir work/effect/etc/title/title_07_banner_red.mse";
			case 3002: return "d:/ymir work/effect/etc/title/title_08_banner_blue.mse";
			case 3003: return "d:/ymir work/effect/etc/title/title_02_dragon.mse";
			case 3004: return "d:/ymir work/effect/etc/title/title_05_medal.mse";
			default: return "";
		}
	}
}
#endif


// Arat

void CHARACTER::EncodeInsertPacket(LPENTITY entity)
{

...
....

	if (iDur)
	{
		TPacketGCMove pack;
		EncodeMovePacket(pack, GetVID(), FUNC_MOVE, 0, m_posDest.x, m_posDest.y, iDur, 0, (BYTE) (GetRotation() / 5));
		d->Packet(&pack, sizeof(pack));

		TPacketGCWalkMode p;
		p.vid = GetVID();
		p.header = HEADER_GC_WALK_MODE;
		p.mode = m_bNowWalking ? WALKMODE_WALK : WALKMODE_RUN;

		d->Packet(&p, sizeof(p));
	}

// if (iDur) öncesine (üstüne) ekle

#ifdef ENABLE_TITLE_SYSTEM
	if (IsPC())
	{
		const int iActiveTitle = GetQuestFlag("title_system.active");
		const char* c_szTitleEffect = GetTitleSystemEffectPath(iActiveTitle);
		if (c_szTitleEffect && *c_szTitleEffect)
		{
			TPacketGCSpecificEffect p;
			p.header = HEADER_GC_SPECIFIC_EFFECT;
			p.vid = GetVID();
			memset(p.effect_file, 0, sizeof(p.effect_file));
			strlcpy(p.effect_file, c_szTitleEffect, sizeof(p.effect_file));
			d->Packet(&p, sizeof(p));
		}
	}
#endif
