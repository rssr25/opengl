import cv2
import numpy as np

image = cv2.imread("lion.png")

counter = 0

for i in range(0, image.shape[0]):
	for j in range(0, image.shape[1]):
		if(image[i][j][0] == 0):
			counter = counter + 1

print counter