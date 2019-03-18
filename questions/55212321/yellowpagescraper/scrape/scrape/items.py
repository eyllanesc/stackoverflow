# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://doc.scrapy.org/en/latest/topics/items.html

import scrapy
from scrapy.loader import ItemLoader
from scrapy.loader.processors import TakeFirst, MapCompose, Join
from scrapy.item import Item, Field
from collections import defaultdict


class Item(scrapy.Item):
    business_name = scrapy.Field()
    website = scrapy.Field()
    phonenumber = scrapy.Field()
    email = scrapy.Field()
    location = scrapy.Field()
    second_location = scrapy.Field()
 

    # third_location = scrapy.Field()
    # fourth_location = scrapy.Field()
    visit_id = scrapy.Field()
    visit_status = scrapy.Field()
