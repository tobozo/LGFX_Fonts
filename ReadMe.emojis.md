
### LGFX_Emojis

There are **1393** unique emojis in this package.
Each one is available in 8x8, 16x16, 24x24, 32x32 and 64x64, totalling **6965** png images.

## How will all this fit on flash?

The Unicode Consortium has organized all emojis in categories, groups and subgroups.

- **group**
  - group, e.g. *Smileys & Emotion*
- **subgroup**
  - sub group sub group, e.g. *face-smiling*

LGFX_Font provides the relevant declarations for each of those groups/subgroups to allow the creation of custom sets.
**Only the emojis actually selected at compile time are included in the firmware.**

Custom sets can be composed by creating one array of the following C types:

- `emoji_png_t { uint32_t code, ... }` **emoji_data**: an Emoji
- `emoji_png_set_t { emoji_png_t* emojis, size_t count }` **subgroup**: a collection of Emojis
- `emoji_png_group_t { emoji_png_set_t* subgroups, size_t count}` **group**: a collection of **subgroups**

See [`src/Fonts/emojis/emojis_structs.h`](src/Fonts/emojis/emojis_structs.h) for more details.

## Usage

For convenience, the following complete sets are available:

- `all_groups_8x8`
- `all_groups_16x16`
- `all_groups_24x24`
- `all_groups_32x32`
- `all_groups_64x64`

Some of those will only compile with big partitions though.

Loading all 24x24 emojis consumes a lot of program storage space:
```cpp
  lgfx::LGFX_Emojis::loadEmojis(&lcd, all_groups_24x24);
```

Loading all 16x16 emojis from a smaller set may save some of it:
```cpp
  lgfx::LGFX_Emojis::loadEmojis(&lcd, all_groups_16x16);
```

Loading all 8x8 emojis from an even smaller set will produce pixelated emojis:
```cpp
  lgfx::LGFX_Emojis::loadEmojis(&lcd, all_groups_8x8);
```

Mixing different sizes is okay, just create a custom set from subgroups:
```cpp
  const emoji_png_set_t emoji_subgroups[] = {subgroup_FACE_SMILING_32x32, subgroup_FACE_TONGUE_8x8, subgroup_HAND_FINGERS_OPEN_24x24, subgroup_TRANSPORT_SIGN_64x64};
  lgfx::LGFX_Emojis::loadEmojis(&lcd, emoji_subgroups);
```

Or create bigger custom sets from groups:
```cpp
  const emoji_png_group_t emoji_groups[] = { group_SMILEYS_EMOTION_64x64, group_PEOPLE_BODY_64x64 };
  lgfx::LGFX_Emojis::loadEmojis(&lcd, emoji_groups);
```

