
# Ara

	def OpenCharacterWindowWithState(self, state):
		if FALSE == player.IsObserverMode():
			self.wndCharacter.SetState(state)
			self.wndCharacter.Show()
			self.wndCharacter.SetTop()

# Altýna ekle

	if app.ENABLE_TITLE_SYSTEM:
		def TitleSystemSyncReset(self):
			if not self.wndCharacter:
				return
			try:
				self.wndCharacter.titleSystemUnlockedIDs = set()
			except:
				pass
			if self.wndCharacter.wndTitleSystem:
				self.wndCharacter.wndTitleSystem.SetUnlockedTitleIDs(set())
	
		def TitleSystemSyncAdd(self, titleID):
			if not self.wndCharacter:
				return
			try:
				titleID = int(titleID)
			except:
				return
			try:
				if not hasattr(self.wndCharacter, "titleSystemUnlockedIDs"):
					self.wndCharacter.titleSystemUnlockedIDs = set()
				self.wndCharacter.titleSystemUnlockedIDs.add(titleID)
			except:
				return
			if self.wndCharacter.wndTitleSystem:
				self.wndCharacter.wndTitleSystem.SetUnlockedTitleIDs(self.wndCharacter.titleSystemUnlockedIDs)
	
		def TitleSystemSyncActive(self, titleID):
			if not self.wndCharacter:
				return
			try:
				titleID = int(titleID)
			except:
				titleID = 0
			try:
				self.wndCharacter.titleSystemActiveID = titleID
			except:
				pass
			if self.wndCharacter.wndTitleSystem:
				self.wndCharacter.wndTitleSystem.SetActiveTitleID(titleID)
