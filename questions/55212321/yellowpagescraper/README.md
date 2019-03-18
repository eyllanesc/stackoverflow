# Command Line:

```bash
foo@bar:~$ cd scrape
foo@bar:~$ scrapy crawl yellow -a parameters='{"search_item": "house", "locations": ["usa", "germany", "brazil"]}'
``` 

# Terminal:

```bash
foo@bar:~$ python terminal.py 
Input The Search Item: house
Location:usa
Do you want to add a new location?: [y/n]: y
Location:germany
Do you want to add a new location?: [y/n]: brazil
Please use y/n or yes/no.

Do you want to add a new location?: [y/n]: n
2019-03-17 21:10:41 [scrapy.utils.log] INFO: Scrapy 1.6.0 started (bot: scrape)
...
```  

# GUI:


```bash
foo@bar:~$ python gui.py
``` 

  ![](screenshot.png) 