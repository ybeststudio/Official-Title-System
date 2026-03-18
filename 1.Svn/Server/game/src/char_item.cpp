

// Arat

					case USE_MOVE:
					case USE_TREASURE_BOX:
					case USE_MONEYBAG:
						break;

// Altýna ekle

#ifdef ENABLE_TITLE_SYSTEM
					case USE_TITLE:
					{
						int iDuration = item->GetValue(1);
						if (iDuration <= 0)
							iDuration = item->GetValue(2);

						const DWORD dwVnum = item->GetVnum();
						const int iBundle0[5] = { 1000, 1001, 1002, 1003, 1004 };
						const int iBundle1[5] = { 1005, 2000, 2001, 2002, 2003 };
						const int iBundle2[5] = { 3000, 3001, 3002, 3003, 3004 };

						const int* pBundle = NULL;
						int iBundleCount = 0;
						switch (dwVnum)
						{
							case 57000: pBundle = iBundle0; iBundleCount = 5; break;
							case 57001: pBundle = iBundle1; iBundleCount = 5; break;
							case 57002: pBundle = iBundle2; iBundleCount = 5; break;
						}

						if (pBundle && iBundleCount > 0)
						{
							int iUnlockedCount = 0;
							for (int i = 0; i < iBundleCount; ++i)
							{
								const int iTitleID = pBundle[i];
								char szOwned[64];
								char szExpire[64];
								snprintf(szOwned, sizeof(szOwned), "title_system.owned.%d", iTitleID);
								snprintf(szExpire, sizeof(szExpire), "title_system.expire.%d", iTitleID);

								if (GetQuestFlag(szOwned) > 0)
									continue;

								SetQuestFlag(szOwned, 1);
								if (iDuration > 0)
									SetQuestFlag(szExpire, get_global_time() + iDuration);
								else
									SetQuestFlag(szExpire, 0);
								++iUnlockedCount;
							}

							if (iUnlockedCount <= 0)
							{
								ChatPacket(CHAT_TYPE_INFO, "You already own all titles in this package.");
								break;
							}

							item->SetCount(item->GetCount() - 1);
							ChatPacket(CHAT_TYPE_INFO, "Title package unlocked: %d new titles.", iUnlockedCount);
							break;
						}

						int iTitleID = item->GetValue(0);
						if (iTitleID <= 0)
						{
							ChatPacket(CHAT_TYPE_INFO, "Invalid title certificate.");
							break;
						}

						char szOwned[64];
						char szExpire[64];
						snprintf(szOwned, sizeof(szOwned), "title_system.owned.%d", iTitleID);
						snprintf(szExpire, sizeof(szExpire), "title_system.expire.%d", iTitleID);
						if (GetQuestFlag(szOwned) > 0)
						{
							ChatPacket(CHAT_TYPE_INFO, "You already own this title.");
							break;
						}

						const int iActiveTitle = GetQuestFlag("title_system.active");
						if (iActiveTitle > 0 && iActiveTitle != iTitleID)
						{
							ChatPacket(CHAT_TYPE_INFO, "Remove your current title first.");
							break;
						}

						SetQuestFlag(szOwned, 1);
						if (iDuration > 0)
							SetQuestFlag(szExpire, get_global_time() + iDuration);
						else
							SetQuestFlag(szExpire, 0);

						SetQuestFlag("title_system.active", iTitleID);
						const char* c_szTitleEffect = "";
						switch (iTitleID)
						{
							case 1000: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_05_medal.mse"; break;
							case 1001: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_06_banner_gold.mse"; break;
							case 1002: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_07_banner_red.mse"; break;
							case 1003: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_08_banner_blue.mse"; break;
							case 1004: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_02_dragon.mse"; break;
							case 1005: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_01_shield.mse"; break;
							case 2000: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_04_trophy.mse"; break;
							case 2001: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_03_fist.mse"; break;
							case 2002: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_02_dragon.mse"; break;
							case 2003: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_01_shield.mse"; break;
							case 3000: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_06_banner_gold.mse"; break;
							case 3001: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_07_banner_red.mse"; break;
							case 3002: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_08_banner_blue.mse"; break;
							case 3003: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_02_dragon.mse"; break;
							case 3004: c_szTitleEffect = "d:/ymir work/effect/etc/title/title_05_medal.mse"; break;
						}

						if (c_szTitleEffect && *c_szTitleEffect)
							SpecificEffectPacket(c_szTitleEffect);

						ChatPacket(CHAT_TYPE_INFO, "Title unlocked and equipped (ID: %d)", iTitleID);
						item->SetCount(item->GetCount() - 1);
					}
					break;
#endif
