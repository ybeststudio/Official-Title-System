
// Ara

		void AttachSpecialEffect(DWORD effect);
		
// Altına ekle

#ifdef ENABLE_TITLE_SYSTEM
		void AttachSpecialEffectOverHead(DWORD effect);
		void ClearSpecialEffectOverHead();
#endif


// Ara

		DWORD m_swordRefineEffectRight;
		DWORD m_swordRefineEffectLeft;
		DWORD m_armorRefineEffect[2];

// Altına ekle

#ifdef ENABLE_TITLE_SYSTEM
		DWORD m_dwOverHeadSpecialEffect;
#endif
