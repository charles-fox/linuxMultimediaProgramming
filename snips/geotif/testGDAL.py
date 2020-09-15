import gdal
ds = gdal.Open('map.tif')
gt = ds.GetGeoTransform()
print(gt)
print("Origin = ({}, {})".format(gt[0], gt[3]))
print("Pixel Size = ({}, {})".format(gt[1], gt[5]))
proj = ds.GetProjection()      #contains the datum 
print(proj)
band = ds.GetRasterBand(1)   #the raw data pixels for a channel (numbered 1-3)
print("X size in pix: %i"%band.XSize)
print("scale: %f"%band.GetScale())
print("offset: %f"%band.GetOffset())

