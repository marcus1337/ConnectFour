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

getButtons = function()
	adaptImageToRatio(backButton, 2,1)
	backButton.x = leftPaneWidth/2 - backButton.width/2
	return backButton
end

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
	return tmp
end

getRow = function(colIndex)
	local col = {}	
	for i = 1, 6 do
		local tmpPiece = getABoardPiece()
		tmpPiece.x = tmpPiece.x + tmpPiece.width*colIndex
		tmpPiece.y = tmpPiece.y - tmpPiece.height*(i-1)
		col[i] = tmpPiece	
	end
	
	return col
end

local getBoard = function()
	local row1 = getRow(1)

	return table.unpack(row1)
end

getImages = function()
	adaptAndCenterImage(background, 4,3)
	return table.unpack({getBoard()})
	--return table.unpack(getBoard()), gameBox, background
end

-------------