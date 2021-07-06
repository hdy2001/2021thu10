# -*- coding:UTF-8 -*-
# how to use ?
# make sure the file path is all right (note: you have to create a null file first in JpgPath and PgmWritePath)
# then add the following in qt slot
# system("bash -c 'source /opt/ros/kinetic/setup.bash;source ~/catkin_ws/devel/setup.bash; cd path_to_this_file && python PgmDenoise.py; bash'&");


import numpy as np
from matplotlib import pyplot as plt
from PIL import Image,ImageEnhance,ImageFilter

def denoising(im):
    pixdata=im.load()
    w,h=im.size
    # 如果黑点周围有三个以上黑点，这点才是黑点，否则是噪声
    for j in range(1,h-1):
        for i in range(1,w-1):
            count=0
            if pixdata[i,j-1]>245:
                count=count+1
            if pixdata[i,j+1]>245:
                count=count+1
            if pixdata[i+1,j]>245:
                count=count+1
            if pixdata[i-1,j]>245:
                count=count+1
            if count>2:
                pixdata[i,j]=255
    return im

PgmOpenPath = '/home/pzs/map.pgm'
JpgPath = '/home/pzs/MapJpg.jpg'
PgmWritePath = '/home/pzs/catkin_ws/src/wpb_home/wpb_home_tutorials/maps/map.pgm'
Image.open(PgmOpenPath).save(JpgPath)#最终保存下来的是灰度图的jpg
im = Image.open(JpgPath)

ImgDenoise = denoising(im)
ImgDenoise.convert('L').save(PgmWritePath)
print("slam image denoise done!")
