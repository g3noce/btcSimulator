import bybit 
import math
import time
from datetime import datetime
from decimal import Decimal

client = bybit.bybit(test = False, api_key='5FLdbvQqybLAKtOi6o', api_secret='tsV6i846D8i9RxwS8wNpVZlV0LO1TXnMcgl7')
print('login to\n', client)

while 1:
    time.sleep(0.9)
    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    time_min = int(now.strftime("%M"))
    time_sec = int(now.strftime("%S"))
    info = client.Market.Market_symbolInfo(symbol="BTCUSDT").result()
    keys = info[0]['result']
    ask_price = keys[0]['ask_price']
    fichier = open("BTC-USD.json", "w")
    ask_price = Decimal("%.2f" % float(ask_price))
    fichier.write(str(ask_price))
    print(" ", ask_price, " at ", current_time)
    fichier.close()
        

fichier.close()
