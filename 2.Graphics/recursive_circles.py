#coding:utf-8

from drawing import * 

pygame.init()
screen=pygame.display.set_mode((640,480), pygame.RESIZABLE)
pygame.display.set_caption("Drawing")
launched=True

twoCircles(screen, pygame.display.Info().current_h/2-10, 
                    pygame.display.Info().current_w/2, 
                    pygame.display.Info().current_h/2)

while launched:
    for event in pygame.event.get():
        pygame.display.flip()
        if event.type==pygame.QUIT:
            launched=False
