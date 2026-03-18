# importların arasına ekle

if app.ENABLE_TITLE_SYSTEM:
	import uicharactertitle

# Ara

		self.soloEmotionSlot = None
		self.dualEmotionSlot = None

# Altına ekle

		if app.ENABLE_TITLE_SYSTEM:
			self.wndTitleSystem = None
			self.titleSystemButton = None
			self.titleSystemUnlockedIDs = set()
			self.titleSystemActiveID = 0


# Ara

		self.tabDict = {
			"STATUS"	: self.GetChild("Tab_01"),
			"SKILL"		: self.GetChild("Tab_02"),
			"EMOTICON"	: self.GetChild("Tab_03"),
			"QUEST"		: self.GetChild("Tab_04"),
		}

# Üstüne ekle

		if app.ENABLE_TITLE_SYSTEM:
			try:
				self.titleSystemButton = self.GetChild("Face_Button")
				self.titleSystemButton.SetEvent(ui.__mem_func__(self.__ToggleTitleSystemWindow))
			except:
				self.titleSystemButton = None


# Ara

	def Destroy(self):
		self.ClearDictionary()

# Altına ekle

		if app.ENABLE_TITLE_SYSTEM:
			if self.wndTitleSystem:
				self.wndTitleSystem.Destroy()
				self.wndTitleSystem = None

# Ara

	def Close(self):

# Altına ekle

		if app.ENABLE_TITLE_SYSTEM:
			if self.wndTitleSystem and self.wndTitleSystem.IsShow():
				self.wndTitleSystem.Hide()

# Ara

	def __OnClickTabButton(self, stateKey):
		self.SetState(stateKey)


# Altına ekle

	if app.ENABLE_TITLE_SYSTEM:
		def __ToggleTitleSystemWindow(self):
			if not (hasattr(app, "ENABLE_TITLE_SYSTEM") and app.ENABLE_TITLE_SYSTEM):
				return

			if not self.wndTitleSystem:
				self.wndTitleSystem = uicharactertitle.CharacterTitleWindow()
				try:
					self.wndTitleSystem.SetUnlockedTitleIDs(self.titleSystemUnlockedIDs)
					self.wndTitleSystem.SetActiveTitleID(self.titleSystemActiveID)
				except:
					pass

			if self.wndTitleSystem.IsShow():
				self.wndTitleSystem.Hide()
			else:
				self.wndTitleSystem.Open()
