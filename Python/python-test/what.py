import random as r
print(''.join(r.choice('██▓▓░░  ') for _ in range(1000)))

import pygame, sys
pygame.init()
screen = pygame.display.set_mode((400, 300))
x, y = 200, 250
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()
    keys = pygame.key.get_pressed()
    x += (keys[pygame.K_RIGHT] - keys[pygame.K_LEFT]) * 5
    screen.fill((0,0,0))
    pygame.draw.circle(screen, (0,255,0), (x, y), 10)
    pygame.display.flip()
    pygame.time.wait(10)