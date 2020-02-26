require("utils")


local btnHotSeatPvP = {
	value = 2,
    width = btnWidth,
    height = btnHeight,
    title = "HUMAN v HUMAN",
	x = centerX - btnWidth/2,
	y = centerY - ySpacing*2 + ySpaceBias,
	downImg = "",
	upImg = "",
	hoverImg = ""
}

local btnHotSeatPvE = {
	value = 3,
    width = btnWidth,
    height = btnHeight,
    title = "HUMAN v CPU",
	x = centerX - btnWidth/2,
	y = centerY - ySpacing + ySpaceBias,
	downImg = "",
	upImg = "",
	hoverImg = ""
}

local btnLANCreate = {
	value = 3,
    width = btnWidth,
    height = btnHeight,
    title = "Host LAN",
	x = centerX - btnWidth/2,
	y = centerY + ySpaceBias,
	downImg = "",
	upImg = "",
	hoverImg = ""
}

local btnLANJoin = {
	value = 4,
    width = btnWidth,
    height = btnHeight,
    title = "Join LAN",
	x = centerX - btnWidth/2,
	y = centerY + ySpacing + ySpaceBias,
	downImg = "",
	upImg = "",
	hoverImg = ""
}

getButtons = function()
	return btnHotSeatPvP, btnHotSeatPvE, btnLANCreate, btnLANJoin
end

----------------------

local background = {
	width = 5000,
	height = 5000,
	x = 0,
	y = 0,
	imageName = "space1.png"
}

local banner = {
	width = 80,
	height = 60,
	x = centerX,
	y = centerY - ySpacing,
	imageName = "con4banner.png"
}


getImages = function()
	adaptAndCenterImage(background, 4,3)
	adaptAndCenterImage(banner, 4,1)
	banner.y = banner.y - ySpacing*2.2
	return banner, background
end

-------------



