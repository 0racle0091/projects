from vkbottle.bot import Bot, Message
from vkbottle import Keyboard, KeyboardButtonColor, Text, OpenLink, EMPTY_KEYBOARD,template_gen,TemplateElement

bot = Bot(
    token="vk1.a.qYPSZT2kHDAsa8P59HoiPjhJNl77ILD8dEKjSrtg7AVtKBzREHHhe3Ab5kAp5sQb__Xa22oexT9uL-2oCCAvdVfV62z-7VWSUy8Nvsy-3m55r3BMamRY3Zpk7eLp5otQ6pR21FOxkRZB1_hYzpPhFmz35zQJnlGaQEsD1ueJjYqIZIHUkrc2lGgQ9PkS__ctiJEJ77s6_noEpDK3SgfiLQ")

@bot.on.private_message(text="Начать")
@bot.on.private_message(payload = {"cmd": "menu"})
async def menu_handler(message: Message):
    keyboard =  keyboard = (
        Keyboard(one_time=True)
        .add(Text("Как попасть в театр?", {"cmd": "fquestion"}))
        .row()
        .add(Text("Расписания занятий", {"cmd": "squestion"}))
        .row()
        .add(Text("Дополнительные занятия", {"cmd": "tquestion"}))
        .row()
        .add(Text("Афиша", {"cmd": "foquestion"}))
        .row()
        .add(Text("Занятия для дошкольников", {"cmd": "fiquestion"}))

    )
    await message.answer("пупиду", keyboard=keyboard)


@bot.on.private_message(text="Начать")
@bot.on.private_message(payload={"cmd": "fquestion"})
async def fquestion_handler(message: Message):
    keyboard = Keyboard(one_time=True).add(Text("Назад", {"cmd": "menu"}), color=KeyboardButtonColor.NEGATIVE)
    await message.answer("про попадание в театр", keyboard=keyboard)


@bot.on.private_message(text="Начать")
@bot.on.private_message(payload={"cmd": "squestion"})
async def white_tshirt_handler(message: Message):
    keyboard = Keyboard(one_time=True).add(Text("Назад", {"cmd": "menu"}), color=KeyboardButtonColor.NEGATIVE)
    await message.answer("8:00 подьем \n 9:00 завтрак", keyboard=keyboard)


@bot.on.private_message(text="Начать")
@bot.on.private_message(payload={"cmd": "tquestion"})
async def white_tshirt_handler(message: Message):
    keyboard = Keyboard(one_time=True).add(Text("Назад", {"cmd": "menu"}), color=KeyboardButtonColor.NEGATIVE)
    await message.answer("доп занятия можно поставить у преподователей *goryachiy_meksikanec(Семён)", keyboard=keyboard)


@bot.on.private_message(text="Начать")
@bot.on.private_message(payload={"cmd": "foquestion"})
async def white_tshirt_handler(message: Message):
    keyboard = Keyboard(one_time=True).add(Text("Назад", {"cmd": "menu"}), color=KeyboardButtonColor.NEGATIVE)
    await message.answer("Ближайшие спектакли вы можете найти тут: \n https://vk.com/market-1961586", keyboard=keyboard)


@bot.on.private_message(text="Начать")
@bot.on.private_message(payload={"cmd": "fiquestion"})
async def white_tshirt_handler(message: Message):
    keyboard = Keyboard(one_time=True).add(Text("Назад", {"cmd": "menu"}), color=KeyboardButtonColor.NEGATIVE)
    await message.answer("домисолька", keyboard=keyboard)

bot.run_forever()