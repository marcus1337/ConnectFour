local btnWidth = info.width / 10
local btnHeight = info.height / 10
local centerX = info.width / 2
local centerY = info.height / 2
local ySpacing = info.height / 10

local button1 = {
    width = btnWidth,
    height = btnHeight,
    title = "Test window",
	x = centerX - btnWidth/2,
	y = centerY - ySpacing
}

local button2 = {
    width = btnWidth,
    height = btnHeight,
    title = "Test wind",
	x = centerX - btnWidth/2,
	y = centerY - ySpacing*2
}

getButtons = function()
	return button1, button2
end

