local btnWidth = info.width / 3
local btnHeight = info.height / 4
local centerX = info.width / 2
local centerY = info.height / 2
local ySpacing = info.height / 7

local btnHotSeatPvP = {
    width = btnWidth,
    height = btnHeight,
    title = "HUMAN v HUMAN",
	x = centerX - btnWidth/2,
	y = centerY - ySpacing*2
}

local btnHotSeatPvE = {
    width = btnWidth,
    height = btnHeight,
    title = "HUMAN v CPU",
	x = centerX - btnWidth/2,
	y = centerY - ySpacing
}

local btnLANCreate = {
    width = btnWidth,
    height = btnHeight,
    title = "Host LAN",
	x = centerX - btnWidth/2,
	y = centerY
}

local btnLANJoin = {
    width = btnWidth,
    height = btnHeight,
    title = "Join LAN",
	x = centerX - btnWidth/2,
	y = centerY + ySpacing
}

getButtons = function()
	return btnHotSeatPvP, btnHotSeatPvE, btnLANCreate, btnLANJoin
end

