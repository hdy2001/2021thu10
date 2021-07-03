from os import name
from lxml import etree

#读取
with open("waypoints.xml") as fp:
    doc=etree.XML(fp.read())

names=doc.xpath("//Name")
Pos_xs=doc.xpath("//Pos_x")
Pos_ys=doc.xpath("//Pos_y")
Ori_zs=doc.xpath("//Ori_z")

with open("waypoints.txt","w") as f:
    for i in range(len(names)):
        f.write('%s %s %s %s\n'%(names[i].text, Pos_xs[i].text, Pos_ys[i].text, Ori_zs[i].text))
print("write done!")
