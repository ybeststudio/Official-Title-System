
// Ara  case USE_PUT_INTO_RING_SOCKET: hemen altýna ekle

const char *CItemData::GetUseTypeString() const
{
	if (GetType() != CItemData::ITEM_TYPE_USE)
		return "NOT_USE_TYPE";

	switch (GetSubType())
	{

		case USE_PUT_INTO_RING_SOCKET:
			return DEF_STR(USE_PUT_INTO_RING_SOCKET);
			
#ifdef ENABLE_TITLE_SYSTEM
		case USE_TITLE:
			return DEF_STR(USE_TITLE);
#endif
