

# Ara

	def BINARY_AppendNotifyMessage(self, type):
		if not type in localeInfo.NOTIFY_MESSAGE:
			return
		chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.NOTIFY_MESSAGE[type])


# Altýna ekle

	if app.ENABLE_TITLE_SYSTEM:
        def __TitleSystemSyncReset(self):
            if self.interface:
                self.interface.TitleSystemSyncReset()

        def __TitleSystemSyncAdd(self, titleID):
            if self.interface:
                self.interface.TitleSystemSyncAdd(titleID)

        def __TitleSystemSyncActive(self, titleID):
            if self.interface:
                self.interface.TitleSystemSyncActive(titleID)



# Ara

	def __ServerCommand_Build(self):
		serverCommandList={
        .
        ..
        ...
        ..
		}

# Altýna ekle

		if app.ENABLE_TITLE_SYSTEM:
			serverCommandList["TitleSyncReset"] = self.__TitleSystemSyncReset
			serverCommandList["TitleSyncAdd"] = self.__TitleSystemSyncAdd
			serverCommandList["TitleSyncActive"] = self.__TitleSystemSyncActive
