import cv2
import numpy as np

img = cv2.imread("Input/seismic.png", 0)
dim = (70,60)

resized = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)
resized = cv2.blur(resized, ksize=(5,5))

priors = open("Input/priors.txt", "w")

for i in range (60):
    for j in range(70):
        priors.write(str(resized[i][j])+"\n")

priors.close()

cv2.imwrite("Input/seismic_priors.png", resized)
cv2.waitKey(0)
cv2.destroyAllWindows()
