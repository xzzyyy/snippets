from typing import Optional
from telethon import TelegramClient, events
from telethon.tl.types import User
from telethon.tl.functions.users import GetFullUserRequest

tg = TelegramClient('telegram-logger', 9240596, "85df64eb9ad4378ada1279c16eaff8f3")
user_bios = {}
cnt = [0]

tg.start()


async def get_user(user_id: int, chat_id: Optional[int] = None) -> None | User:
    try:
        if not user_id:
            return None

        try:
            return await tg.get_entity(user_id)
        except ValueError:
            if not chat_id:
                return None

            await tg.get_participants(chat_id)

            try:
                return await tg.get_entity(user_id)
            except ValueError:
                await tg.get_participants(chat_id, aggressive=True)
                try:
                    return await tg.get_entity(user_id)
                except ValueError:
                    return None
    except TypeError:
        return None


async def store_user(user):
    full_info = await tg(GetFullUserRequest(user))                      # UserFull
    about = full_info.full_user.about

    user_bios[user.id] = about.replace('\n', ' * ') if about else '-'
    full_name = (user.first_name if user.first_name else '-') + ' ' + (user.last_name if user.last_name else '-')
    print('| %d | %d | %s | %s |' % (cnt[0], user.id, full_name, user_bios[user.id]))
    cnt[0] += 1


@tg.on(events.NewMessage)
async def on_new_message(event: events.NewMessage.Event) -> None:
    msg = event.message
    chat = await tg.get_entity(msg.peer_id)                             # User, Chat or Channel
    user = await get_user(msg.from_id, chat.id if chat else None)       # User
    if not user:
        print("dbg | not user == True | msg = %s, chat = %s" % (msg, chat))
        return
    if user.id not in user_bios:
        user_bios[user.id] = ""     # to avoid adding same user several times due to parallelism
        await store_user(user)


print('started...')
print('| no | id | name | bio |')
print('|----|----|------|-----|')

tg.run_until_disconnected()
