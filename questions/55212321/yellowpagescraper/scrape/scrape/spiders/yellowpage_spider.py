import json
import scrapy
from scrape.items import Item

class YellowSpider(scrapy.Spider):
    name = "yellow"

    def __init__(self, *args, **kwargs):
        super(YellowSpider, self).__init__(*args, **kwargs)
        self.seen_business_names = []
        self.seen_phonenumbers = []
        self.seen_websites = []
        self.seen_emails = []

    def start_requests(self):
        if not hasattr(self, 'parameters'):
            return
        parameters = json.loads(self.parameters)
        search_item = parameters['search_item']
        locations = parameters['locations']
        for location in locations:
            url = "https://www.yellowpages.com/search?search_terms={}&geo_location_terms={}".format(search_item, location)
            yield scrapy.Request(url=url, callback=self.parse, meta={'location': location})

    def parse(self, response):
        location = response.meta['location']
        for href in response.css('div.v-card a.business-name::attr(href)'):
            yield response.follow(href, self.businessprofile, meta={'location': location})

        for href in response.css('div.pagination a::attr(href)'):
            yield response.follow(href, self.parse, meta={'location': location})

    def businessprofile(self, response):
        location = response.meta['location']
        for business in response.css('header#main-header'):
            item = Item()
            item['business_name'] = business.css('div.sales-info h1::text').extract()
            w = business.css('a.secondary-btn.website-link::attr(href)').extract()

            item['website'] = str(w).strip('[]')

            item['location'] = location

            s = business.css('a.email-business::attr(href)').extract()
            item['email'] = [item[7:] for item in s]

            item['phonenumber'] = business.css('p.phone::text').extract_first()
            for x in item['email']:
                #new code here, call to self.seen_business_names
                if x not in self.seen_emails:
                    if item['email']:
                        if item['phonenumber']:
                            if item['website']:
                                self.seen_emails.append(x)
                                yield item

