#coding:utf-8
import pygame
from math import *

def circle(screen,r,x,y):
    pygame.draw.circle(screen,(255,255,255), (x,y),r,3)

def twoCircles(screen,r,x,y):
    if(r>10):
        circle(screen,r,x,y)
        twoCircles(screen,r/2,x-r/2,y)
        twoCircles(screen,r/2,x+r/2,y)

