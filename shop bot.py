from vkbottle.bot import Bot, Message
from vkbottle import Keyboard, KeyboardButtonColor, Text, OpenLink, EMPTY_KEYBOARD,template_gen,TemplateElement

bot = Bot(
    token="vk1.a.qYPSZT2kHDAsa8P59HoiPjhJNl77ILD8dEKjSrtg7AVtKBzREHHhe3Ab5kAp5sQb__Xa22oexT9uL-2oCCAvdVfV62z-7VWSUy8Nvsy-3m55r3BMamRY3Zpk7eLp5otQ6pR21FOxkRZB1_hYzpPhFmz35zQJnlGaQEsD1ueJjYqIZIHUkrc2lGgQ9PkS__ctiJEJ77s6_noEpDK3SgfiLQ")

@bot.on.private_message(text="menu")
@bot.on.private_message(payload={"cmd": "menu"})
async def handler(message: Message):
    keyboard = (
        Keyboard(one_time=True)
        .add(Text("tshirt", {"cmd": "Tshirt"}))
    )

    await message.answer("Bot in progress", keyboard=keyboard)



@bot.on.private_message(text="menu")
@bot.on.private_message(payload={"cmd": "Tshirt"})
async def tshirt_handler(message: Message):
    keyboard = (
        Keyboard(one_time=True)
        .add(Text("white", {"cmd": "White_Tshirt"}))
        .add(Text("black", {"cmd": "Black_Tshirt"}))
        .add(Text("blue", {"cmd": "Blue_Tshirt"}), color=KeyboardButtonColor.SECONDARY)
        .add(Text("back", {"cmd": "menu"}), color=KeyboardButtonColor.NEGATIVE)
    )

    await message.answer("Choose tshirt type", keyboard=keyboard)



@bot.on.private_message(text="menu")
@bot.on.private_message(payload={"cmd": "White_Tshirt"})
async def white_tshirt_handler(message: Message):
    keyboard1 = Keyboard().add(Text("Buy"),color=KeyboardButtonColor.POSITIVE)
    carousel = template_gen(
        TemplateElement(
            "SIGMA MALE",
            "Sigma male type t-shirt (white)",
            "-221860370_457239021",
            keyboard1.get_json()
        )
    )
    await message.answer("pizdec",template= carousel)



@bot.on.private_message(text="menu")
@bot.on.private_message(payload={"cmd": "Black_Tshirt"})
async def white_tshirt_handler(message: Message):
    keyboard = Keyboard(one_time=True).add(Text("back", {"cmd": "Tshirt"}), color=KeyboardButtonColor.NEGATIVE)
    await message.answer("out of order", keyboard=keyboard)



@bot.on.private_message(text="menu")
@bot.on.private_message(payload={"cmd": "Blue_Tshirt"})
async def white_tshirt_handler(message: Message):
    keyboard = Keyboard(one_time=True).add(Text("back", {"cmd": "Tshirt"}), color=KeyboardButtonColor.NEGATIVE)
    await message.answer("out of order", keyboard=keyboard)



bot.run_forever()
