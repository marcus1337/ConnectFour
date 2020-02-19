local btnWidth = info.width / 3
local btnHeight = info.height / 8
local centerX = info.width / 2
local centerY = info.height / 2
local ySpacing = info.height / 5 - 10
local ySpaceBias = info.height/10;

local btnHotSeatPvP = {
    width = btnWidth,
    height = btnHeight,
    title = "HUMAN v HUMAN",
	x = centerX - btnWidth/2,
	y = centerY - ySpacing*2 + ySpaceBias
}

local btnHotSeatPvE = {
    width = btnWidth,
    height = btnHeight,
    title = "HUMAN v CPU",
	x = centerX - btnWidth/2,
	y = centerY - ySpacing + ySpaceBias
}

local btnLANCreate = {
    width = btnWidth,
    height = btnHeight,
    title = "Host LAN",
	x = centerX - btnWidth/2,
	y = centerY + ySpaceBias
}

local btnLANJoin = {
    width = btnWidth,
    height = btnHeight,
    title = "Join LAN",
	x = centerX - btnWidth/2,
	y = centerY + ySpacing + ySpaceBias
}

getButtons = function()
	return btnHotSeatPvP, btnHotSeatPvE, btnLANCreate, btnLANJoin
end

