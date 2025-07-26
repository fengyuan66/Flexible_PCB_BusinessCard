# Flexible PCB card
A PCB business card inspired by Github's, with displays that can adapt to whichever event I attend

**Notes**

I've included the firmware. However, it hasn't gone through any testing yet. I've tried my best to understand and check that the code reflect the irl board. Please see  journal for more details regarding the making of the firmware.

Also, I know that the PCB business card is now 2 points, but I genuinely feel like that this design deserves at least fits in the 4 point category for its features. Unlike some of my other projects, I am pretty confident in my judgement for this one. Though if it doesn't deserve 4 points, I'm okay with that as well.

<h3>Project Description</h3>

This is a PCB business card with my basic contact info printed on it. It is based off this really cool PCB business card design on Github (I couldn't find the original link :() (Hi this is Harry from like 1 hour later, turns out it's the "Github Universe Badge" as pointed out by this one guy's journal). Its main feature is its ability to display different things under different contexts. The way it works is simple...

1. There exists an image and a text folder in an external micro SD card
2. Files are stored accordingly into the external micro SD card's folders
3. The displays iterate through the contents in their corresponding folder when their corresponding button is pressed

There's also some cool LED lights to light up the hole thing and grant aura to the otherwise bland-looking information silkscreen. You can toggle them with its own button, too!

The top square display is for images, the bottom is for texts.

<h3>Why I built it</h3>

To be blatantly honest...

**1. To get enough points and get reimbursement my flight**

I feel kinda upset because the price of my flight dropped by like 300 dollars days after I bought it. Also I'm like 2 points away from getting the reimbursement to completely cover my flight...


But at the same time...

**2. It's something that's useful**

A regular PCB business card I find is too generic. A common need I find when attending events is that I sometimes need to display some sort of information. This could look like a QR code when running the next boba drops workshop, or displaying which school you are from during a field trip. Having a PCB card that can display information that can change depending on the event is super helpful because not only does it make you not have to hold up a piece of paper, people would pay more attention at the displayed information because they find it cool.

**2. Unique technical skills involved**

My previous project taught me how to (in an introductory manner) use Kicad's schematic tool and Fusion360's modelling. This project completes the Kicad design process by involving uniquely PCB design and firmware. I think that with these two Highway projects, I would have an introduction to the whole hardware design process.



<h3>Pictures of my project</h3>

<h2>Full 3D model</h2>

PCB Card - no displays + microcontroller

![alt text](Assets/image-2.png)


PCB Card - with displays + microcontroller (and yes the 1.8"OLED and SD card receptor looks weird but trust me it's wired correctly in that way)

![alt text](Assets/{D1354CFE-27D3-4F61-BB18-D3CD1A534CFE}.png)


<h2>Schematics<h2>

**LEGEND:**

Blue = controls

Yellow = grounds

Green = power

![alt text](PCBBusinessCardSchematics.svg)

<h2>BOM</h2>

By the way, the JLPCB quote I couldn't include a link to, so here's an image instead:

![alt text](Assets/JLPCBQuote.PNG)


| Platform | Description                            | Price per listed lot | # of parts per listed lot | Lots purchased    | Final price (+shipping), (CAD) | Final price (USD) | Already owned? | Comments                                                                                                      | Link                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  |
|----------|----------------------------------------|----------------------|---------------------------|-------------------|--------------------------------|-------------------|----------------|---------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Taobao   | WS2812 LED light strip                 | 0.19                 | 1                         | 1                 | 0.19                           | 0.1387            | No             |                                                                                                               | https://item.taobao.com/item.htm?abbucket=8&id=713275663555&ltk2=1753504932468kc5d1mva35jqm2i7ez5niq&ns=1&priceTId=213e03b917535049057584274e1bd4&skuId=5162177838989&spm=a21n57.1.hoverItem.32&utparam=%7B%22aplus_abtest%22%3A%22ddbe73aa2c41ad0c6b1321407c129fc9%22%7D&xxc=taobaoSearch                                                                                                                                                                                                                                                                                                                                            |
| Taobao   | MicroSD card interface                 | 0.74                 | 1                         | 1                 | 0.74                           | 0.5402            | No             |                                                                                                               | https://detail.tmall.com/item.htm?from=cart&id=41337396998&pisk=gUnKXfaxSCA3spnLIv8GEGrEO1vi9FDEBXkfq7VhPfhtNbelqYNu2bh-wW4WTkm-6bG8EgDSq8i8Yc0hqWAU2YG02IADmnDELkrWiIm7TFp8c-w5R_4CChZuevq5H5kELuP5I_Tm5vWJ0VGFN8NWBlw83aZ5R8_6B82uNuNQP1__h5Z7VzNC1Ow3H9s7NM9TC82PA6NCRNt_KJZ7NbZWBANaeuNSMpTLZCVV22EQeYQPf8j5VceL5nDQ13ksbJF0ividVg9zpyFjd5dCuorQ5Yz-4TS8lvgqa-GCOQFrXAiIljOG-WgYex0-dHs_xDkIlziXaaGYvbUjAPB5AlZ__lescLb4scFnNDU6niUufm4bAVYwtzqLHbiE9TISGADmYPoJM1Nr--r_e0Jfy7U54onmDK2liSelRdpOzazQQV9SslD-T5oTBSvMIa7zWXeTidpOzazQQRFDQf7PzPhd.&skuId=5051669025377&spm=a1z0d.6639537%2F202410.item.d41337396998.174b7484ndtpOq |
| Taobao   | 0.91 inch OLED display (text)          | 1.12                 | 1                         | 1                 | 1.12                           | 0.8176            | No             |                                                                                                               | https://detail.tmall.com/item.htm?abbucket=8&id=600261313078&ltk2=1753504398479ci2khaq2kqmhe2vs5xy105&ns=1&priceTId=215042e817535043927425208e1a9d&skuId=4193259944122&spm=a21n57.1.hoverItem.2&utparam=%7B%22aplus_abtest%22%3A%22d5c49652632f13f333e3844f6e84d441%22%7D&xxc=taobaoSearch                                                                                                                                                                                                                                                                                                                                            |
| Taobao   | 1.8 inch OLED display (image)          | 2.06                 | 1                         | 1                 | 2.06                           | 1.5038            | No             |                                                                                                               | https://item.taobao.com/item.htm?abbucket=8&id=866673025601&ltk2=1753504364623ep1jt9x19yg84l7wt4ls&ns=1&priceTId=2150470017535043573542103e0ef5&skuId=5691733032070&spm=a21n57.1.hoverItem.2&utparam=%7B%22aplus_abtest%22%3A%22499fcad78ff98e920f8aab6d2d4fccf8%22%7D&xxc=taobaoSearch                                                                                                                                                                                                                                                                                                                                               |
| Taobao   | Small push buttons                     | 0.37                 | 20                        | 1                 | 0.37                           | 0.2701            | No             |                                                                                                               | https://detail.tmall.com/item.htm?abbucket=8&id=558374381395&ltk2=1753504272981kvblexa4kwl1wy69p4990u&ns=1&skuId=3471184705960&spm=a21n57.1.hoverItem.2&utparam=%7B%22aplus_abtest%22%3A%227af594b2bd48a0bd27b0f88fe3ede619%22%7D&xxc=taobaoSearch                                                                                                                                                                                                                                                                                                                                                                                    |
| Taobao   | Resistors (330 ohms)                   | 0.36                 | 100 (supposedly)          | 1                 | 0.36                           | 0.2628            | No             | I don't have access in China                                                                                  | https://detail.tmall.com/item.htm?abbucket=8&id=604722661912&ltk2=175350212768347o5euee9doqh9nbgmakur&ns=1&skuId=4405819222938&spm=a21n57.1.hoverItem.5&utparam=%7B%22aplus_abtest%22%3A%22dba4d2246491f2dd2822195b487cf587%22%7D&xxc=taobaoSearch                                                                                                                                                                                                                                                                                                                                                                                    |
| Taobao   | Resistors (47k ohms)                   | 0.36                 | 100 (supposedly)          | 1                 | 0.36                           | 0.2628            | No             | I don't have access in China                                                                                  | https://detail.tmall.com/item.htm?abbucket=8&id=604943038864&ltk2=1753502399979i3pfv8tp7etgh8v9tofn&ns=1&priceTId=215044cc17535018153884876e0ecd&skuId=4235104924044&spm=a21n57.1.hoverItem.1&utparam=%7B%22aplus_abtest%22%3A%2255916e9cfae7a6eee227c2700b316cce%22%7D&xxc=taobaoSearch                                                                                                                                                                                                                                                                                                                                              |
| Taobao   | 512mb MicroSD card + card reader (pack)  | 1.53                 | 1 of each                 | 1                 | 1.53                           | 1.1169            | No             | The reason for the SD card addon option is because I don't have means to write in the card right now in China | https://detail.tmall.com/item.htm?detail_redpacket_pop=true&id=648801516814&ltk2=1753502455647mv98w41yr72et30952i8c&ns=1&priceTId=2147821617535024397927885e18bb&query=%E8%BF%B7%E4%BD%A0SD%E5%8D%A1&skuId=4760055037612&spm=a21n57.1.hoverItem.1&utparam=%7B%22aplus_abtest%22%3A%22d4e84d49866cf6c5d3cc5f9e572d732d%22%7D&xxc=ad_ztc                                                                                                                                                                                                                                                                                                |
| Taobao   | Raspberry Pi Pico w/ pins (Type-C USB) | 9.23                 | 1                         | 1                 | 9.23                           | 6.7379            | No             |                                                                                                               | https://item.taobao.com/item.htm?abbucket=8&id=637653493419&ltk2=1753505064511vsrzv28u4lqitn0uoeoxxq&ns=1&priceTId=215041fb17535050508425643e1ae8&skuId=5953375371936&spm=a21n57.1.hoverItem.3&utparam=%7B%22aplus_abtest%22%3A%227d3fbc0a71df18f4cce1fbea7a63f8af%22%7D&xxc=taobaoSearch                                                                                                                                                                                                                                                                                                                                             |
| JLPCB    | PCB board                              | 2.72                 | 5 (can't change to lower) | 1                 | 3.72                           | 2.7156            | No             |  + 3.72 shipping, -2.72 coupon. Can't add link so image instead.                                              |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
|          |                                        |                      |                           |                   |                                |                   |                |                                                                                                               |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
|          |                                        |                      |                           | Total (CAD, USD): | 19.68                          | 14.3664           |                |                                                                                                               |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
