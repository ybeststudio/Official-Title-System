// Ara

	PyModule_AddIntConstant(poModule, "USE_TIME_CHARGE_FIX", CItemData::USE_TIME_CHARGE_FIX);

// Altına ekle

#ifdef ENABLE_TITLE_SYSTEM
	PyModule_AddIntConstant(poModule, "USE_TITLE", CItemData::USE_TITLE);
#endif