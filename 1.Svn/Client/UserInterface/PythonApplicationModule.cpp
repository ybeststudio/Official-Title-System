
// Ara 

#ifdef ENABLE_ENERGY_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_ENERGY_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_ENERGY_SYSTEM", 0);
#endif

// Altına ekle

#ifdef ENABLE_TITLE_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_TITLE_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_TITLE_SYSTEM", 0);
#endif

