require("utils")

getButtons = function()
	return nil
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
	return background
end

-------------