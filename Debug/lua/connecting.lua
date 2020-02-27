require("utils")

local leftPaneWidth = info.width / 10
local backDiv = 2

local backButton = {
	value = 1,
    width = leftPaneWidth/backDiv,
    height = btnHeight,
    title = "",
	x = leftPaneWidth/2 - leftPaneWidth/(backDiv*2),
	y = info.height / 30,
	downImg = "icons//prev.png",
	upImg = "icons//prev.png",
	hoverImg = ""
}

local rematchButton = {
	value = 4,
    width = leftPaneWidth/backDiv,
    height = btnHeight,
    title = "",
	x = leftPaneWidth/2 - leftPaneWidth/(backDiv*2),
	y = (info.height / 30)+backButton.height,
	downImg = "icons//replay.png",
	upImg = "icons//replay.png",
	hoverImg = ""
}

----------------------

local background = {
	width = 5000,
	height = 5000,
	x = 0,
	y = 0,
	imageName = "space1.png"
}

local leftMenuPlane = {
	x = 0,
	y = 0,
	width = leftPaneWidth,
	height = info.height,
	imageName = ""
}

local gameBox = {
	width = info.width - leftMenuPlane.width,
	height = info.height,
	x = leftMenuPlane.width,
	y = 0,
	imageName = "space1.png"
}


getImages = function()
	adaptAndCenterImage(background, 4,3)
	local imageTable = {}
	table.insert(imageTable, gameBox)
	table.insert(imageTable, background)
	return table.unpack(imageTable)
end

getButtons = function()
	adaptImageToRatio(backButton, 2,1)
	adaptImageToRatio(rematchButton, 2,1)
	backButton.x = leftPaneWidth/2 - backButton.width/2
	rematchButton.x = backButton.x
	return backButton, rematchButton
end

-------------