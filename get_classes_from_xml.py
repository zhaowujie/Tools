#!/usr/bin/python
#coding = UTF-8
import xml.etree.ElementTree as ET
import pickle
import os
from os import listdir, getcwd
from os.path import join

file_path = 'D:\电力金具500张\电力金具500张\VOCdevkit2007\VOC2007\Annotations\\'
class_list = []
for name_list in os.listdir(file_path):
    #for file in name_list:
    file = file_path + name_list
    in_file = open(file , 'r')
    out_file = open('D:\电力金具500张\电力金具500张\VOCdevkit2007\VOC2007\classes.txt', 'a')
    tree = ET.parse(in_file)
    root = tree.getroot()
    size = root.find('size')
    obj = root.find('object')   #从根节点得到object的位置/级别,观察xml文件层级即可
    w = int(size.find('width').text)
    h = int(size.find('height').text)
    #for obj in root.iter('object'):
    cls = obj.find('name').text
    if (cls not in class_list):
        class_list.append(cls)
print (class_list)
    #out_file.write(cls + "\n" )





	