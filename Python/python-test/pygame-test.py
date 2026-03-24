import pygame
import sys

# 1. 初始化Pygame
pygame.init()

# 2. 设置游戏窗口
screen_width = 800
screen_height = 600
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("我的第一个游戏")

# 定义颜色 (RGB值)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)

# 玩家位置（从一个矩形开始）
player_x = 370
player_y = 480
player_width = 50
player_height = 50

# 3. 游戏主循环
clock = pygame.time.Clock()  # 用于控制帧率
running = True
while running:
    # --- 事件处理 ---
    for event in pygame.event.get():
        if event.type == pygame.QUIT:  # 点击窗口关闭按钮
            running = False
        # 键盘按下事件
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                player_x -= 10
            if event.key == pygame.K_RIGHT:
                player_x += 10

    # --- 游戏逻辑更新 ---
    # (这里可以添加碰撞检测、得分更新等)

    # --- 画面渲染 ---
    screen.fill(WHITE)                          # 用白色清屏
    pygame.draw.rect(screen, RED, (player_x, player_y, player_width, player_height)) # 画玩家
    pygame.display.flip()                        # 更新整个屏幕

    # 控制游戏帧率为60 FPS
    clock.tick(60)

# 4. 退出游戏
pygame.quit()
sys.exit()