All groups/subgroups names are derived from [emojis.json](https://unpkg.com/emoji.json@16.0.0/emoji.json) package and are listed below.


## Size `8x8`

<details><summary><code>group_SMILEYS_EMOTION_8x8</code> (16 subgroups)</summary>

- `subgroup_FACE_SMILING_8x8` : 😀😃😄😁😆😅🤣😂🙂🙃🫠😉😊😇
- `subgroup_FACE_AFFECTION_8x8` : 🥰😍🤩😘😗☺😚😙🥲
- `subgroup_FACE_TONGUE_8x8` : 😋😛😜🤪😝🤑
- `subgroup_FACE_HAND_8x8` : 🤗🤭🫢🫣🤫🤔🫡
- `subgroup_FACE_NEUTRAL_SKEPTICAL_8x8` : 🤐🤨😐😑😶🫥😏😒🙄😬🤥🫨
- `subgroup_FACE_SLEEPY_8x8` : 😌😔😪🤤😴🫩
- `subgroup_FACE_UNWELL_8x8` : 😷🤒🤕🤢🤮🤧🥵🥶🥴😵🤯
- `subgroup_FACE_HAT_8x8` : 🤠🥳🥸
- `subgroup_FACE_GLASSES_8x8` : 😎🤓🧐
- `subgroup_FACE_CONCERNED_8x8` : 😕🫤😟🙁☹😮😯😲😳🥺🥹😦😧😨😰😥😢😭😱😖😣😞😓😩😫🥱
- `subgroup_FACE_NEGATIVE_8x8` : 😤😡😠🤬😈👿💀☠
- `subgroup_FACE_COSTUME_8x8` : 💩🤡👹👺👻👽👾🤖
- `subgroup_CAT_FACE_8x8` : 😺😸😹😻😼😽🙀😿😾
- `subgroup_MONKEY_FACE_8x8` : 🙈🙉🙊
- `subgroup_HEART_8x8` : 💌💘💝💖💗💓💞💕💟❣💔❤🩷🧡💛💚💙🩵💜🤎🖤🩶🤍
- `subgroup_EMOTION_8x8` : 💋💯💢💥💫💦💨🕳💬🗨🗯💭💤

</details>
<details><summary><code>group_PEOPLE_BODY_8x8</code> (16 subgroups)</summary>

- `subgroup_HAND_FINGERS_OPEN_8x8` : 👋🤚🖐✋🖖🫱🫲🫳🫴🫷🫸
- `subgroup_HAND_FINGERS_PARTIAL_8x8` : 👌🤌🤏✌🤞🫰🤟🤘🤙
- `subgroup_HAND_SINGLE_FINGER_8x8` : 👈👉👆🖕👇☝🫵
- `subgroup_HAND_FINGERS_CLOSED_8x8` : 👍👎✊👊🤛🤜
- `subgroup_HANDS_8x8` : 👏🙌🫶👐🤲🤝🙏
- `subgroup_HAND_PROP_8x8` : ✍💅🤳
- `subgroup_BODY_PARTS_8x8` : 💪🦾🦿🦵🦶👂🦻👃🧠🫀🫁🦷🦴👀👁👅👄🫦
- `subgroup_PERSON_8x8` : 👶🧒👦👧🧑👱👨🧔👩🧓👴👵
- `subgroup_PERSON_GESTURE_8x8` : 🙍🙎🙅🙆💁🙋🧏🙇🤦🤷
- `subgroup_PERSON_ROLE_8x8` : 👮🕵💂🥷👷🫅🤴👸👳👲🧕🤵👰🤰🫃🫄🤱
- `subgroup_PERSON_FANTASY_8x8` : 👼🎅🤶🦸🦹🧙🧚🧛🧜🧝🧞🧟🧌
- `subgroup_PERSON_ACTIVITY_8x8` : 💆💇🚶🧍🧎🏃💃🕺🕴👯🧖🧗
- `subgroup_PERSON_SPORT_8x8` : 🤺🏇⛷🏂🏌🏄🚣🏊⛹🏋🚴🚵🤸🤼🤽🤾🤹
- `subgroup_PERSON_RESTING_8x8` : 🧘🛀🛌
- `subgroup_FAMILY_8x8` : 👭👫👬💏💑
- `subgroup_PERSON_SYMBOL_8x8` : 🗣👤👥🫂👪👣🫆

</details>
<details><summary><code>group_COMPONENT_8x8</code> (2 subgroups)</summary>

- `subgroup_SKIN_TONE_8x8` : 🏻🏼🏽🏾🏿
- `subgroup_HAIR_STYLE_8x8` : 🦰🦱🦳🦲

</details>
<details><summary><code>group_ANIMALS_NATURE_8x8</code> (8 subgroups)</summary>

- `subgroup_ANIMAL_MAMMAL_8x8` : 🐵🐒🦍🦧🐶🐕🦮🐩🐺🦊🦝🐱🐈🦁🐯🐅🐆🐴🫎🫏🐎🦄🦓🦌🦬🐮🐂🐃🐄🐷🐖🐗🐽🐏🐑🐐🐪🐫🦙🦒🐘🦣🦏🦛🐭🐁🐀🐹🐰🐇🐿🦫🦔🦇🐻🐨🐼🦥🦦🦨🦘🦡🐾
- `subgroup_ANIMAL_BIRD_8x8` : 🦃🐔🐓🐣🐤🐥🐦🐧🕊🦅🦆🦢🦉🦤🪶🦩🦚🦜🪽🪿
- `subgroup_ANIMAL_AMPHIBIAN_8x8` : 🐸
- `subgroup_ANIMAL_REPTILE_8x8` : 🐊🐢🦎🐍🐲🐉🦕🦖
- `subgroup_ANIMAL_MARINE_8x8` : 🐳🐋🐬🦭🐟🐠🐡🦈🐙🐚🪸🪼🦀🦞🦐🦑🦪
- `subgroup_ANIMAL_BUG_8x8` : 🐌🦋🐛🐜🐝🪲🐞🦗🪳🕷🕸🦂🦟🪰🪱🦠
- `subgroup_PLANT_FLOWER_8x8` : 💐🌸💮🪷🏵🌹🥀🌺🌻🌼🌷🪻
- `subgroup_PLANT_OTHER_8x8` : 🌱🪴🌲🌳🌴🌵🌾🌿☘🍀🍁🍂🍃🪹🪺🍄🪾

</details>
<details><summary><code>group_FOOD_DRINK_8x8</code> (7 subgroups)</summary>

- `subgroup_FOOD_FRUIT_8x8` : 🍇🍈🍉🍊🍋🍌🍍🥭🍎🍏🍐🍑🍒🍓🫐🥝🍅🫒🥥
- `subgroup_FOOD_VEGETABLE_8x8` : 🥑🍆🥔🥕🌽🌶🫑🥒🥬🥦🧄🧅🥜🫘🌰🫚🫛🫜
- `subgroup_FOOD_PREPARED_8x8` : 🍞🥐🥖🫓🥨🥯🥞🧇🧀🍖🍗🥩🥓🍔🍟🍕🌭🥪🌮🌯🫔🥙🧆🥚🍳🥘🍲🫕🥣🥗🍿🧈🧂🥫
- `subgroup_FOOD_ASIAN_8x8` : 🍱🍘🍙🍚🍛🍜🍝🍠🍢🍣🍤🍥🥮🍡🥟🥠🥡
- `subgroup_FOOD_SWEET_8x8` : 🍦🍧🍨🍩🍪🎂🍰🧁🥧🍫🍬🍭🍮🍯
- `subgroup_DRINK_8x8` : 🍼🥛☕🫖🍵🍶🍾🍷🍸🍹🍺🍻🥂🥃🫗🥤🧋🧃🧉🧊
- `subgroup_DISHWARE_8x8` : 🥢🍽🍴🥄🔪🫙🏺

</details>
<details><summary><code>group_TRAVEL_PLACES_8x8</code> (11 subgroups)</summary>

- `subgroup_PLACE_MAP_8x8` : 🌍🌎🌏🌐🗺🗾🧭
- `subgroup_PLACE_GEOGRAPHIC_8x8` : 🏔⛰🌋🗻🏕🏖🏜🏝🏞
- `subgroup_PLACE_BUILDING_8x8` : 🏟🏛🏗🧱🪨🪵🛖🏘🏚🏠🏡🏢🏣🏤🏥🏦🏨🏩🏪🏫🏬🏭🏯🏰💒🗼🗽
- `subgroup_PLACE_RELIGIOUS_8x8` : ⛪🕌🛕🕍⛩🕋
- `subgroup_PLACE_OTHER_8x8` : ⛲⛺🌁🌃🏙🌄🌅🌆🌇🌉♨🎠🛝🎡🎢💈🎪
- `subgroup_TRANSPORT_GROUND_8x8` : 🚂🚃🚄🚅🚆🚇🚈🚉🚊🚝🚞🚋🚌🚍🚎🚐🚑🚒🚓🚔🚕🚖🚗🚘🚙🛻🚚🚛🚜🏎🏍🛵🦽🦼🛺🚲🛴🛹🛼🚏🛣🛤🛢⛽🛞🚨🚥🚦🛑🚧
- `subgroup_TRANSPORT_WATER_8x8` : ⚓🛟⛵🛶🚤🛳⛴🛥🚢
- `subgroup_TRANSPORT_AIR_8x8` : ✈🛩🛫🛬🪂💺🚁🚟🚠🚡🛰🚀🛸
- `subgroup_HOTEL_8x8` : 🛎🧳
- `subgroup_TIME_8x8` : ⌛⏳⌚⏰⏱⏲🕰🕛🕧🕐🕜🕑🕝🕒🕞🕓🕟🕔🕠🕕🕡🕖🕢🕗🕣🕘🕤🕙🕥🕚🕦
- `subgroup_SKY_WEATHER_8x8` : 🌑🌒🌓🌔🌕🌖🌗🌘🌙🌚🌛🌜🌡☀🌝🌞🪐⭐🌟🌠🌌☁⛅⛈🌤🌥🌦🌧🌨🌩🌪🌫🌬🌀🌈🌂☂☔⛱⚡❄☃⛄☄🔥💧🌊

</details>
<details><summary><code>group_ACTIVITIES_8x8</code> (5 subgroups)</summary>

- `subgroup_EVENT_8x8` : 🎃🎄🎆🎇🧨✨🎈🎉🎊🎋🎍🎎🎏🎐🎑🧧🎀🎁🎗🎟🎫
- `subgroup_AWARD_MEDAL_8x8` : 🎖🏆🏅🥇🥈🥉
- `subgroup_SPORT_8x8` : ⚽⚾🥎🏀🏐🏈🏉🎾🥏🎳🏏🏑🏒🥍🏓🏸🥊🥋🥅⛳⛸🎣🤿🎽🎿🛷🥌
- `subgroup_GAME_8x8` : 🎯🪀🪁🔫🎱🔮🪄🎮🕹🎰🎲🧩🧸🪅🪩🪆♠♥♦♣♟🃏🀄🎴
- `subgroup_ARTS_CRAFTS_8x8` : 🎭🖼🎨🧵🪡🧶🪢

</details>
<details><summary><code>group_OBJECTS_8x8</code> (18 subgroups)</summary>

- `subgroup_CLOTHING_8x8` : 👓🕶🥽🥼🦺👔👕👖🧣🧤🧥🧦👗👘🥻🩱🩲🩳👙👚🪭👛👜👝🛍🎒🩴👞👟🥾🥿👠👡🩰👢🪮👑👒🎩🎓🧢🪖⛑📿💄💍💎
- `subgroup_SOUND_8x8` : 🔇🔈🔉🔊📢📣📯🔔🔕
- `subgroup_MUSIC_8x8` : 🎼🎵🎶🎙🎚🎛🎤🎧📻
- `subgroup_MUSICAL_INSTRUMENT_8x8` : 🎷🪗🎸🎹🎺🎻🪕🥁🪘🪇🪈🪉
- `subgroup_PHONE_8x8` : 📱📲☎📞📟📠
- `subgroup_COMPUTER_8x8` : 🔋🪫🔌💻🖥🖨⌨🖱🖲💽💾💿📀🧮
- `subgroup_LIGHT_VIDEO_8x8` : 🎥🎞📽🎬📺📷📸📹📼🔍🔎🕯💡🔦🏮🪔
- `subgroup_BOOK_PAPER_8x8` : 📔📕📖📗📘📙📚📓📒📃📜📄📰🗞📑🔖🏷
- `subgroup_MONEY_8x8` : 💰🪙💴💵💶💷💸💳🧾💹
- `subgroup_MAIL_8x8` : ✉📧📨📩📤📥📦📫📪📬📭📮🗳
- `subgroup_WRITING_8x8` : ✏✒🖋🖊🖌🖍📝
- `subgroup_OFFICE_8x8` : 💼📁📂🗂📅📆🗒🗓📇📈📉📊📋📌📍📎🖇📏📐✂🗃🗄🗑
- `subgroup_LOCK_8x8` : 🔒🔓🔏🔐🔑🗝
- `subgroup_TOOL_8x8` : 🔨🪓⛏⚒🛠🗡⚔💣🪃🏹🛡🪚🔧🪛🔩⚙🗜⚖🦯🔗⛓🪝🧰🧲🪜🪏
- `subgroup_SCIENCE_8x8` : ⚗🧪🧫🧬🔬🔭📡
- `subgroup_MEDICAL_8x8` : 💉🩸💊🩹🩼🩺🩻
- `subgroup_HOUSEHOLD_8x8` : 🚪🛗🪞🪟🛏🛋🪑🚽🪠🚿🛁🪤🪒🧴🧷🧹🧺🧻🪣🧼🫧🪥🧽🧯🛒
- `subgroup_OTHER_OBJECT_8x8` : 🚬⚰🪦⚱🧿🪬🗿🪧🪪

</details>
<details><summary><code>group_SYMBOLS_8x8</code> (14 subgroups)</summary>

- `subgroup_TRANSPORT_SIGN_8x8` : 🏧🚮🚰♿🚹🚺🚻🚼🚾🛂🛃🛄🛅
- `subgroup_WARNING_8x8` : ⚠🚸⛔🚫🚳🚭🚯🚱🚷📵🔞☢☣
- `subgroup_ARROW_8x8` : ⬆↗➡↘⬇↙⬅↖↕↔↩↪⤴⤵🔃🔄🔙🔚🔛🔜🔝
- `subgroup_RELIGION_8x8` : 🛐⚛🕉✡☸☯✝☦☪☮🕎🔯🪯
- `subgroup_ZODIAC_8x8` : ♈♉♊♋♌♍♎♏♐♑♒♓⛎
- `subgroup_AV_SYMBOL_8x8` : 🔀🔁🔂▶⏩⏭⏯◀⏪⏮🔼⏫🔽⏬⏸⏹⏺⏏🎦🔅🔆📶🛜📳📴
- `subgroup_GENDER_8x8` : ♀♂⚧
- `subgroup_MATH_8x8` : ✖➕➖➗🟰♾
- `subgroup_PUNCTUATION_8x8` : ‼⁉❓❔❕❗〰
- `subgroup_CURRENCY_8x8` : 💱💲
- `subgroup_OTHER_SYMBOL_8x8` : ⚕♻⚜🔱📛🔰⭕✅☑✔❌❎➰➿〽✳✴❇©®™🫟
- `subgroup_KEYCAP_8x8` : 🔟
- `subgroup_ALPHANUM_8x8` : 🔠🔡🔢🔣🔤🅰🆎🅱🆑🆒🆓ℹ🆔Ⓜ🆕🆖🅾🆗🅿🆘🆙🆚🈁🈂🈷🈶🈯🉐🈹🈚🈲🉑🈸🈴🈳㊗㊙🈺🈵
- `subgroup_GEOMETRIC_8x8` : 🔴🟠🟡🟢🔵🟣🟤⚫⚪🟥🟧🟨🟩🟦🟪🟫⬛⬜◼◻◾◽▪▫🔶🔷🔸🔹🔺🔻💠🔘🔳🔲

</details>
<details><summary><code>group_FLAGS_8x8</code> (1 subgroup)</summary>

- `subgroup_FLAG_8x8` : 🏁🚩🎌🏴🏳

</details>

## Size `16x16`

<details><summary><code>group_SMILEYS_EMOTION_16x16</code> (16 subgroups)</summary>

- `subgroup_FACE_SMILING_16x16` : 😀😃😄😁😆😅🤣😂🙂🙃🫠😉😊😇
- `subgroup_FACE_AFFECTION_16x16` : 🥰😍🤩😘😗☺😚😙🥲
- `subgroup_FACE_TONGUE_16x16` : 😋😛😜🤪😝🤑
- `subgroup_FACE_HAND_16x16` : 🤗🤭🫢🫣🤫🤔🫡
- `subgroup_FACE_NEUTRAL_SKEPTICAL_16x16` : 🤐🤨😐😑😶🫥😏😒🙄😬🤥🫨
- `subgroup_FACE_SLEEPY_16x16` : 😌😔😪🤤😴🫩
- `subgroup_FACE_UNWELL_16x16` : 😷🤒🤕🤢🤮🤧🥵🥶🥴😵🤯
- `subgroup_FACE_HAT_16x16` : 🤠🥳🥸
- `subgroup_FACE_GLASSES_16x16` : 😎🤓🧐
- `subgroup_FACE_CONCERNED_16x16` : 😕🫤😟🙁☹😮😯😲😳🥺🥹😦😧😨😰😥😢😭😱😖😣😞😓😩😫🥱
- `subgroup_FACE_NEGATIVE_16x16` : 😤😡😠🤬😈👿💀☠
- `subgroup_FACE_COSTUME_16x16` : 💩🤡👹👺👻👽👾🤖
- `subgroup_CAT_FACE_16x16` : 😺😸😹😻😼😽🙀😿😾
- `subgroup_MONKEY_FACE_16x16` : 🙈🙉🙊
- `subgroup_HEART_16x16` : 💌💘💝💖💗💓💞💕💟❣💔❤🩷🧡💛💚💙🩵💜🤎🖤🩶🤍
- `subgroup_EMOTION_16x16` : 💋💯💢💥💫💦💨🕳💬🗨🗯💭💤

</details>
<details><summary><code>group_PEOPLE_BODY_16x16</code> (16 subgroups)</summary>

- `subgroup_HAND_FINGERS_OPEN_16x16` : 👋🤚🖐✋🖖🫱🫲🫳🫴🫷🫸
- `subgroup_HAND_FINGERS_PARTIAL_16x16` : 👌🤌🤏✌🤞🫰🤟🤘🤙
- `subgroup_HAND_SINGLE_FINGER_16x16` : 👈👉👆🖕👇☝🫵
- `subgroup_HAND_FINGERS_CLOSED_16x16` : 👍👎✊👊🤛🤜
- `subgroup_HANDS_16x16` : 👏🙌🫶👐🤲🤝🙏
- `subgroup_HAND_PROP_16x16` : ✍💅🤳
- `subgroup_BODY_PARTS_16x16` : 💪🦾🦿🦵🦶👂🦻👃🧠🫀🫁🦷🦴👀👁👅👄🫦
- `subgroup_PERSON_16x16` : 👶🧒👦👧🧑👱👨🧔👩🧓👴👵
- `subgroup_PERSON_GESTURE_16x16` : 🙍🙎🙅🙆💁🙋🧏🙇🤦🤷
- `subgroup_PERSON_ROLE_16x16` : 👮🕵💂🥷👷🫅🤴👸👳👲🧕🤵👰🤰🫃🫄🤱
- `subgroup_PERSON_FANTASY_16x16` : 👼🎅🤶🦸🦹🧙🧚🧛🧜🧝🧞🧟🧌
- `subgroup_PERSON_ACTIVITY_16x16` : 💆💇🚶🧍🧎🏃💃🕺🕴👯🧖🧗
- `subgroup_PERSON_SPORT_16x16` : 🤺🏇⛷🏂🏌🏄🚣🏊⛹🏋🚴🚵🤸🤼🤽🤾🤹
- `subgroup_PERSON_RESTING_16x16` : 🧘🛀🛌
- `subgroup_FAMILY_16x16` : 👭👫👬💏💑
- `subgroup_PERSON_SYMBOL_16x16` : 🗣👤👥🫂👪👣🫆

</details>
<details><summary><code>group_COMPONENT_16x16</code> (2 subgroups)</summary>

- `subgroup_SKIN_TONE_16x16` : 🏻🏼🏽🏾🏿
- `subgroup_HAIR_STYLE_16x16` : 🦰🦱🦳🦲

</details>
<details><summary><code>group_ANIMALS_NATURE_16x16</code> (8 subgroups)</summary>

- `subgroup_ANIMAL_MAMMAL_16x16` : 🐵🐒🦍🦧🐶🐕🦮🐩🐺🦊🦝🐱🐈🦁🐯🐅🐆🐴🫎🫏🐎🦄🦓🦌🦬🐮🐂🐃🐄🐷🐖🐗🐽🐏🐑🐐🐪🐫🦙🦒🐘🦣🦏🦛🐭🐁🐀🐹🐰🐇🐿🦫🦔🦇🐻🐨🐼🦥🦦🦨🦘🦡🐾
- `subgroup_ANIMAL_BIRD_16x16` : 🦃🐔🐓🐣🐤🐥🐦🐧🕊🦅🦆🦢🦉🦤🪶🦩🦚🦜🪽🪿
- `subgroup_ANIMAL_AMPHIBIAN_16x16` : 🐸
- `subgroup_ANIMAL_REPTILE_16x16` : 🐊🐢🦎🐍🐲🐉🦕🦖
- `subgroup_ANIMAL_MARINE_16x16` : 🐳🐋🐬🦭🐟🐠🐡🦈🐙🐚🪸🪼🦀🦞🦐🦑🦪
- `subgroup_ANIMAL_BUG_16x16` : 🐌🦋🐛🐜🐝🪲🐞🦗🪳🕷🕸🦂🦟🪰🪱🦠
- `subgroup_PLANT_FLOWER_16x16` : 💐🌸💮🪷🏵🌹🥀🌺🌻🌼🌷🪻
- `subgroup_PLANT_OTHER_16x16` : 🌱🪴🌲🌳🌴🌵🌾🌿☘🍀🍁🍂🍃🪹🪺🍄🪾

</details>
<details><summary><code>group_FOOD_DRINK_16x16</code> (7 subgroups)</summary>

- `subgroup_FOOD_FRUIT_16x16` : 🍇🍈🍉🍊🍋🍌🍍🥭🍎🍏🍐🍑🍒🍓🫐🥝🍅🫒🥥
- `subgroup_FOOD_VEGETABLE_16x16` : 🥑🍆🥔🥕🌽🌶🫑🥒🥬🥦🧄🧅🥜🫘🌰🫚🫛🫜
- `subgroup_FOOD_PREPARED_16x16` : 🍞🥐🥖🫓🥨🥯🥞🧇🧀🍖🍗🥩🥓🍔🍟🍕🌭🥪🌮🌯🫔🥙🧆🥚🍳🥘🍲🫕🥣🥗🍿🧈🧂🥫
- `subgroup_FOOD_ASIAN_16x16` : 🍱🍘🍙🍚🍛🍜🍝🍠🍢🍣🍤🍥🥮🍡🥟🥠🥡
- `subgroup_FOOD_SWEET_16x16` : 🍦🍧🍨🍩🍪🎂🍰🧁🥧🍫🍬🍭🍮🍯
- `subgroup_DRINK_16x16` : 🍼🥛☕🫖🍵🍶🍾🍷🍸🍹🍺🍻🥂🥃🫗🥤🧋🧃🧉🧊
- `subgroup_DISHWARE_16x16` : 🥢🍽🍴🥄🔪🫙🏺

</details>
<details><summary><code>group_TRAVEL_PLACES_16x16</code> (11 subgroups)</summary>

- `subgroup_PLACE_MAP_16x16` : 🌍🌎🌏🌐🗺🗾🧭
- `subgroup_PLACE_GEOGRAPHIC_16x16` : 🏔⛰🌋🗻🏕🏖🏜🏝🏞
- `subgroup_PLACE_BUILDING_16x16` : 🏟🏛🏗🧱🪨🪵🛖🏘🏚🏠🏡🏢🏣🏤🏥🏦🏨🏩🏪🏫🏬🏭🏯🏰💒🗼🗽
- `subgroup_PLACE_RELIGIOUS_16x16` : ⛪🕌🛕🕍⛩🕋
- `subgroup_PLACE_OTHER_16x16` : ⛲⛺🌁🌃🏙🌄🌅🌆🌇🌉♨🎠🛝🎡🎢💈🎪
- `subgroup_TRANSPORT_GROUND_16x16` : 🚂🚃🚄🚅🚆🚇🚈🚉🚊🚝🚞🚋🚌🚍🚎🚐🚑🚒🚓🚔🚕🚖🚗🚘🚙🛻🚚🚛🚜🏎🏍🛵🦽🦼🛺🚲🛴🛹🛼🚏🛣🛤🛢⛽🛞🚨🚥🚦🛑🚧
- `subgroup_TRANSPORT_WATER_16x16` : ⚓🛟⛵🛶🚤🛳⛴🛥🚢
- `subgroup_TRANSPORT_AIR_16x16` : ✈🛩🛫🛬🪂💺🚁🚟🚠🚡🛰🚀🛸
- `subgroup_HOTEL_16x16` : 🛎🧳
- `subgroup_TIME_16x16` : ⌛⏳⌚⏰⏱⏲🕰🕛🕧🕐🕜🕑🕝🕒🕞🕓🕟🕔🕠🕕🕡🕖🕢🕗🕣🕘🕤🕙🕥🕚🕦
- `subgroup_SKY_WEATHER_16x16` : 🌑🌒🌓🌔🌕🌖🌗🌘🌙🌚🌛🌜🌡☀🌝🌞🪐⭐🌟🌠🌌☁⛅⛈🌤🌥🌦🌧🌨🌩🌪🌫🌬🌀🌈🌂☂☔⛱⚡❄☃⛄☄🔥💧🌊

</details>
<details><summary><code>group_ACTIVITIES_16x16</code> (5 subgroups)</summary>

- `subgroup_EVENT_16x16` : 🎃🎄🎆🎇🧨✨🎈🎉🎊🎋🎍🎎🎏🎐🎑🧧🎀🎁🎗🎟🎫
- `subgroup_AWARD_MEDAL_16x16` : 🎖🏆🏅🥇🥈🥉
- `subgroup_SPORT_16x16` : ⚽⚾🥎🏀🏐🏈🏉🎾🥏🎳🏏🏑🏒🥍🏓🏸🥊🥋🥅⛳⛸🎣🤿🎽🎿🛷🥌
- `subgroup_GAME_16x16` : 🎯🪀🪁🔫🎱🔮🪄🎮🕹🎰🎲🧩🧸🪅🪩🪆♠♥♦♣♟🃏🀄🎴
- `subgroup_ARTS_CRAFTS_16x16` : 🎭🖼🎨🧵🪡🧶🪢

</details>
<details><summary><code>group_OBJECTS_16x16</code> (18 subgroups)</summary>

- `subgroup_CLOTHING_16x16` : 👓🕶🥽🥼🦺👔👕👖🧣🧤🧥🧦👗👘🥻🩱🩲🩳👙👚🪭👛👜👝🛍🎒🩴👞👟🥾🥿👠👡🩰👢🪮👑👒🎩🎓🧢🪖⛑📿💄💍💎
- `subgroup_SOUND_16x16` : 🔇🔈🔉🔊📢📣📯🔔🔕
- `subgroup_MUSIC_16x16` : 🎼🎵🎶🎙🎚🎛🎤🎧📻
- `subgroup_MUSICAL_INSTRUMENT_16x16` : 🎷🪗🎸🎹🎺🎻🪕🥁🪘🪇🪈🪉
- `subgroup_PHONE_16x16` : 📱📲☎📞📟📠
- `subgroup_COMPUTER_16x16` : 🔋🪫🔌💻🖥🖨⌨🖱🖲💽💾💿📀🧮
- `subgroup_LIGHT_VIDEO_16x16` : 🎥🎞📽🎬📺📷📸📹📼🔍🔎🕯💡🔦🏮🪔
- `subgroup_BOOK_PAPER_16x16` : 📔📕📖📗📘📙📚📓📒📃📜📄📰🗞📑🔖🏷
- `subgroup_MONEY_16x16` : 💰🪙💴💵💶💷💸💳🧾💹
- `subgroup_MAIL_16x16` : ✉📧📨📩📤📥📦📫📪📬📭📮🗳
- `subgroup_WRITING_16x16` : ✏✒🖋🖊🖌🖍📝
- `subgroup_OFFICE_16x16` : 💼📁📂🗂📅📆🗒🗓📇📈📉📊📋📌📍📎🖇📏📐✂🗃🗄🗑
- `subgroup_LOCK_16x16` : 🔒🔓🔏🔐🔑🗝
- `subgroup_TOOL_16x16` : 🔨🪓⛏⚒🛠🗡⚔💣🪃🏹🛡🪚🔧🪛🔩⚙🗜⚖🦯🔗⛓🪝🧰🧲🪜🪏
- `subgroup_SCIENCE_16x16` : ⚗🧪🧫🧬🔬🔭📡
- `subgroup_MEDICAL_16x16` : 💉🩸💊🩹🩼🩺🩻
- `subgroup_HOUSEHOLD_16x16` : 🚪🛗🪞🪟🛏🛋🪑🚽🪠🚿🛁🪤🪒🧴🧷🧹🧺🧻🪣🧼🫧🪥🧽🧯🛒
- `subgroup_OTHER_OBJECT_16x16` : 🚬⚰🪦⚱🧿🪬🗿🪧🪪

</details>
<details><summary><code>group_SYMBOLS_16x16</code> (14 subgroups)</summary>

- `subgroup_TRANSPORT_SIGN_16x16` : 🏧🚮🚰♿🚹🚺🚻🚼🚾🛂🛃🛄🛅
- `subgroup_WARNING_16x16` : ⚠🚸⛔🚫🚳🚭🚯🚱🚷📵🔞☢☣
- `subgroup_ARROW_16x16` : ⬆↗➡↘⬇↙⬅↖↕↔↩↪⤴⤵🔃🔄🔙🔚🔛🔜🔝
- `subgroup_RELIGION_16x16` : 🛐⚛🕉✡☸☯✝☦☪☮🕎🔯🪯
- `subgroup_ZODIAC_16x16` : ♈♉♊♋♌♍♎♏♐♑♒♓⛎
- `subgroup_AV_SYMBOL_16x16` : 🔀🔁🔂▶⏩⏭⏯◀⏪⏮🔼⏫🔽⏬⏸⏹⏺⏏🎦🔅🔆📶🛜📳📴
- `subgroup_GENDER_16x16` : ♀♂⚧
- `subgroup_MATH_16x16` : ✖➕➖➗🟰♾
- `subgroup_PUNCTUATION_16x16` : ‼⁉❓❔❕❗〰
- `subgroup_CURRENCY_16x16` : 💱💲
- `subgroup_OTHER_SYMBOL_16x16` : ⚕♻⚜🔱📛🔰⭕✅☑✔❌❎➰➿〽✳✴❇©®™🫟
- `subgroup_KEYCAP_16x16` : 🔟
- `subgroup_ALPHANUM_16x16` : 🔠🔡🔢🔣🔤🅰🆎🅱🆑🆒🆓ℹ🆔Ⓜ🆕🆖🅾🆗🅿🆘🆙🆚🈁🈂🈷🈶🈯🉐🈹🈚🈲🉑🈸🈴🈳㊗㊙🈺🈵
- `subgroup_GEOMETRIC_16x16` : 🔴🟠🟡🟢🔵🟣🟤⚫⚪🟥🟧🟨🟩🟦🟪🟫⬛⬜◼◻◾◽▪▫🔶🔷🔸🔹🔺🔻💠🔘🔳🔲

</details>
<details><summary><code>group_FLAGS_16x16</code> (1 subgroup)</summary>

- `subgroup_FLAG_16x16` : 🏁🚩🎌🏴🏳

</details>

## Size `24x24`

<details><summary><code>group_SMILEYS_EMOTION_24x24</code> (16 subgroups)</summary>

- `subgroup_FACE_SMILING_24x24` : 😀😃😄😁😆😅🤣😂🙂🙃🫠😉😊😇
- `subgroup_FACE_AFFECTION_24x24` : 🥰😍🤩😘😗☺😚😙🥲
- `subgroup_FACE_TONGUE_24x24` : 😋😛😜🤪😝🤑
- `subgroup_FACE_HAND_24x24` : 🤗🤭🫢🫣🤫🤔🫡
- `subgroup_FACE_NEUTRAL_SKEPTICAL_24x24` : 🤐🤨😐😑😶🫥😏😒🙄😬🤥🫨
- `subgroup_FACE_SLEEPY_24x24` : 😌😔😪🤤😴🫩
- `subgroup_FACE_UNWELL_24x24` : 😷🤒🤕🤢🤮🤧🥵🥶🥴😵🤯
- `subgroup_FACE_HAT_24x24` : 🤠🥳🥸
- `subgroup_FACE_GLASSES_24x24` : 😎🤓🧐
- `subgroup_FACE_CONCERNED_24x24` : 😕🫤😟🙁☹😮😯😲😳🥺🥹😦😧😨😰😥😢😭😱😖😣😞😓😩😫🥱
- `subgroup_FACE_NEGATIVE_24x24` : 😤😡😠🤬😈👿💀☠
- `subgroup_FACE_COSTUME_24x24` : 💩🤡👹👺👻👽👾🤖
- `subgroup_CAT_FACE_24x24` : 😺😸😹😻😼😽🙀😿😾
- `subgroup_MONKEY_FACE_24x24` : 🙈🙉🙊
- `subgroup_HEART_24x24` : 💌💘💝💖💗💓💞💕💟❣💔❤🩷🧡💛💚💙🩵💜🤎🖤🩶🤍
- `subgroup_EMOTION_24x24` : 💋💯💢💥💫💦💨🕳💬🗨🗯💭💤

</details>
<details><summary><code>group_PEOPLE_BODY_24x24</code> (16 subgroups)</summary>

- `subgroup_HAND_FINGERS_OPEN_24x24` : 👋🤚🖐✋🖖🫱🫲🫳🫴🫷🫸
- `subgroup_HAND_FINGERS_PARTIAL_24x24` : 👌🤌🤏✌🤞🫰🤟🤘🤙
- `subgroup_HAND_SINGLE_FINGER_24x24` : 👈👉👆🖕👇☝🫵
- `subgroup_HAND_FINGERS_CLOSED_24x24` : 👍👎✊👊🤛🤜
- `subgroup_HANDS_24x24` : 👏🙌🫶👐🤲🤝🙏
- `subgroup_HAND_PROP_24x24` : ✍💅🤳
- `subgroup_BODY_PARTS_24x24` : 💪🦾🦿🦵🦶👂🦻👃🧠🫀🫁🦷🦴👀👁👅👄🫦
- `subgroup_PERSON_24x24` : 👶🧒👦👧🧑👱👨🧔👩🧓👴👵
- `subgroup_PERSON_GESTURE_24x24` : 🙍🙎🙅🙆💁🙋🧏🙇🤦🤷
- `subgroup_PERSON_ROLE_24x24` : 👮🕵💂🥷👷🫅🤴👸👳👲🧕🤵👰🤰🫃🫄🤱
- `subgroup_PERSON_FANTASY_24x24` : 👼🎅🤶🦸🦹🧙🧚🧛🧜🧝🧞🧟🧌
- `subgroup_PERSON_ACTIVITY_24x24` : 💆💇🚶🧍🧎🏃💃🕺🕴👯🧖🧗
- `subgroup_PERSON_SPORT_24x24` : 🤺🏇⛷🏂🏌🏄🚣🏊⛹🏋🚴🚵🤸🤼🤽🤾🤹
- `subgroup_PERSON_RESTING_24x24` : 🧘🛀🛌
- `subgroup_FAMILY_24x24` : 👭👫👬💏💑
- `subgroup_PERSON_SYMBOL_24x24` : 🗣👤👥🫂👪👣🫆

</details>
<details><summary><code>group_COMPONENT_24x24</code> (2 subgroups)</summary>

- `subgroup_SKIN_TONE_24x24` : 🏻🏼🏽🏾🏿
- `subgroup_HAIR_STYLE_24x24` : 🦰🦱🦳🦲

</details>
<details><summary><code>group_ANIMALS_NATURE_24x24</code> (8 subgroups)</summary>

- `subgroup_ANIMAL_MAMMAL_24x24` : 🐵🐒🦍🦧🐶🐕🦮🐩🐺🦊🦝🐱🐈🦁🐯🐅🐆🐴🫎🫏🐎🦄🦓🦌🦬🐮🐂🐃🐄🐷🐖🐗🐽🐏🐑🐐🐪🐫🦙🦒🐘🦣🦏🦛🐭🐁🐀🐹🐰🐇🐿🦫🦔🦇🐻🐨🐼🦥🦦🦨🦘🦡🐾
- `subgroup_ANIMAL_BIRD_24x24` : 🦃🐔🐓🐣🐤🐥🐦🐧🕊🦅🦆🦢🦉🦤🪶🦩🦚🦜🪽🪿
- `subgroup_ANIMAL_AMPHIBIAN_24x24` : 🐸
- `subgroup_ANIMAL_REPTILE_24x24` : 🐊🐢🦎🐍🐲🐉🦕🦖
- `subgroup_ANIMAL_MARINE_24x24` : 🐳🐋🐬🦭🐟🐠🐡🦈🐙🐚🪸🪼🦀🦞🦐🦑🦪
- `subgroup_ANIMAL_BUG_24x24` : 🐌🦋🐛🐜🐝🪲🐞🦗🪳🕷🕸🦂🦟🪰🪱🦠
- `subgroup_PLANT_FLOWER_24x24` : 💐🌸💮🪷🏵🌹🥀🌺🌻🌼🌷🪻
- `subgroup_PLANT_OTHER_24x24` : 🌱🪴🌲🌳🌴🌵🌾🌿☘🍀🍁🍂🍃🪹🪺🍄🪾

</details>
<details><summary><code>group_FOOD_DRINK_24x24</code> (7 subgroups)</summary>

- `subgroup_FOOD_FRUIT_24x24` : 🍇🍈🍉🍊🍋🍌🍍🥭🍎🍏🍐🍑🍒🍓🫐🥝🍅🫒🥥
- `subgroup_FOOD_VEGETABLE_24x24` : 🥑🍆🥔🥕🌽🌶🫑🥒🥬🥦🧄🧅🥜🫘🌰🫚🫛🫜
- `subgroup_FOOD_PREPARED_24x24` : 🍞🥐🥖🫓🥨🥯🥞🧇🧀🍖🍗🥩🥓🍔🍟🍕🌭🥪🌮🌯🫔🥙🧆🥚🍳🥘🍲🫕🥣🥗🍿🧈🧂🥫
- `subgroup_FOOD_ASIAN_24x24` : 🍱🍘🍙🍚🍛🍜🍝🍠🍢🍣🍤🍥🥮🍡🥟🥠🥡
- `subgroup_FOOD_SWEET_24x24` : 🍦🍧🍨🍩🍪🎂🍰🧁🥧🍫🍬🍭🍮🍯
- `subgroup_DRINK_24x24` : 🍼🥛☕🫖🍵🍶🍾🍷🍸🍹🍺🍻🥂🥃🫗🥤🧋🧃🧉🧊
- `subgroup_DISHWARE_24x24` : 🥢🍽🍴🥄🔪🫙🏺

</details>
<details><summary><code>group_TRAVEL_PLACES_24x24</code> (11 subgroups)</summary>

- `subgroup_PLACE_MAP_24x24` : 🌍🌎🌏🌐🗺🗾🧭
- `subgroup_PLACE_GEOGRAPHIC_24x24` : 🏔⛰🌋🗻🏕🏖🏜🏝🏞
- `subgroup_PLACE_BUILDING_24x24` : 🏟🏛🏗🧱🪨🪵🛖🏘🏚🏠🏡🏢🏣🏤🏥🏦🏨🏩🏪🏫🏬🏭🏯🏰💒🗼🗽
- `subgroup_PLACE_RELIGIOUS_24x24` : ⛪🕌🛕🕍⛩🕋
- `subgroup_PLACE_OTHER_24x24` : ⛲⛺🌁🌃🏙🌄🌅🌆🌇🌉♨🎠🛝🎡🎢💈🎪
- `subgroup_TRANSPORT_GROUND_24x24` : 🚂🚃🚄🚅🚆🚇🚈🚉🚊🚝🚞🚋🚌🚍🚎🚐🚑🚒🚓🚔🚕🚖🚗🚘🚙🛻🚚🚛🚜🏎🏍🛵🦽🦼🛺🚲🛴🛹🛼🚏🛣🛤🛢⛽🛞🚨🚥🚦🛑🚧
- `subgroup_TRANSPORT_WATER_24x24` : ⚓🛟⛵🛶🚤🛳⛴🛥🚢
- `subgroup_TRANSPORT_AIR_24x24` : ✈🛩🛫🛬🪂💺🚁🚟🚠🚡🛰🚀🛸
- `subgroup_HOTEL_24x24` : 🛎🧳
- `subgroup_TIME_24x24` : ⌛⏳⌚⏰⏱⏲🕰🕛🕧🕐🕜🕑🕝🕒🕞🕓🕟🕔🕠🕕🕡🕖🕢🕗🕣🕘🕤🕙🕥🕚🕦
- `subgroup_SKY_WEATHER_24x24` : 🌑🌒🌓🌔🌕🌖🌗🌘🌙🌚🌛🌜🌡☀🌝🌞🪐⭐🌟🌠🌌☁⛅⛈🌤🌥🌦🌧🌨🌩🌪🌫🌬🌀🌈🌂☂☔⛱⚡❄☃⛄☄🔥💧🌊

</details>
<details><summary><code>group_ACTIVITIES_24x24</code> (5 subgroups)</summary>

- `subgroup_EVENT_24x24` : 🎃🎄🎆🎇🧨✨🎈🎉🎊🎋🎍🎎🎏🎐🎑🧧🎀🎁🎗🎟🎫
- `subgroup_AWARD_MEDAL_24x24` : 🎖🏆🏅🥇🥈🥉
- `subgroup_SPORT_24x24` : ⚽⚾🥎🏀🏐🏈🏉🎾🥏🎳🏏🏑🏒🥍🏓🏸🥊🥋🥅⛳⛸🎣🤿🎽🎿🛷🥌
- `subgroup_GAME_24x24` : 🎯🪀🪁🔫🎱🔮🪄🎮🕹🎰🎲🧩🧸🪅🪩🪆♠♥♦♣♟🃏🀄🎴
- `subgroup_ARTS_CRAFTS_24x24` : 🎭🖼🎨🧵🪡🧶🪢

</details>
<details><summary><code>group_OBJECTS_24x24</code> (18 subgroups)</summary>

- `subgroup_CLOTHING_24x24` : 👓🕶🥽🥼🦺👔👕👖🧣🧤🧥🧦👗👘🥻🩱🩲🩳👙👚🪭👛👜👝🛍🎒🩴👞👟🥾🥿👠👡🩰👢🪮👑👒🎩🎓🧢🪖⛑📿💄💍💎
- `subgroup_SOUND_24x24` : 🔇🔈🔉🔊📢📣📯🔔🔕
- `subgroup_MUSIC_24x24` : 🎼🎵🎶🎙🎚🎛🎤🎧📻
- `subgroup_MUSICAL_INSTRUMENT_24x24` : 🎷🪗🎸🎹🎺🎻🪕🥁🪘🪇🪈🪉
- `subgroup_PHONE_24x24` : 📱📲☎📞📟📠
- `subgroup_COMPUTER_24x24` : 🔋🪫🔌💻🖥🖨⌨🖱🖲💽💾💿📀🧮
- `subgroup_LIGHT_VIDEO_24x24` : 🎥🎞📽🎬📺📷📸📹📼🔍🔎🕯💡🔦🏮🪔
- `subgroup_BOOK_PAPER_24x24` : 📔📕📖📗📘📙📚📓📒📃📜📄📰🗞📑🔖🏷
- `subgroup_MONEY_24x24` : 💰🪙💴💵💶💷💸💳🧾💹
- `subgroup_MAIL_24x24` : ✉📧📨📩📤📥📦📫📪📬📭📮🗳
- `subgroup_WRITING_24x24` : ✏✒🖋🖊🖌🖍📝
- `subgroup_OFFICE_24x24` : 💼📁📂🗂📅📆🗒🗓📇📈📉📊📋📌📍📎🖇📏📐✂🗃🗄🗑
- `subgroup_LOCK_24x24` : 🔒🔓🔏🔐🔑🗝
- `subgroup_TOOL_24x24` : 🔨🪓⛏⚒🛠🗡⚔💣🪃🏹🛡🪚🔧🪛🔩⚙🗜⚖🦯🔗⛓🪝🧰🧲🪜🪏
- `subgroup_SCIENCE_24x24` : ⚗🧪🧫🧬🔬🔭📡
- `subgroup_MEDICAL_24x24` : 💉🩸💊🩹🩼🩺🩻
- `subgroup_HOUSEHOLD_24x24` : 🚪🛗🪞🪟🛏🛋🪑🚽🪠🚿🛁🪤🪒🧴🧷🧹🧺🧻🪣🧼🫧🪥🧽🧯🛒
- `subgroup_OTHER_OBJECT_24x24` : 🚬⚰🪦⚱🧿🪬🗿🪧🪪

</details>
<details><summary><code>group_SYMBOLS_24x24</code> (14 subgroups)</summary>

- `subgroup_TRANSPORT_SIGN_24x24` : 🏧🚮🚰♿🚹🚺🚻🚼🚾🛂🛃🛄🛅
- `subgroup_WARNING_24x24` : ⚠🚸⛔🚫🚳🚭🚯🚱🚷📵🔞☢☣
- `subgroup_ARROW_24x24` : ⬆↗➡↘⬇↙⬅↖↕↔↩↪⤴⤵🔃🔄🔙🔚🔛🔜🔝
- `subgroup_RELIGION_24x24` : 🛐⚛🕉✡☸☯✝☦☪☮🕎🔯🪯
- `subgroup_ZODIAC_24x24` : ♈♉♊♋♌♍♎♏♐♑♒♓⛎
- `subgroup_AV_SYMBOL_24x24` : 🔀🔁🔂▶⏩⏭⏯◀⏪⏮🔼⏫🔽⏬⏸⏹⏺⏏🎦🔅🔆📶🛜📳📴
- `subgroup_GENDER_24x24` : ♀♂⚧
- `subgroup_MATH_24x24` : ✖➕➖➗🟰♾
- `subgroup_PUNCTUATION_24x24` : ‼⁉❓❔❕❗〰
- `subgroup_CURRENCY_24x24` : 💱💲
- `subgroup_OTHER_SYMBOL_24x24` : ⚕♻⚜🔱📛🔰⭕✅☑✔❌❎➰➿〽✳✴❇©®™🫟
- `subgroup_KEYCAP_24x24` : 🔟
- `subgroup_ALPHANUM_24x24` : 🔠🔡🔢🔣🔤🅰🆎🅱🆑🆒🆓ℹ🆔Ⓜ🆕🆖🅾🆗🅿🆘🆙🆚🈁🈂🈷🈶🈯🉐🈹🈚🈲🉑🈸🈴🈳㊗㊙🈺🈵
- `subgroup_GEOMETRIC_24x24` : 🔴🟠🟡🟢🔵🟣🟤⚫⚪🟥🟧🟨🟩🟦🟪🟫⬛⬜◼◻◾◽▪▫🔶🔷🔸🔹🔺🔻💠🔘🔳🔲

</details>
<details><summary><code>group_FLAGS_24x24</code> (1 subgroup)</summary>

- `subgroup_FLAG_24x24` : 🏁🚩🎌🏴🏳

</details>

## Size `32x32`

<details><summary><code>group_SMILEYS_EMOTION_32x32</code> (16 subgroups)</summary>

- `subgroup_FACE_SMILING_32x32` : 😀😃😄😁😆😅🤣😂🙂🙃🫠😉😊😇
- `subgroup_FACE_AFFECTION_32x32` : 🥰😍🤩😘😗☺😚😙🥲
- `subgroup_FACE_TONGUE_32x32` : 😋😛😜🤪😝🤑
- `subgroup_FACE_HAND_32x32` : 🤗🤭🫢🫣🤫🤔🫡
- `subgroup_FACE_NEUTRAL_SKEPTICAL_32x32` : 🤐🤨😐😑😶🫥😏😒🙄😬🤥🫨
- `subgroup_FACE_SLEEPY_32x32` : 😌😔😪🤤😴🫩
- `subgroup_FACE_UNWELL_32x32` : 😷🤒🤕🤢🤮🤧🥵🥶🥴😵🤯
- `subgroup_FACE_HAT_32x32` : 🤠🥳🥸
- `subgroup_FACE_GLASSES_32x32` : 😎🤓🧐
- `subgroup_FACE_CONCERNED_32x32` : 😕🫤😟🙁☹😮😯😲😳🥺🥹😦😧😨😰😥😢😭😱😖😣😞😓😩😫🥱
- `subgroup_FACE_NEGATIVE_32x32` : 😤😡😠🤬😈👿💀☠
- `subgroup_FACE_COSTUME_32x32` : 💩🤡👹👺👻👽👾🤖
- `subgroup_CAT_FACE_32x32` : 😺😸😹😻😼😽🙀😿😾
- `subgroup_MONKEY_FACE_32x32` : 🙈🙉🙊
- `subgroup_HEART_32x32` : 💌💘💝💖💗💓💞💕💟❣💔❤🩷🧡💛💚💙🩵💜🤎🖤🩶🤍
- `subgroup_EMOTION_32x32` : 💋💯💢💥💫💦💨🕳💬🗨🗯💭💤

</details>
<details><summary><code>group_PEOPLE_BODY_32x32</code> (16 subgroups)</summary>

- `subgroup_HAND_FINGERS_OPEN_32x32` : 👋🤚🖐✋🖖🫱🫲🫳🫴🫷🫸
- `subgroup_HAND_FINGERS_PARTIAL_32x32` : 👌🤌🤏✌🤞🫰🤟🤘🤙
- `subgroup_HAND_SINGLE_FINGER_32x32` : 👈👉👆🖕👇☝🫵
- `subgroup_HAND_FINGERS_CLOSED_32x32` : 👍👎✊👊🤛🤜
- `subgroup_HANDS_32x32` : 👏🙌🫶👐🤲🤝🙏
- `subgroup_HAND_PROP_32x32` : ✍💅🤳
- `subgroup_BODY_PARTS_32x32` : 💪🦾🦿🦵🦶👂🦻👃🧠🫀🫁🦷🦴👀👁👅👄🫦
- `subgroup_PERSON_32x32` : 👶🧒👦👧🧑👱👨🧔👩🧓👴👵
- `subgroup_PERSON_GESTURE_32x32` : 🙍🙎🙅🙆💁🙋🧏🙇🤦🤷
- `subgroup_PERSON_ROLE_32x32` : 👮🕵💂🥷👷🫅🤴👸👳👲🧕🤵👰🤰🫃🫄🤱
- `subgroup_PERSON_FANTASY_32x32` : 👼🎅🤶🦸🦹🧙🧚🧛🧜🧝🧞🧟🧌
- `subgroup_PERSON_ACTIVITY_32x32` : 💆💇🚶🧍🧎🏃💃🕺🕴👯🧖🧗
- `subgroup_PERSON_SPORT_32x32` : 🤺🏇⛷🏂🏌🏄🚣🏊⛹🏋🚴🚵🤸🤼🤽🤾🤹
- `subgroup_PERSON_RESTING_32x32` : 🧘🛀🛌
- `subgroup_FAMILY_32x32` : 👭👫👬💏💑
- `subgroup_PERSON_SYMBOL_32x32` : 🗣👤👥🫂👪👣🫆

</details>
<details><summary><code>group_COMPONENT_32x32</code> (2 subgroups)</summary>

- `subgroup_SKIN_TONE_32x32` : 🏻🏼🏽🏾🏿
- `subgroup_HAIR_STYLE_32x32` : 🦰🦱🦳🦲

</details>
<details><summary><code>group_ANIMALS_NATURE_32x32</code> (8 subgroups)</summary>

- `subgroup_ANIMAL_MAMMAL_32x32` : 🐵🐒🦍🦧🐶🐕🦮🐩🐺🦊🦝🐱🐈🦁🐯🐅🐆🐴🫎🫏🐎🦄🦓🦌🦬🐮🐂🐃🐄🐷🐖🐗🐽🐏🐑🐐🐪🐫🦙🦒🐘🦣🦏🦛🐭🐁🐀🐹🐰🐇🐿🦫🦔🦇🐻🐨🐼🦥🦦🦨🦘🦡🐾
- `subgroup_ANIMAL_BIRD_32x32` : 🦃🐔🐓🐣🐤🐥🐦🐧🕊🦅🦆🦢🦉🦤🪶🦩🦚🦜🪽🪿
- `subgroup_ANIMAL_AMPHIBIAN_32x32` : 🐸
- `subgroup_ANIMAL_REPTILE_32x32` : 🐊🐢🦎🐍🐲🐉🦕🦖
- `subgroup_ANIMAL_MARINE_32x32` : 🐳🐋🐬🦭🐟🐠🐡🦈🐙🐚🪸🪼🦀🦞🦐🦑🦪
- `subgroup_ANIMAL_BUG_32x32` : 🐌🦋🐛🐜🐝🪲🐞🦗🪳🕷🕸🦂🦟🪰🪱🦠
- `subgroup_PLANT_FLOWER_32x32` : 💐🌸💮🪷🏵🌹🥀🌺🌻🌼🌷🪻
- `subgroup_PLANT_OTHER_32x32` : 🌱🪴🌲🌳🌴🌵🌾🌿☘🍀🍁🍂🍃🪹🪺🍄🪾

</details>
<details><summary><code>group_FOOD_DRINK_32x32</code> (7 subgroups)</summary>

- `subgroup_FOOD_FRUIT_32x32` : 🍇🍈🍉🍊🍋🍌🍍🥭🍎🍏🍐🍑🍒🍓🫐🥝🍅🫒🥥
- `subgroup_FOOD_VEGETABLE_32x32` : 🥑🍆🥔🥕🌽🌶🫑🥒🥬🥦🧄🧅🥜🫘🌰🫚🫛🫜
- `subgroup_FOOD_PREPARED_32x32` : 🍞🥐🥖🫓🥨🥯🥞🧇🧀🍖🍗🥩🥓🍔🍟🍕🌭🥪🌮🌯🫔🥙🧆🥚🍳🥘🍲🫕🥣🥗🍿🧈🧂🥫
- `subgroup_FOOD_ASIAN_32x32` : 🍱🍘🍙🍚🍛🍜🍝🍠🍢🍣🍤🍥🥮🍡🥟🥠🥡
- `subgroup_FOOD_SWEET_32x32` : 🍦🍧🍨🍩🍪🎂🍰🧁🥧🍫🍬🍭🍮🍯
- `subgroup_DRINK_32x32` : 🍼🥛☕🫖🍵🍶🍾🍷🍸🍹🍺🍻🥂🥃🫗🥤🧋🧃🧉🧊
- `subgroup_DISHWARE_32x32` : 🥢🍽🍴🥄🔪🫙🏺

</details>
<details><summary><code>group_TRAVEL_PLACES_32x32</code> (11 subgroups)</summary>

- `subgroup_PLACE_MAP_32x32` : 🌍🌎🌏🌐🗺🗾🧭
- `subgroup_PLACE_GEOGRAPHIC_32x32` : 🏔⛰🌋🗻🏕🏖🏜🏝🏞
- `subgroup_PLACE_BUILDING_32x32` : 🏟🏛🏗🧱🪨🪵🛖🏘🏚🏠🏡🏢🏣🏤🏥🏦🏨🏩🏪🏫🏬🏭🏯🏰💒🗼🗽
- `subgroup_PLACE_RELIGIOUS_32x32` : ⛪🕌🛕🕍⛩🕋
- `subgroup_PLACE_OTHER_32x32` : ⛲⛺🌁🌃🏙🌄🌅🌆🌇🌉♨🎠🛝🎡🎢💈🎪
- `subgroup_TRANSPORT_GROUND_32x32` : 🚂🚃🚄🚅🚆🚇🚈🚉🚊🚝🚞🚋🚌🚍🚎🚐🚑🚒🚓🚔🚕🚖🚗🚘🚙🛻🚚🚛🚜🏎🏍🛵🦽🦼🛺🚲🛴🛹🛼🚏🛣🛤🛢⛽🛞🚨🚥🚦🛑🚧
- `subgroup_TRANSPORT_WATER_32x32` : ⚓🛟⛵🛶🚤🛳⛴🛥🚢
- `subgroup_TRANSPORT_AIR_32x32` : ✈🛩🛫🛬🪂💺🚁🚟🚠🚡🛰🚀🛸
- `subgroup_HOTEL_32x32` : 🛎🧳
- `subgroup_TIME_32x32` : ⌛⏳⌚⏰⏱⏲🕰🕛🕧🕐🕜🕑🕝🕒🕞🕓🕟🕔🕠🕕🕡🕖🕢🕗🕣🕘🕤🕙🕥🕚🕦
- `subgroup_SKY_WEATHER_32x32` : 🌑🌒🌓🌔🌕🌖🌗🌘🌙🌚🌛🌜🌡☀🌝🌞🪐⭐🌟🌠🌌☁⛅⛈🌤🌥🌦🌧🌨🌩🌪🌫🌬🌀🌈🌂☂☔⛱⚡❄☃⛄☄🔥💧🌊

</details>
<details><summary><code>group_ACTIVITIES_32x32</code> (5 subgroups)</summary>

- `subgroup_EVENT_32x32` : 🎃🎄🎆🎇🧨✨🎈🎉🎊🎋🎍🎎🎏🎐🎑🧧🎀🎁🎗🎟🎫
- `subgroup_AWARD_MEDAL_32x32` : 🎖🏆🏅🥇🥈🥉
- `subgroup_SPORT_32x32` : ⚽⚾🥎🏀🏐🏈🏉🎾🥏🎳🏏🏑🏒🥍🏓🏸🥊🥋🥅⛳⛸🎣🤿🎽🎿🛷🥌
- `subgroup_GAME_32x32` : 🎯🪀🪁🔫🎱🔮🪄🎮🕹🎰🎲🧩🧸🪅🪩🪆♠♥♦♣♟🃏🀄🎴
- `subgroup_ARTS_CRAFTS_32x32` : 🎭🖼🎨🧵🪡🧶🪢

</details>
<details><summary><code>group_OBJECTS_32x32</code> (18 subgroups)</summary>

- `subgroup_CLOTHING_32x32` : 👓🕶🥽🥼🦺👔👕👖🧣🧤🧥🧦👗👘🥻🩱🩲🩳👙👚🪭👛👜👝🛍🎒🩴👞👟🥾🥿👠👡🩰👢🪮👑👒🎩🎓🧢🪖⛑📿💄💍💎
- `subgroup_SOUND_32x32` : 🔇🔈🔉🔊📢📣📯🔔🔕
- `subgroup_MUSIC_32x32` : 🎼🎵🎶🎙🎚🎛🎤🎧📻
- `subgroup_MUSICAL_INSTRUMENT_32x32` : 🎷🪗🎸🎹🎺🎻🪕🥁🪘🪇🪈🪉
- `subgroup_PHONE_32x32` : 📱📲☎📞📟📠
- `subgroup_COMPUTER_32x32` : 🔋🪫🔌💻🖥🖨⌨🖱🖲💽💾💿📀🧮
- `subgroup_LIGHT_VIDEO_32x32` : 🎥🎞📽🎬📺📷📸📹📼🔍🔎🕯💡🔦🏮🪔
- `subgroup_BOOK_PAPER_32x32` : 📔📕📖📗📘📙📚📓📒📃📜📄📰🗞📑🔖🏷
- `subgroup_MONEY_32x32` : 💰🪙💴💵💶💷💸💳🧾💹
- `subgroup_MAIL_32x32` : ✉📧📨📩📤📥📦📫📪📬📭📮🗳
- `subgroup_WRITING_32x32` : ✏✒🖋🖊🖌🖍📝
- `subgroup_OFFICE_32x32` : 💼📁📂🗂📅📆🗒🗓📇📈📉📊📋📌📍📎🖇📏📐✂🗃🗄🗑
- `subgroup_LOCK_32x32` : 🔒🔓🔏🔐🔑🗝
- `subgroup_TOOL_32x32` : 🔨🪓⛏⚒🛠🗡⚔💣🪃🏹🛡🪚🔧🪛🔩⚙🗜⚖🦯🔗⛓🪝🧰🧲🪜🪏
- `subgroup_SCIENCE_32x32` : ⚗🧪🧫🧬🔬🔭📡
- `subgroup_MEDICAL_32x32` : 💉🩸💊🩹🩼🩺🩻
- `subgroup_HOUSEHOLD_32x32` : 🚪🛗🪞🪟🛏🛋🪑🚽🪠🚿🛁🪤🪒🧴🧷🧹🧺🧻🪣🧼🫧🪥🧽🧯🛒
- `subgroup_OTHER_OBJECT_32x32` : 🚬⚰🪦⚱🧿🪬🗿🪧🪪

</details>
<details><summary><code>group_SYMBOLS_32x32</code> (14 subgroups)</summary>

- `subgroup_TRANSPORT_SIGN_32x32` : 🏧🚮🚰♿🚹🚺🚻🚼🚾🛂🛃🛄🛅
- `subgroup_WARNING_32x32` : ⚠🚸⛔🚫🚳🚭🚯🚱🚷📵🔞☢☣
- `subgroup_ARROW_32x32` : ⬆↗➡↘⬇↙⬅↖↕↔↩↪⤴⤵🔃🔄🔙🔚🔛🔜🔝
- `subgroup_RELIGION_32x32` : 🛐⚛🕉✡☸☯✝☦☪☮🕎🔯🪯
- `subgroup_ZODIAC_32x32` : ♈♉♊♋♌♍♎♏♐♑♒♓⛎
- `subgroup_AV_SYMBOL_32x32` : 🔀🔁🔂▶⏩⏭⏯◀⏪⏮🔼⏫🔽⏬⏸⏹⏺⏏🎦🔅🔆📶🛜📳📴
- `subgroup_GENDER_32x32` : ♀♂⚧
- `subgroup_MATH_32x32` : ✖➕➖➗🟰♾
- `subgroup_PUNCTUATION_32x32` : ‼⁉❓❔❕❗〰
- `subgroup_CURRENCY_32x32` : 💱💲
- `subgroup_OTHER_SYMBOL_32x32` : ⚕♻⚜🔱📛🔰⭕✅☑✔❌❎➰➿〽✳✴❇©®™🫟
- `subgroup_KEYCAP_32x32` : 🔟
- `subgroup_ALPHANUM_32x32` : 🔠🔡🔢🔣🔤🅰🆎🅱🆑🆒🆓ℹ🆔Ⓜ🆕🆖🅾🆗🅿🆘🆙🆚🈁🈂🈷🈶🈯🉐🈹🈚🈲🉑🈸🈴🈳㊗㊙🈺🈵
- `subgroup_GEOMETRIC_32x32` : 🔴🟠🟡🟢🔵🟣🟤⚫⚪🟥🟧🟨🟩🟦🟪🟫⬛⬜◼◻◾◽▪▫🔶🔷🔸🔹🔺🔻💠🔘🔳🔲

</details>
<details><summary><code>group_FLAGS_32x32</code> (1 subgroup)</summary>

- `subgroup_FLAG_32x32` : 🏁🚩🎌🏴🏳

</details>

## Size `64x64`

<details><summary><code>group_SMILEYS_EMOTION_64x64</code> (16 subgroups)</summary>

- `subgroup_FACE_SMILING_64x64` : 😀😃😄😁😆😅🤣😂🙂🙃🫠😉😊😇
- `subgroup_FACE_AFFECTION_64x64` : 🥰😍🤩😘😗☺😚😙🥲
- `subgroup_FACE_TONGUE_64x64` : 😋😛😜🤪😝🤑
- `subgroup_FACE_HAND_64x64` : 🤗🤭🫢🫣🤫🤔🫡
- `subgroup_FACE_NEUTRAL_SKEPTICAL_64x64` : 🤐🤨😐😑😶🫥😏😒🙄😬🤥🫨
- `subgroup_FACE_SLEEPY_64x64` : 😌😔😪🤤😴🫩
- `subgroup_FACE_UNWELL_64x64` : 😷🤒🤕🤢🤮🤧🥵🥶🥴😵🤯
- `subgroup_FACE_HAT_64x64` : 🤠🥳🥸
- `subgroup_FACE_GLASSES_64x64` : 😎🤓🧐
- `subgroup_FACE_CONCERNED_64x64` : 😕🫤😟🙁☹😮😯😲😳🥺🥹😦😧😨😰😥😢😭😱😖😣😞😓😩😫🥱
- `subgroup_FACE_NEGATIVE_64x64` : 😤😡😠🤬😈👿💀☠
- `subgroup_FACE_COSTUME_64x64` : 💩🤡👹👺👻👽👾🤖
- `subgroup_CAT_FACE_64x64` : 😺😸😹😻😼😽🙀😿😾
- `subgroup_MONKEY_FACE_64x64` : 🙈🙉🙊
- `subgroup_HEART_64x64` : 💌💘💝💖💗💓💞💕💟❣💔❤🩷🧡💛💚💙🩵💜🤎🖤🩶🤍
- `subgroup_EMOTION_64x64` : 💋💯💢💥💫💦💨🕳💬🗨🗯💭💤

</details>
<details><summary><code>group_PEOPLE_BODY_64x64</code> (16 subgroups)</summary>

- `subgroup_HAND_FINGERS_OPEN_64x64` : 👋🤚🖐✋🖖🫱🫲🫳🫴🫷🫸
- `subgroup_HAND_FINGERS_PARTIAL_64x64` : 👌🤌🤏✌🤞🫰🤟🤘🤙
- `subgroup_HAND_SINGLE_FINGER_64x64` : 👈👉👆🖕👇☝🫵
- `subgroup_HAND_FINGERS_CLOSED_64x64` : 👍👎✊👊🤛🤜
- `subgroup_HANDS_64x64` : 👏🙌🫶👐🤲🤝🙏
- `subgroup_HAND_PROP_64x64` : ✍💅🤳
- `subgroup_BODY_PARTS_64x64` : 💪🦾🦿🦵🦶👂🦻👃🧠🫀🫁🦷🦴👀👁👅👄🫦
- `subgroup_PERSON_64x64` : 👶🧒👦👧🧑👱👨🧔👩🧓👴👵
- `subgroup_PERSON_GESTURE_64x64` : 🙍🙎🙅🙆💁🙋🧏🙇🤦🤷
- `subgroup_PERSON_ROLE_64x64` : 👮🕵💂🥷👷🫅🤴👸👳👲🧕🤵👰🤰🫃🫄🤱
- `subgroup_PERSON_FANTASY_64x64` : 👼🎅🤶🦸🦹🧙🧚🧛🧜🧝🧞🧟🧌
- `subgroup_PERSON_ACTIVITY_64x64` : 💆💇🚶🧍🧎🏃💃🕺🕴👯🧖🧗
- `subgroup_PERSON_SPORT_64x64` : 🤺🏇⛷🏂🏌🏄🚣🏊⛹🏋🚴🚵🤸🤼🤽🤾🤹
- `subgroup_PERSON_RESTING_64x64` : 🧘🛀🛌
- `subgroup_FAMILY_64x64` : 👭👫👬💏💑
- `subgroup_PERSON_SYMBOL_64x64` : 🗣👤👥🫂👪👣🫆

</details>
<details><summary><code>group_COMPONENT_64x64</code> (2 subgroups)</summary>

- `subgroup_SKIN_TONE_64x64` : 🏻🏼🏽🏾🏿
- `subgroup_HAIR_STYLE_64x64` : 🦰🦱🦳🦲

</details>
<details><summary><code>group_ANIMALS_NATURE_64x64</code> (8 subgroups)</summary>

- `subgroup_ANIMAL_MAMMAL_64x64` : 🐵🐒🦍🦧🐶🐕🦮🐩🐺🦊🦝🐱🐈🦁🐯🐅🐆🐴🫎🫏🐎🦄🦓🦌🦬🐮🐂🐃🐄🐷🐖🐗🐽🐏🐑🐐🐪🐫🦙🦒🐘🦣🦏🦛🐭🐁🐀🐹🐰🐇🐿🦫🦔🦇🐻🐨🐼🦥🦦🦨🦘🦡🐾
- `subgroup_ANIMAL_BIRD_64x64` : 🦃🐔🐓🐣🐤🐥🐦🐧🕊🦅🦆🦢🦉🦤🪶🦩🦚🦜🪽🪿
- `subgroup_ANIMAL_AMPHIBIAN_64x64` : 🐸
- `subgroup_ANIMAL_REPTILE_64x64` : 🐊🐢🦎🐍🐲🐉🦕🦖
- `subgroup_ANIMAL_MARINE_64x64` : 🐳🐋🐬🦭🐟🐠🐡🦈🐙🐚🪸🪼🦀🦞🦐🦑🦪
- `subgroup_ANIMAL_BUG_64x64` : 🐌🦋🐛🐜🐝🪲🐞🦗🪳🕷🕸🦂🦟🪰🪱🦠
- `subgroup_PLANT_FLOWER_64x64` : 💐🌸💮🪷🏵🌹🥀🌺🌻🌼🌷🪻
- `subgroup_PLANT_OTHER_64x64` : 🌱🪴🌲🌳🌴🌵🌾🌿☘🍀🍁🍂🍃🪹🪺🍄🪾

</details>
<details><summary><code>group_FOOD_DRINK_64x64</code> (7 subgroups)</summary>

- `subgroup_FOOD_FRUIT_64x64` : 🍇🍈🍉🍊🍋🍌🍍🥭🍎🍏🍐🍑🍒🍓🫐🥝🍅🫒🥥
- `subgroup_FOOD_VEGETABLE_64x64` : 🥑🍆🥔🥕🌽🌶🫑🥒🥬🥦🧄🧅🥜🫘🌰🫚🫛🫜
- `subgroup_FOOD_PREPARED_64x64` : 🍞🥐🥖🫓🥨🥯🥞🧇🧀🍖🍗🥩🥓🍔🍟🍕🌭🥪🌮🌯🫔🥙🧆🥚🍳🥘🍲🫕🥣🥗🍿🧈🧂🥫
- `subgroup_FOOD_ASIAN_64x64` : 🍱🍘🍙🍚🍛🍜🍝🍠🍢🍣🍤🍥🥮🍡🥟🥠🥡
- `subgroup_FOOD_SWEET_64x64` : 🍦🍧🍨🍩🍪🎂🍰🧁🥧🍫🍬🍭🍮🍯
- `subgroup_DRINK_64x64` : 🍼🥛☕🫖🍵🍶🍾🍷🍸🍹🍺🍻🥂🥃🫗🥤🧋🧃🧉🧊
- `subgroup_DISHWARE_64x64` : 🥢🍽🍴🥄🔪🫙🏺

</details>
<details><summary><code>group_TRAVEL_PLACES_64x64</code> (11 subgroups)</summary>

- `subgroup_PLACE_MAP_64x64` : 🌍🌎🌏🌐🗺🗾🧭
- `subgroup_PLACE_GEOGRAPHIC_64x64` : 🏔⛰🌋🗻🏕🏖🏜🏝🏞
- `subgroup_PLACE_BUILDING_64x64` : 🏟🏛🏗🧱🪨🪵🛖🏘🏚🏠🏡🏢🏣🏤🏥🏦🏨🏩🏪🏫🏬🏭🏯🏰💒🗼🗽
- `subgroup_PLACE_RELIGIOUS_64x64` : ⛪🕌🛕🕍⛩🕋
- `subgroup_PLACE_OTHER_64x64` : ⛲⛺🌁🌃🏙🌄🌅🌆🌇🌉♨🎠🛝🎡🎢💈🎪
- `subgroup_TRANSPORT_GROUND_64x64` : 🚂🚃🚄🚅🚆🚇🚈🚉🚊🚝🚞🚋🚌🚍🚎🚐🚑🚒🚓🚔🚕🚖🚗🚘🚙🛻🚚🚛🚜🏎🏍🛵🦽🦼🛺🚲🛴🛹🛼🚏🛣🛤🛢⛽🛞🚨🚥🚦🛑🚧
- `subgroup_TRANSPORT_WATER_64x64` : ⚓🛟⛵🛶🚤🛳⛴🛥🚢
- `subgroup_TRANSPORT_AIR_64x64` : ✈🛩🛫🛬🪂💺🚁🚟🚠🚡🛰🚀🛸
- `subgroup_HOTEL_64x64` : 🛎🧳
- `subgroup_TIME_64x64` : ⌛⏳⌚⏰⏱⏲🕰🕛🕧🕐🕜🕑🕝🕒🕞🕓🕟🕔🕠🕕🕡🕖🕢🕗🕣🕘🕤🕙🕥🕚🕦
- `subgroup_SKY_WEATHER_64x64` : 🌑🌒🌓🌔🌕🌖🌗🌘🌙🌚🌛🌜🌡☀🌝🌞🪐⭐🌟🌠🌌☁⛅⛈🌤🌥🌦🌧🌨🌩🌪🌫🌬🌀🌈🌂☂☔⛱⚡❄☃⛄☄🔥💧🌊

</details>
<details><summary><code>group_ACTIVITIES_64x64</code> (5 subgroups)</summary>

- `subgroup_EVENT_64x64` : 🎃🎄🎆🎇🧨✨🎈🎉🎊🎋🎍🎎🎏🎐🎑🧧🎀🎁🎗🎟🎫
- `subgroup_AWARD_MEDAL_64x64` : 🎖🏆🏅🥇🥈🥉
- `subgroup_SPORT_64x64` : ⚽⚾🥎🏀🏐🏈🏉🎾🥏🎳🏏🏑🏒🥍🏓🏸🥊🥋🥅⛳⛸🎣🤿🎽🎿🛷🥌
- `subgroup_GAME_64x64` : 🎯🪀🪁🔫🎱🔮🪄🎮🕹🎰🎲🧩🧸🪅🪩🪆♠♥♦♣♟🃏🀄🎴
- `subgroup_ARTS_CRAFTS_64x64` : 🎭🖼🎨🧵🪡🧶🪢

</details>
<details><summary><code>group_OBJECTS_64x64</code> (18 subgroups)</summary>

- `subgroup_CLOTHING_64x64` : 👓🕶🥽🥼🦺👔👕👖🧣🧤🧥🧦👗👘🥻🩱🩲🩳👙👚🪭👛👜👝🛍🎒🩴👞👟🥾🥿👠👡🩰👢🪮👑👒🎩🎓🧢🪖⛑📿💄💍💎
- `subgroup_SOUND_64x64` : 🔇🔈🔉🔊📢📣📯🔔🔕
- `subgroup_MUSIC_64x64` : 🎼🎵🎶🎙🎚🎛🎤🎧📻
- `subgroup_MUSICAL_INSTRUMENT_64x64` : 🎷🪗🎸🎹🎺🎻🪕🥁🪘🪇🪈🪉
- `subgroup_PHONE_64x64` : 📱📲☎📞📟📠
- `subgroup_COMPUTER_64x64` : 🔋🪫🔌💻🖥🖨⌨🖱🖲💽💾💿📀🧮
- `subgroup_LIGHT_VIDEO_64x64` : 🎥🎞📽🎬📺📷📸📹📼🔍🔎🕯💡🔦🏮🪔
- `subgroup_BOOK_PAPER_64x64` : 📔📕📖📗📘📙📚📓📒📃📜📄📰🗞📑🔖🏷
- `subgroup_MONEY_64x64` : 💰🪙💴💵💶💷💸💳🧾💹
- `subgroup_MAIL_64x64` : ✉📧📨📩📤📥📦📫📪📬📭📮🗳
- `subgroup_WRITING_64x64` : ✏✒🖋🖊🖌🖍📝
- `subgroup_OFFICE_64x64` : 💼📁📂🗂📅📆🗒🗓📇📈📉📊📋📌📍📎🖇📏📐✂🗃🗄🗑
- `subgroup_LOCK_64x64` : 🔒🔓🔏🔐🔑🗝
- `subgroup_TOOL_64x64` : 🔨🪓⛏⚒🛠🗡⚔💣🪃🏹🛡🪚🔧🪛🔩⚙🗜⚖🦯🔗⛓🪝🧰🧲🪜🪏
- `subgroup_SCIENCE_64x64` : ⚗🧪🧫🧬🔬🔭📡
- `subgroup_MEDICAL_64x64` : 💉🩸💊🩹🩼🩺🩻
- `subgroup_HOUSEHOLD_64x64` : 🚪🛗🪞🪟🛏🛋🪑🚽🪠🚿🛁🪤🪒🧴🧷🧹🧺🧻🪣🧼🫧🪥🧽🧯🛒
- `subgroup_OTHER_OBJECT_64x64` : 🚬⚰🪦⚱🧿🪬🗿🪧🪪

</details>
<details><summary><code>group_SYMBOLS_64x64</code> (14 subgroups)</summary>

- `subgroup_TRANSPORT_SIGN_64x64` : 🏧🚮🚰♿🚹🚺🚻🚼🚾🛂🛃🛄🛅
- `subgroup_WARNING_64x64` : ⚠🚸⛔🚫🚳🚭🚯🚱🚷📵🔞☢☣
- `subgroup_ARROW_64x64` : ⬆↗➡↘⬇↙⬅↖↕↔↩↪⤴⤵🔃🔄🔙🔚🔛🔜🔝
- `subgroup_RELIGION_64x64` : 🛐⚛🕉✡☸☯✝☦☪☮🕎🔯🪯
- `subgroup_ZODIAC_64x64` : ♈♉♊♋♌♍♎♏♐♑♒♓⛎
- `subgroup_AV_SYMBOL_64x64` : 🔀🔁🔂▶⏩⏭⏯◀⏪⏮🔼⏫🔽⏬⏸⏹⏺⏏🎦🔅🔆📶🛜📳📴
- `subgroup_GENDER_64x64` : ♀♂⚧
- `subgroup_MATH_64x64` : ✖➕➖➗🟰♾
- `subgroup_PUNCTUATION_64x64` : ‼⁉❓❔❕❗〰
- `subgroup_CURRENCY_64x64` : 💱💲
- `subgroup_OTHER_SYMBOL_64x64` : ⚕♻⚜🔱📛🔰⭕✅☑✔❌❎➰➿〽✳✴❇©®™🫟
- `subgroup_KEYCAP_64x64` : 🔟
- `subgroup_ALPHANUM_64x64` : 🔠🔡🔢🔣🔤🅰🆎🅱🆑🆒🆓ℹ🆔Ⓜ🆕🆖🅾🆗🅿🆘🆙🆚🈁🈂🈷🈶🈯🉐🈹🈚🈲🉑🈸🈴🈳㊗㊙🈺🈵
- `subgroup_GEOMETRIC_64x64` : 🔴🟠🟡🟢🔵🟣🟤⚫⚪🟥🟧🟨🟩🟦🟪🟫⬛⬜◼◻◾◽▪▫🔶🔷🔸🔹🔺🔻💠🔘🔳🔲

</details>
<details><summary><code>group_FLAGS_64x64</code> (1 subgroup)</summary>

- `subgroup_FLAG_64x64` : 🏁🚩🎌🏴🏳

</details>
