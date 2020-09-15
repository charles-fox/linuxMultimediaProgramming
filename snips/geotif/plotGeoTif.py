import gdal
import numpy as np
from pylab import *

ds = gdal.Open('map.tif')
M = np.array(ds.GetRasterBand(1).ReadAsArray())
imshow(M)
show()


