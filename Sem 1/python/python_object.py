import pygame
import random

pygame.init()

RED    =  (255,   0,   0)
WHITE =  (255,255,255)
BLUE =  (25,25,0)
size = [600, 600]
screen = pygame.display.set_mode(size)


done = False
clock = pygame.time.Clock()
mov=1
flag=0
a1=275
a2=380
b1=265
b2=390
c1=270
c2=400
d1=280
d2=400
e1=285
e2=390
while not done:

    clock.tick(random.randint(5,500))
        screen.fill(WHITE)

        if mov<=126 and flag==1:
            if mov==0:
                flag=0


                pygame.draw.polygon(screen, ( 220,(mov*2), 0),  ((a1,a2),(b1,b2), (c1,c2),(d1,d2),(e1,e2)))
                a2+=3
                b1+=1
                b2+=1
                e1-=1
                e2+=1
                c1+=0.25
                d1-=0.25
                mov=mov-1

                pygame.display.flip()

        else:
            if mov==125:
                flag=1
                mov=mov+1
                a2-=3
                b1-=1
                b2-=1
                e1+=1
                e2-=1
                c1-=0.25
                d1+=0.25

                pygame.draw.polygon(screen, ( 220,(mov*2),   0),  ((a1,a2),(b1,b2), (c1,c2),(d1,d2),(e1,e2))); 

                pygame.display.flip()


        for event in pygame.event.get(): 
            if event.type == pygame.QUIT: 
                done=True 

pygame.quit()
