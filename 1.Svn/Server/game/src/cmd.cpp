

// Ara

struct command_info cmd_info[] =

// Üstüne ekle 

#ifdef ENABLE_TITLE_SYSTEM
ACMD(do_title);
#endif

// Ara

	{ "\n",		NULL,		0,		POS_DEAD,		GM_IMPLEMENTOR	}
};

// Üstüne ekle 

#ifdef ENABLE_TITLE_SYSTEM
	{ "title",		do_title,		0,		POS_DEAD,		GM_PLAYER	},
#endif
