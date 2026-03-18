
// Ara 
	if (pInstance)
	{
		CInstanceBase::RegisterEffect(CInstanceBase::EFFECT_TEMP, "", kSpecificEffect.effect_file, false);
		pInstance->AttachSpecialEffect(CInstanceBase::EFFECT_TEMP);
	}

// Deðiþtir

#ifdef ENABLE_TITLE_SYSTEM
	if (pInstance)
	{
		const bool bClearTitleEffect =
			(strcmp(kSpecificEffect.effect_file, "__TITLE_EFFECT_CLEAR__") == 0);
		const bool bIsTitleEffect =
			(strstr(kSpecificEffect.effect_file, "/effect/etc/title/") != nullptr) ||
			(strstr(kSpecificEffect.effect_file, "\\effect\\etc\\title\\") != nullptr);

		if (bClearTitleEffect || bIsTitleEffect)
			pInstance->ClearSpecialEffectOverHead();

		if (!bClearTitleEffect)
		{
			CInstanceBase::RegisterEffect(CInstanceBase::EFFECT_TEMP, "", kSpecificEffect.effect_file, false);
			if (bIsTitleEffect)
				pInstance->AttachSpecialEffectOverHead(CInstanceBase::EFFECT_TEMP);
			else
				pInstance->AttachSpecialEffect(CInstanceBase::EFFECT_TEMP);
		}
	}
#else
	if (pInstance)
	{
		CInstanceBase::RegisterEffect(CInstanceBase::EFFECT_TEMP, "", kSpecificEffect.effect_file, false);
		pInstance->AttachSpecialEffect(CInstanceBase::EFFECT_TEMP);
	}

#endif
