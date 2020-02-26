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

local boardPiece = {
	x = 0,
	y = 0,
	width = 120,
	height = 120,
	imageName = "board_cell.png"
}

local getABoardPiece = function()
	tmp = copyTable(boardPiece)
	tmp.x = gameBox.x
	tmp.width = math.floor(gameBox.width/7)
	tmp.height = math.floor(gameBox.height/6)
	tmp.y = info.height - tmp.height
	tmp.downImg = "board_cell_hover.png"
	tmp.upImg = "board_cell.png"
	tmp.hoverImg = "board_cell_hover.png"
	tmp.title = ""
	tmp.value = 0
	return tmp
end

getRow = function(colIndex)
	local col = {}	
	for i = 1, 6 do
		local tmpPiece = getABoardPiece()
		tmpPiece.x = tmpPiece.x + tmpPiece.width*colIndex
		tmpPiece.y = tmpPiece.y - tmpPiece.height*(i-1)
		tmpPiece.value = colIndex
		col[i] = tmpPiece	
	end
	
	return col
end

local getBoard = function()
	local row1 = getRow(0)

	return table.unpack(row1)
end

getImages = function()
	adaptAndCenterImage(background, 4,3)
	local imageTable = {}
	table.insert(imageTable, gameBox)
	table.insert(imageTable, background)
	return table.unpack(imageTable)
end

getGameButtons = function()
	local buttonTable = {}
	for i = 0, 6 do
		for k, v in pairs(getRow(i)) do
			table.insert(buttonTable, v)
		end
	end
	return table.unpack(buttonTable)
end

getButtons = function()
	adaptImageToRatio(backButton, 2,1)
	adaptImageToRatio(rematchButton, 2,1)
	backButton.x = leftPaneWidth/2 - backButton.width/2
	rematchButton.x = backButton.x
	return backButton, rematchButton
end

-------------