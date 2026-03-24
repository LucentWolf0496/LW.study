import pygame
import time
import random

# 初始化pygame
pygame.init()

# 定义颜色
white = (255, 255, 255)
black = (0, 0, 0)
red = (213, 50, 80)
green = (0, 255, 0)
blue = (50, 153, 213)

# 设置显示窗口
display_width = 600
display_height = 400
dis = pygame.display.set_mode((display_width, display_height))
pygame.display.set_caption('贪吃蛇游戏 - 初学者版')

# 设置游戏时钟
clock = pygame.time.Clock()

# 蛇的大小和速度
snake_block = 10
snake_speed = 15

# 设置字体
font_style = pygame.font.SysFont(None, 30)
score_font = pygame.font.SysFont(None, 35)

# 显示得分
def show_score(score):
    value = score_font.render("得分: " + str(score), True, black)
    dis.blit(value, [10, 10])

# 绘制蛇
def our_snake(snake_block, snake_list):
    for x in snake_list:
        pygame.draw.rect(dis, green, [x[0], x[1], snake_block, snake_block])

# 显示消息
def message(msg, color):
    mesg = font_style.render(msg, True, color)
    dis.blit(mesg, [display_width / 6, display_height / 3])

# 主游戏函数
def gameLoop():
    game_over = False
    game_close = False

    # 初始化蛇的位置
    x1 = display_width / 2
    y1 = display_height / 2

    # 初始化蛇的移动方向
    x1_change = 0
    y1_change = 0

    # 初始化蛇的身体
    snake_list = []
    length_of_snake = 1

    # 随机生成食物位置
    foodx = round(random.randrange(0, display_width - snake_block) / 10.0) * 10.0
    foody = round(random.randrange(0, display_height - snake_block) / 10.0) * 10.0

    while not game_over:

        while game_close == True:
            dis.fill(white)
            message("游戏结束! 按Q退出或按C重新开始", red)
            show_score(length_of_snake - 1)
            pygame.display.update()

            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_q:
                        game_over = True
                        game_close = False
                    if event.key == pygame.K_c:
                        gameLoop()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over = True
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    x1_change = -snake_block
                    y1_change = 0
                elif event.key == pygame.K_RIGHT:
                    x1_change = snake_block
                    y1_change = 0
                elif event.key == pygame.K_UP:
                    y1_change = -snake_block
                    x1_change = 0
                elif event.key == pygame.K_DOWN:
                    y1_change = snake_block
                    x1_change = 0

        # 检查是否撞墙
        if x1 >= display_width or x1 < 0 or y1 >= display_height or y1 < 0:
            game_close = True

        # 更新蛇的位置
        x1 += x1_change
        y1 += y1_change
        dis.fill(white)
        
        # 绘制食物
        pygame.draw.rect(dis, red, [foodx, foody, snake_block, snake_block])
        
        # 更新蛇的身体
        snake_head = []
        snake_head.append(x1)
        snake_head.append(y1)
        snake_list.append(snake_head)
        
        # 如果蛇的长度超过了应有的长度，删除多余的部分
        if len(snake_list) > length_of_snake:
            del snake_list[0]

        # 检查是否撞到自己
        for x in snake_list[:-1]:
            if x == snake_head:
                game_close = True

        # 绘制蛇和显示得分
        our_snake(snake_block, snake_list)
        show_score(length_of_snake - 1)

        pygame.display.update()

        # 检查是否吃到食物
        if x1 == foodx and y1 == foody:
            foodx = round(random.randrange(0, display_width - snake_block) / 10.0) * 10.0
            foody = round(random.randrange(0, display_height - snake_block) / 10.0) * 10.0
            length_of_snake += 1

        # 控制游戏速度
        clock.tick(snake_speed)

    # 退出游戏
    pygame.quit()
    quit()

# 启动游戏
gameLoop()