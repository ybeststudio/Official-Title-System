
# En alta müsait bir yere ekle

if app.ENABLE_TITLE_SYSTEM:
	# ??? ??
	window["children"][0]["children"][4]["children"].append(
		{	
			"name" : "Face_Button",
			"type" : "button",
					
			"x" : 10,
			"y" : 10,
					
			"default_image" : ROOT_PATH + "char_face_button_default.sub",
			"over_image"	: ROOT_PATH + "char_face_button_over.sub",
			"down_image"	: ROOT_PATH + "char_face_button_down.sub",
		}
	)

	# ??? ??? ?? ???
	window["children"][0]["children"][4]["children"].append(
		{	
			"name"	: "Write_Image",
			"type"	: "image",
					
			"x"		: 43,
			"y"		: 44,
	
			"image" : ROOT_PATH + "char_face_write_default.sub",
		}
	)