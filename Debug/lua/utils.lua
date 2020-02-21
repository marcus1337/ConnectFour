


function getMax(a, b) 
	if (a > b) then
		return a
	end
	return b
end

function adaptToRatio(ratioW, ratioH, w, h)
	m = getMax(ratioW, ratioH)
	w = w * ratioW
	h = h * ratioH
	return math.floor(w), math.floor(h)
end

function centerImage(winW, winH, imgW, imgH)
	x = winW / 2 - imgW / 2
	y = winH / 2 - imgH / 2
	return x, y
end 

function adaptAndCenterImage(image, ratioW, ratioH)
	w, h = adaptToRatio(ratioW, ratioH, image.width, image.height)
	image.width = w
	image.height = h
	x, y = centerImage(info.width, info.height, image.width, image.height)
	image.x = x
	image.y = y
end