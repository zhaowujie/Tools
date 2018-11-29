#!/usr/bin/python
#coding=utf-8
import xml.etree.ElementTree as ET
import pickle
import os
import json
#get_classes_and_number_from_xml
file_path = '/media/hp208/4t/zhaoxingjie/data/VOCdevkit2007/VOC2007/Annotations/'
class_list = {}
for name_list in os.listdir(file_path):
    #for file in name_list:
    file = file_path + name_list
    in_file = open(file , 'r')
    tree = ET.parse(in_file)
    root = tree.getroot()
    size = root.find('size')
    obj = root.find('object')   #从根节点得到object的位置/级别,观察xml文件层级即可
    w = int(size.find('width').text)
    h = int(size.find('height').text)
    for obj in root.iter('object'):
        cls = obj.find('name').text
        if (cls not in class_list):
            class_list[cls] = 1
        else:
            class_list[cls] +=1
print (class_list)
with open('/media/hp208/4t/zhaoxingjie/data/VOCdevkit2007/VOC2007/classes.txt', 'w') as f:
    json.dump(class_list, f)

