
btnWidth = info.width / 3
btnHeight = info.height / 8
centerX = info.width / 2
centerY = info.height / 2
ySpacing = info.height / 5 - 10
ySpaceBias = info.height/10;


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

function adaptImageToRatio(image, ratioW, ratioH)
	w, h = adaptToRatio(ratioW, ratioH, image.width, image.height)
	image.width = w
	image.height = h
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


function copyTable(t)
  local t2 = {}
  for k,v in pairs(t) do
    t2[k] = v
  end
  return t2
end

