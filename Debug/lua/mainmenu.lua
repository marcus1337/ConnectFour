local btnWidth = info.width / 3
local btnHeight = info.height / 8
local centerX = info.width / 2
local centerY = info.height / 2
local ySpacing = info.height / 5 - 10
local ySpaceBias = info.height/10;

local btnHotSeatPvP = {
	value = 1,
    width = btnWidth,
    height = btnHeight,
    title = "HUMAN v HUMAN",
	x = centerX - btnWidth/2,
	y = centerY - ySpacing*2 + ySpaceBias
}

local btnHotSeatPvE = {
	value = 2,
    width = btnWidth,
    height = btnHeight,
    title = "HUMAN v CPU",
	x = centerX - btnWidth/2,
	y = centerY - ySpacing + ySpaceBias
}

local btnLANCreate = {
	value = 3,
    width = btnWidth,
    height = btnHeight,
    title = "Host LAN",
	x = centerX - btnWidth/2,
	y = centerY + ySpaceBias
}

local btnLANJoin = {
	value = 4,
    width = btnWidth,
    height = btnHeight,
    title = "Join LAN",
	x = centerX - btnWidth/2,
	y = centerY + ySpacing + ySpaceBias
}

getButtons = function()
	return btnHotSeatPvP, btnHotSeatPvE, btnLANCreate, btnLANJoin
end

----------------------

local background = {
	width = 500,
	height = 500,
	x = 0,
	y = 0,
	imageName = "button1.png"

}

getImages = function()
	return background
end
