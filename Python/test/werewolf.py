import time

def slow_print(text):
    """模拟打字效果，增加氛围"""
    for char in text:
        print(char, end='', flush=True)
        time.sleep(0.02)
    print()

def intro():
    slow_print("\n🌕 风雨呼啸的夜晚，你从泥泞中醒来。")
    slow_print("你的毛发竖起，指尖变成利爪——你是一只刚刚变身的狼人。")
    slow_print("森林在雷声中颤抖，你迷失了方向。")
    slow_print("远处传来隐约的狼嚎，左侧似乎有微弱的火光。\n")

def make_choice(options):
    """显示选项并返回用户输入"""
    for i, (key, desc) in enumerate(options.items(), 1):
        print(f"{i}. {desc}")
    choice = input("👉 你要怎么做？ (输入序号): ").strip()
    return choice

def scene_left():
    slow_print("\n你向左走去，穿过荆棘丛，看到一间破旧的小木屋。")
    slow_print("窗户里透出温暖的烛光，但门缝里飘出的是……血的味道。")
    options = {
        "1": "警惕地靠近，从窗户偷看",
        "2": "直接推门进去",
        "3": "转身离开，回到岔路口"
    }
    choice = make_choice(options)
    if choice == "1":
        slow_print("你悄悄扒在窗边，看见一个猎人正在剥狼皮。")
        slow_print("他抬头，正对上你的眼睛……")
        slow_print("🔫 一声枪响。你倒在血泊中。")
        return "bad"
    elif choice == "2":
        slow_print("你猛地推开门，猎人惊愕地举起猎枪。")
        slow_print("但你更快，一爪拍飞了枪。")
        slow_print("他颤抖着缩在墙角。你放过他，拿了些食物离开。")
        slow_print("你找到了一条出山的路，在黎明前回到了洞穴。")
        return "good"
    else:
        slow_print("你退回岔路口。")
        return None

def scene_right():
    slow_print("\n你朝狼嚎的方向奔去，雨水打在脸上。")
    slow_print("穿过一片枯木林，你看见几双幽绿的眼睛——是狼群。")
    slow_print("它们围住你，嗅了嗅，然后低吼着让开一条路。")
    slow_print("你跟着它们，来到一个隐蔽的山洞。")
    options = {
        "1": "和狼群一起进入山洞",
        "2": "怀疑有诈，独自离开"
    }
    choice = make_choice(options)
    if choice == "1":
        slow_print("山洞深处躺着受伤的老狼，它舔了舔你的爪子。")
        slow_print("你获得了狼群的信任，从此成为这片森林的守护者。")
        return "good"
    else:
        slow_print("你独自走入雨夜，越来越冷，体力渐渐不支。")
        slow_print("最终你倒在一棵老树下，再也没有醒来。")
        return "bad"

def main():
    intro()
    path = None
    while True:
        if path is None:
            options = {
                "1": "走向左侧的火光",
                "2": "追随右侧的狼嚎"
            }
            choice = make_choice(options)
            if choice == "1":
                result = scene_left()
                if result is not None:
                    break
                else:
                    path = None  # 返回路口
                    continue
            elif choice == "2":
                result = scene_right()
                break
            else:
                slow_print("请输入1或2。")
        else:
            # 处理返回路口的情况（目前只有左路可返回）
            result = scene_left()
            if result is not None:
                break

    slow_print("\n=========================")
    if result == "good":
        slow_print("🌙 结局：你活过了这个夜晚，成为了月下的传奇。")
    else:
        slow_print("💀 结局：你的故事，终结在风雨之中。")
    slow_print("=========================")

if __name__ == "__main__":
    main()